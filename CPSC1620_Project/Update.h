#pragma once
#include <vector>
#include <string> 
#include <iostream>
#include <cctype> 
#include <conio.h>

#include "MenuItem.h"
#include "Status.h"
#include "OrderItem.h"

using namespace std;

string stringLower(string input);
int Boot(Status &statusTracker);
int Exit(string adminPass, Status &statusTracker);
void OrderTaker(Status &statusTracker, vector<OrderItem> orderList, string currSymbol);
void EditMenu(Status &statusTracker);