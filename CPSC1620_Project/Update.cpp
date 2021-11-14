#include "Update.h"

#include <vector>
#include <string> // Used
#include <ctime>
#include <iostream> // Used
#include <cctype> // Used
#include <conio.h> // Used

#include "MenuItem.h"
#include "Status.h"

using namespace std;

string stringLower(string input)
{
	string oldString = input;
	input = "";
	for (int i = 0; i < oldString.length(); ++i)
	{
		input += tolower(oldString.at(i));
	}
	return input;
}

int Boot(Status &statusTracker)
{
	cout << "SimplePos by Kaden Duncan-Matis." << endl << endl << "Type 'start' to begin taking orders." << endl << "Type 'exit' to exit the program." << endl;
	string input;
	cin >> input; // I really wanted to use _getch() for this but I couldn't get it to work properly on the first run which ultimately caused a lot of confusion.
	input = stringLower(input);
	if (input == "start")
	{
		return 1;
	}
	else if (input == "exit")
	{
		return 2;
	}
	else
	{
		statusTracker.UpdatePassthroughTop(true, "Command not recognized. Please try again.");
		return 0;
	}
}

int Exit(string adminPass, Status& statusTracker)
{
	string exitPassInput;
	cout << "Are you sure you wish to quit? Enter administrator password to continue: ";
	cin >> exitPassInput;
	{
		string passOld = exitPassInput;
		exitPassInput = "";
		for (int i = 0; i < passOld.length(); ++i) // Converts it to lowercase super quick here. Yes, I know I'm committing a crime.
		{
			exitPassInput += tolower(passOld.at(i));
		}
	}
	if (exitPassInput == adminPass)
	{
		cout << "Terminating program. Have a nice day." << endl << "Press any key to continue...";
		_getch();
		exit(EXIT_SUCCESS);
	}
	else
	{
		statusTracker.UpdatePassthroughTop(true, "Incorrect password. Returning to menu.");
		return 0;
	}
}

void OrderTaker(Status &statusTracker, vector<OrderItem> orderList, string currSymbol)
{
	cout << "Order Number: " << statusTracker.GetOrderNo() << endl << endl << "--------------------" << endl << endl;

	if (orderList.size() == 0)
	{
		cout << "(No items)" << endl << endl;
	}
	else
	{
		for (int i = 0; i < orderList.size(); ++i)
		{
			cout << (i) << " --- ";
			orderList.at(i).PrintToOrder(currSymbol);
		}
		cout << endl << "--------------------" << endl << "Total: " << currSymbol << statusTracker.GetTotal();
		if (statusTracker.CheckHasPaid())
		{
			cout << " --- ORDER PAID ---";
		}
		cout<< endl << endl;
	}
}

void EditMenu(Status &statusTracker)
{

}