#pragma once
#include <string>
#include "MenuItem.h"

using namespace std;


class OrderItem
{
public:
	OrderItem();
	void Instruction(string input);
	void SetBaseItem(MenuItem newItem);
	void PrintToOrder(string currSymbol);
	void Order(MenuItem baseItem, string special);
	double getPrice();
private:
	string specialInstruction = "";
	MenuItem baseItem;
	double price = 0.00;
};

