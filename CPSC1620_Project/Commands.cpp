 #include "Commands.h"

using namespace std;

void executeCmd(Status &statusTracker, vector<string> cmdLine, vector<OrderItem> &orderList, vector<MenuItem> &menuList, string adminPass)
{
	int cmdSwitch;
	if (cmdLine.size() > 0)
	{
		string cmdOne = cmdLine.at(0);

		if (cmdOne == "add" || cmdOne == "order") // I wish switches worked with strings sometimes.
		{
			cmdAdd(statusTracker, orderList, cmdLine, menuList);
		}
		else if (cmdOne == "cancel")
		{
			cmdCancel(statusTracker, orderList, cmdLine, adminPass);
		}
		else if (cmdOne == "del" || cmdOne == "delete" || cmdOne == "remove")
		{
			cmdDel(statusTracker, orderList, cmdLine, menuList);
		}
		else if (cmdOne == "discount")
		{
			cmdDiscount(statusTracker, orderList, cmdLine, menuList, adminPass);
		}
		else if (cmdOne == "exit")
		{
			cmdExit(statusTracker, orderList, cmdLine, adminPass);
		}
		else if (cmdOne == "extracharge")
		{
			cmdExtraCharge(statusTracker, orderList, cmdLine, menuList, adminPass);
		}
		else if (cmdOne == "new" || cmdOne == "neworder")
		{
			cmdNewOrder(statusTracker, orderList);
		}
		else if (cmdOne == "pay")
		{
			cmdPay(statusTracker);
		}
		else if (cmdOne == "clear" || cmdOne == "clr")
		{
			cmdClr();
		}
		else if (cmdOne == "list" || cmdOne == "listitems")
		{
			cmdListItems(statusTracker, menuList);
		}
		else // This hurt me.
		{
			cmdError(statusTracker);
		}
	}
}

void newOrder(Status &statusTracker, vector<OrderItem> &orderList)
{
	orderList.clear();
	statusTracker.NewOrderNo();
	statusTracker.ResetPay();
	statusTracker.SetTotal(0.00);
}

// Order mode ***
// add [item] [special instruction] -- Adds an item. - 0
// clear -- Clears messages - 10
// clr -- Same as clear - 10
// cancel [adminpass] -- cancels the current order. - 1
// del [itemLine] -- deletes an item line. - 2
// delete [itemLine] -- deletes an item line. Same as del. - 2
// discount [amount] [adminpass] -- grants a discount. - 3
// exit [adminpass] -- exits the program. Default asks for password. - 5
// extracharge [amount] [adminpass] -- adds an extra charge. - 6
// new [adminpass] -- creates new order. Requires adminpass if order is not paid for. - 7
// neworder [adminpass] -- same as new. - 7
// order [item] [special instruction] -- Adds a new item. Same as add command. - 0
// pay [method] -- accepts payment. Cash default. Once payment is accepted, new works. - 8
// 
//
//
//
//
//
//

void cmdAdd(Status& statusTracker, vector<OrderItem>& orderList, vector<string> cmdLine, vector<MenuItem>& menuList)
{
	MenuItem getItem;
	bool success = false;
	if (cmdLine.size() > 1) // Exactly 2 means no special instruction. Anything above means added special instructions
	{

		for (int i = 0; i < menuList.size(); ++i) // time to search for the item we need.
		{
			if ((menuList.at(i).GetName()) == cmdLine.at(1)) // check if the item name is the same as the one typed until one matches.
			{
				getItem = menuList.at(i); // copy the menuItem into getItem.
				success = true;
				break;
			}
		}

		if (!success)
		{
			statusTracker.UpdatePassthroughBottom(true,  "Item not found.");
			return;
		}
		
		orderList.push_back(OrderItem::OrderItem()); // Create the object.

		string special = "";

		if (cmdLine.size() > 2)
		{
			for (int i = 2; i < cmdLine.size(); ++i) // fill the remaining data into a string
			{
				special += cmdLine.at(i);
				special += " ";
			}
		}

		orderList.back().Order(getItem, special); // We just made this, so this works.
		statusTracker.UpdateTotal(orderList.back().getPrice());
		return;
	}
	statusTracker.UpdatePassthroughBottom(true, "You need to follow with an item name."); // If it gets here then that means there was insufficient data.
	return;
}

