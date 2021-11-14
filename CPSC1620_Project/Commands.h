#pragma once
#include <vector>
#include <string>
#include <ctime>
#include <conio.h>

#include "MenuItem.h"
#include "OrderItem.h"
#include "Update.h"
#include "Status.h"

using namespace std;

void cmdAdd(Status &statusTracker, vector<OrderItem> &orderList, vector<string> cmdLine, vector<MenuItem> &menuList);
void cmdCancel(Status& statusTracker, vector<OrderItem>& orderList, vector<string> cmdLine, string adminPass);
void cmdDel(Status& statusTracker, vector<OrderItem>& orderList, vector<string> cmdLine, vector<MenuItem>& menuList);
void cmdDiscount(Status& statusTracker, vector<OrderItem>& orderList, vector<string> cmdLine, vector<MenuItem>& menuList, string adminPass);
void cmdExit(Status& statusTracker, vector<OrderItem>& orderList, vector<string> cmdLine, string adminPass);
void cmdExtraCharge(Status& statusTracker, vector<OrderItem>& orderList, vector<string> cmdLine, vector<MenuItem>& menuList, string adminPass);
void cmdNewOrder(Status& statusTracker, vector<OrderItem>& orderList);
void cmdPay(Status& statusTracker);
void cmdClr();
void cmdError(Status& statusTracker);
void cmdListItems(Status& statusTracker, vector<MenuItem>& menuList);

void executeCmd(Status &statusTracker, vector<string> cmdLine, vector<OrderItem>& orderList, vector<MenuItem>& menuList, string adminPass);

void newOrder(Status& statusTracker, vector<OrderItem> &orderList);


