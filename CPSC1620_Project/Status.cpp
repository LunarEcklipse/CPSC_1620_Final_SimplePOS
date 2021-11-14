#include "Status.h"


int Status::GetStatus()
{
	return status;
}

void Status::UpdateStatus(int newStatus)
{
	status = newStatus;
}

void Status::UpdatePassthroughTop(bool exists, string passthrough)
{
	hasPassthroughTop = exists;
	passthroughTop = passthrough;
}

void Status::UpdatePassthroughBottom(bool exists, string passthrough)
{
	hasPassthroughBottom = exists;
	passthroughBottom = passthrough;
}

void Status::PrintPassthroughTop()
{
	if (hasPassthroughTop)
	{
		cout << passthroughTop << endl << endl;
		hasPassthroughTop = false; // Set this to false so it doesn't reprint the message every time.
	}
}

void Status::PrintPassthroughBottom()
{
	if (hasPassthroughBottom)
	{
		cout << passthroughBottom << endl << endl;
		hasPassthroughBottom = false; // Set this to false so it doesn't reprint the message every time.
	}
}

void Status::UpdateTotal(double change)
{
	totalPrice += change;
}

void Status::SubtractTotal(double change)
{
	totalPrice -= change;
}

void Status::SetTotal(double set)
{
	totalPrice = set;
}

double Status::GetTotal()
{
	return totalPrice;
}

bool Status::orderTakerFresh()
{
	return initOrder;
}

void Status::setOrderTakerFresh(bool input)
{
	initOrder = input;
}

int Status::GetOrderNo()
{
	return orderNumber;
}

void Status::NewOrderNo()
{
	orderNumber += 1;
}

bool Status::CheckHasPaid()
{
	return hasPaid;
}

void Status::Pay()
{
	hasPaid = true;
}

void Status::ResetPay()
{
	hasPaid = false;
}