void cmdCancel(Status& statusTracker, vector<OrderItem>& orderList, vector<string> cmdLine, string adminPass)
{
	if (cmdLine.size() > 1) // Exactly 2 means no special instruction. Anything above means added special instructions
	{
		if (cmdLine.at(1) == adminPass) // cancel the order
		{
			statusTracker.UpdatePassthroughBottom(true, "Order cancelled.");
			newOrder(statusTracker, orderList);
		}
		else
		{
			statusTracker.UpdatePassthroughBottom(true, "Password incorrect. You must provide the administrator password to delete the order.");
		}
		return;
	}
	statusTracker.UpdatePassthroughBottom(true, "You must provide the administrator password to cancel an order.");
	return;
}

void cmdDel(Status& statusTracker, vector<OrderItem>& orderList, vector<string> cmdLine, vector<MenuItem>& menuList)
{
	if (cmdLine.size() > 1)
	{
		int linetoDelete;
		try
		{
			linetoDelete = stoi(cmdLine.at(1));
		}
		catch (invalid_argument) // stoi returns invalid_argument if it can't convert the line. This should stop that from crashing the program.
		{
			statusTracker.UpdatePassthroughBottom(true, "Item line is invalid. Please enter a valid item line.");
			return;
		}
		if (linetoDelete >= 0 && linetoDelete < orderList.size())
		{
			double totaltoSubtract = orderList.at(linetoDelete).getPrice();
			statusTracker.SubtractTotal(totaltoSubtract);
			orderList.erase(orderList.begin() + linetoDelete);
			statusTracker.UpdatePassthroughBottom(true, "Item deleted.");
		}
		else
		{
			statusTracker.UpdatePassthroughBottom(true, "Line is out of range.");
		}
		return;
	}
	statusTracker.UpdatePassthroughBottom(true, "Please specify a line to delete.");
	return;
}

void cmdDiscount(Status& statusTracker, vector<OrderItem>& orderList, vector<string> cmdLine, vector<MenuItem>& menuList, string adminPass)
{
	if (cmdLine.size() > 1)
	{
		if (cmdLine.at(1) == adminPass) // apply the discount as an item.
		{
			if (cmdLine.size() > 2)
			{
				double discAmt;
				try
				{
					discAmt = stod(cmdLine.at(2));
				}
				catch (invalid_argument) // stod returns invalid_argument if it can't convert the line. This should stop that from crashing the program.
				{
					statusTracker.UpdatePassthroughBottom(true, "Discount amount is invalid. Please enter a valid amount.");
					return;
				}
				if (discAmt < 0)
				{
					statusTracker.UpdatePassthroughBottom(true, "Discount cannot be a negative. Use 'extracharge' if you wish to add a charge.");
					return;
				}
				OrderItem discount;
				MenuItem discountItem;
				discountItem.LoadFromFile(-1, -(discAmt), "discount"); // I realized later in development I could just repurpose this load function so here it is, being used in a completely different context.
				discount.Order(discountItem, "");
				orderList.push_back(discount);
				statusTracker.UpdateTotal(orderList.back().getPrice());
				statusTracker.UpdatePassthroughBottom(true, "Discount applied.");
			}
			else
			{
				statusTracker.UpdatePassthroughBottom(true, "You must specify the amount of the discount.");
			}
		}
		else
		{
			statusTracker.UpdatePassthroughBottom(true, "Password incorrect. You must provide the administrator password to apply a discount.");
		}
		return;
	}
	statusTracker.UpdatePassthroughBottom(true, "You must provide the administrator password to apply a discount.");
	return;
}

