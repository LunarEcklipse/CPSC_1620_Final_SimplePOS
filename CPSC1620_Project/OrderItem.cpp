#include "OrderItem.h"

using namespace std;

OrderItem::OrderItem()
{
	specialInstruction = "";
	baseItem;
	price = 0.00;
}

void OrderItem::Instruction(string input)
{
	specialInstruction = input;
}

void OrderItem::SetBaseItem(MenuItem newItem)
{
	baseItem = newItem;
}

void OrderItem::PrintToOrder(string currSymbol)
{
	cout << baseItem.GetName() << " --- " << currSymbol << baseItem.GetPrice() << endl;
	if (specialInstruction != "")
	{
		cout << "   >>> " << specialInstruction << endl;
	}
}

void OrderItem::Order(MenuItem newItem, string special)
{
	baseItem = newItem;
	specialInstruction = special;
	price = newItem.GetPrice();
}

double OrderItem::getPrice()
{
	return price;
}
