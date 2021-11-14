#pragma once // I chose to use a status object for keeping track of stuff globally. There's probably a better way to do this but this works well.
#include <vector>
#include <string>
#include <iostream>
#include <conio.h>
#include <cstdlib>

using namespace std;

class Status
{
public:
	int GetStatus();
	void UpdateStatus(int newStatus);
	void UpdatePassthroughTop(bool exists, string passthrough);
	void UpdatePassthroughBottom(bool exists, string passthrough);
	void PrintPassthroughTop();
	void PrintPassthroughBottom();
	void UpdateTotal(double change);
	void SubtractTotal(double change);
	void SetTotal(double set);
	double GetTotal();

	bool orderTakerFresh();
	void setOrderTakerFresh(bool input);

	int GetOrderNo();
	void NewOrderNo();

	bool CheckHasPaid();
	void Pay();
	void ResetPay();

private:
	int status = 0; // 0 = boot, 1 = order, 2 = edit, 3 = exit.
	int orderNumber = 0;
	bool hasPaid = false;
	double totalPrice = 0.00;

	bool hasPassthroughTop = false; // These two exist to tell the program if it has a passthrough message to push to the next update(). This one prints at the top of the screen.
	string passthroughTop = ""; 
	bool initOrder = false; // If this is set true then neworder doesn't need to be called.

	bool hasPassthroughBottom = false;
	string passthroughBottom = "";
};