void cmdExit(Status& statusTracker, vector<OrderItem>& orderList, vector<string> cmdLine, string adminPass)
{
	if (cmdLine.size() > 1)
	{
		if (cmdLine.at(1) == adminPass) // exit
		{
			system("cls");
			cout << "Are you sure you wish to exit? You will lose any in-progress order. Type 'yes' to exit. Type anything else to continue." << endl;
			string input;
			cin >> input;
			input = stringLower(input);
			if (input == "yes")
			{
				exit(EXIT_SUCCESS);
			}
			statusTracker.UpdatePassthroughBottom(true, "Program not exited.");
		}
		else
		{
			statusTracker.UpdatePassthroughBottom(true, "Password incorrect. You must provide the administrator password to exit the program."); // Of course you could also just, you know, press the X. This is more to prevent malicious employees, but ultimately needs a lot more work that I can't do.
		}
		return;
	}
	statusTracker.UpdatePassthroughBottom(true, "You must provide the administrator password to exit.");
	return;
}

void cmdExtraCharge(Status& statusTracker, vector<OrderItem>& orderList, vector<string> cmdLine, vector<MenuItem>& menuList, string adminPass)
{
	if (cmdLine.size() > 1)
	{
		if (cmdLine.at(1) == adminPass) // apply the extra as an item.
		{
			if (cmdLine.size() > 2)
			{
				double extAmt;
				try
				{
					extAmt = stod(cmdLine.at(2));
				}
				catch (invalid_argument) // stoi returns invalid_argument if it can't convert the line. This should stop that from crashing the program.
				{
					statusTracker.UpdatePassthroughBottom(true, "Extra charge is invalid. Please enter a valid amount.");
					return;
				}
				if (extAmt < 0)
				{
					statusTracker.UpdatePassthroughBottom(true, "Extra charge cannot be negative Use 'discount' if you wish to add a discount.");
					return;
				}
				OrderItem discount;
				MenuItem discountItem;
				discountItem.LoadFromFile(-1, extAmt, "extra charge"); // I realized later in development I could just repurpose this load function so here it is, being used in a completely different context.
				discount.Order(discountItem, "");
				orderList.push_back(discount);
				statusTracker.UpdateTotal(orderList.back().getPrice());
				statusTracker.UpdatePassthroughBottom(true, "Extra charge applied.");
			}
			else  
			{
				statusTracker.UpdatePassthroughBottom(true, "You must specify the amount of the extra charge.");
			}
		}
		else
		{
			statusTracker.UpdatePassthroughBottom(true, "Password incorrect. You must provide the administrator password to apply an extra charge.");
		}
		return;
	}
	statusTracker.UpdatePassthroughBottom(true, "You must provide the administrator password to apply an extra charge.");
	return;
}

void cmdNewOrder(Status& statusTracker, vector<OrderItem>& orderList)
{
	if (!statusTracker.CheckHasPaid()) // You can't make a new order if the old one hasn't been paid for yet.
	{
		statusTracker.UpdatePassthroughBottom(true, "Order has not been paid for. Use 'cancel' if you wish to cancel an active order.");
		return;
	}
	newOrder(statusTracker, orderList);
}

void cmdPay(Status& statusTracker)
{
	statusTracker.Pay();
}

void cmdClr()
{
	system("cls");
}

void cmdError(Status& statusTracker)
{
	statusTracker.UpdatePassthroughBottom(true, "Invalid command.");
}

void cmdListItems(Status& statusTracker, vector<MenuItem>& menuList)
{
	system("cls");
	cout << "Item ID --- Item Name --- Item Price" << endl << endl << "--------------------" << endl << endl;
	for (int i = 0; i < menuList.size(); ++i)
	{
		cout << i << " --- " << menuList.at(i).GetName() << " --- " << menuList.at(i).GetPrice() << endl;
	}
	cout << "--------------------" << endl << "Press any key to continue..." << endl;
	_getch();
}
