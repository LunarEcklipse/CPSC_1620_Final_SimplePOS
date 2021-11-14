#pragma once
#include <string>

using namespace std;

class User
{
public:
	void loadUser(int userID, string userName, string password, bool isAdmin);
	void newUser(string userName, string userPassword, bool isAdmin);

private:
	bool isAdmin = false; // if true, then the user can use administrator level commands with this account. By default this is false.

	int userID = -1; // -1 is a placeholder. A userID should be assigned at creation.
	
	string userName = "";
	string userPassword = "";
	

};