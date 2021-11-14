#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class MenuItem
{
public:
	MenuItem();
	void LoadFromFile(int id, double price, string name);
	string GetName();
	double GetPrice();


private:
	int itemID;
	double itemPrice;
	string itemName;
};

