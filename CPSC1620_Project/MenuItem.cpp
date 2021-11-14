#include "MenuItem.h"

using namespace std;

MenuItem::MenuItem() // Constructor
{
	itemName = "";
	itemID = -1;
	itemPrice = 0.00;
}

void MenuItem::LoadFromFile(int id, double price, string name)
{
	itemName = name;
	itemID = id;
	itemPrice = price;
}

string MenuItem::GetName()
{
	return itemName;
}

double MenuItem::GetPrice()
{
	return itemPrice;
}