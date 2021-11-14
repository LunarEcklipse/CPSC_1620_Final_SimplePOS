/* I really enjoyed the object oriented programming style so I decided I want to do something with that for my final project.
I apologize for the numerous files because I wanted to build it cleanly. I really enjoyed this course so I set out to challenge myself
with this project. Thanks for the excellent lessons!

For this project I decided that I want to make a simple menu ordering system for a restaurant.

Proudly built in the backroom of a Burger King at 7 in the morning.*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream> // Gonna be honest with you fstream makes me kind of miss the simplicity of C#'s streamreader and streamwriter.
#include <iomanip>
#include <sstream> // I wanted to test <sstream> and <iterator> for ways to do line input without having to have a break at the end. It worked pretty well, but that's why this is highlighted.

#include <cctype> // I'm not quite sure if I need this yet so I'm leaving it separate so I can axe it later if I don't.

#include <conio.h> // I don't know how I feel about include a library as old and system dependent as conio.h, but I need the functionality.

#include "MenuItem.h"
#include "Status.h"
#include "Update.h"
#include "OrderItem.h"
#include "Commands.h"

using namespace std; // Just to make my life a bit easier.

void createFiles(string ver) // This one creates all the files necessary for this to work. This runs if even one of the files is missing as a sort of failsafe against files being damaged. This isn't amazing as a damaged file wipes the whole thing, but so it is.
{
	fstream newDataFile;
	newDataFile.open("SimplePosData.dat", ios::out | ios::trunc); // I used trunc here because then this prevents the risk of file overwrite and lets this code be reused for resets.
	if (!newDataFile.is_open())
	{
		cout << "Failed to create data file. Check your file permissions. Program will terminate."; // The program cannot continue if it cannot make a data file as read/write is essential
		cout << "Press any key to continue...";
		_getch(); // Again, don't care about return value.
		exit(EXIT_FAILURE); // The program failed, so an exit failure flag is set.
	}
	newDataFile << "SimplePos v. " << ver << endl;
	newDataFile << "Student Project by Kaden Duncan-Matis" << endl << endl;
	newDataFile << "// Please don't tamper with this file unless you know what you're doing! \\" << endl << endl;
	
	cout << "Setting up restaurant name." << endl;
	string input;
	cout << "Enter restaurant name." << endl;
	getline(cin, input);
	newDataFile << "RestaurantName = " << input << endl;

	newDataFile << "CurrencySymbol = $" << endl; // If you want you can change this later in the file.

	cout << "Setting up admin password." << endl;

	cout << "Enter admin password. Password cannot contain a space: " << endl; // I kept getting an absurdly strange runtime exception here that visual studio had no idea what it was. I think it had something to do with trying to use file append, but no idea, hence why the admin password is kept in a separate file. Ultimately, it's why this isn't in a separate function because I couldn't get the file to open to add data to at the end.

	int strLength = input.length();
	{ // We don't need the bool past here so I'm scoping this.
		bool isSpace = true; // We set this to true first to make sure the while loop enters
		while (isSpace)
		{
			getline(cin, input);
			isSpace = false;
			int strLength = input.length();
			for (int i = 0; i < strLength; ++i)
			{
				if (isspace(input.at(i))) // If the character is a space, break the for early and repeat.
				{
					cout << "Password cannot contain a space." << endl;
					isSpace = true;
					break;
				}
			}
		}
	}
	{ // Same here, using scope for oldInput. This chunk sets the input to lowercase.
		string oldInput = input;
		input = "";

		for (int i = 0; i < strLength; ++i)
		{
			input += tolower(oldInput.at(i));
		}
	}
	newDataFile << "Adminpass = " << input << endl;

	cout << "Admin password created." << endl;
	newDataFile.close();
	newDataFile.open("SimplePosMenu.dat", ios::out | ios::trunc);
	newDataFile.close();
	cout << "Files created successfully. Press any key to continue..." << endl;
	_getch(); // Yep ignored don't care. Just using it to hold the program for a moment.
	cout << endl;
	return;
}

void FileCheck(string filename, string ver) // This makes sure the files actually exist. If one of them is missing, it just resets the entire data structure. Yes, this is bad, but I'm going to assume that if one file is damaged others are too.
{
	ifstream fileCheck;
	fileCheck.open(filename);
	// fileCheck.close(); // This line exists for easy testing since everything creates with truncate. Just comment it out for final.
	if (!fileCheck.is_open()) // If the file fails to open, assume that it's because it doesn't exist or needs to be remade.
	{
		cout << "File " << filename << " is missing. Creating new files." << endl; // I must note by the way that this file reader sucks, but I don't honestly know how to make it any better. It will cause huge unknowable problems if the file can't read correctly or is modified in any way that it doesn't like. Don't tamper with it.
		createFiles(ver);
		fileCheck.open(filename);
		if (!fileCheck.is_open())
		{
			cout << "Still couldn't open the file even though it successfully created it. Something strange has happened or the file has been removed already. Terminating program." << endl;
			cout << "Press any key to continue..." << endl;
			int getch(); // Just using this to get out of here.
			exit(EXIT_FAILURE);
		}
		fileCheck.close();
	}
}

void Initialize(string ver) // This is the startup function that loads all the data into memory from a file. and just gets the program ready.
{

	system("cls"); // Clear the screen first and foremost. Yep, this destroys compatability because this is a windows system command and also is a huge security hole, but I couldn't really find many better solutions without going to third party libraries like curses
	cout << "Simple POS ver." << ver << endl << endl;
	cout << "Checking for existing data..." << endl;

	FileCheck("SimplePosData.dat", ver);
	FileCheck("SimplePosMenu.dat", ver);

	cout << "Files found. Loading data..." << endl;
}

vector<string> readLine() // This took a lot of work to figure out. Thanks to the folks at StackOverflow (https://stackoverflow.com/questions/8377660/how-to-cin-to-a-vector) for this one, since I didn't know you could while loop with iss and cin.
{
	vector<string> outVect(0);
	string inString = "";
	string input = "";

	getline(cin, inString);

	istringstream iss(inString);

	while (iss >> input) // I won't pretend like I know how this works, all I know is that it does, and it does very well.
	{
		string convert = input;
		input = "";
		int strLength = convert.length();
		for (int i = 0; i < strLength; ++i) // Converts everything to lowercase so that the input isn't case sensitive. This spits a compiler warning because it's signed/unsigned 
		{
			input += tolower(convert.at(i));
		}
		outVect.push_back(input);
	}

	return outVect; // By returning my vector this way, I can iterate my lines into a vector without the need of something at the end to indicate to the iterator "hey I'm done now"
}

void dataFileLoad(string &restName, string &currSym, string &admPass, string ver) // This is incredibly messy but it functions well.
{
	ifstream inDataFile;
	string input = ""; // This more or less exists so that unwanted data has somewhere to go.
	inDataFile.open("SimplePosData.dat", ios::in);
	while (input != "=") // Since I know exactly where everything is, I can just for loop through it until I get what I want. in this case, I want it to read until it finds the correct line and then start doing functions.
	{
		inDataFile >> input;
	}
	getline(inDataFile, restName); // Grab the rest of the line, it's the restaurant name.
	if (restName.length() > 0) // It's a safety thing to prevent out of range errors.
	{
		restName.erase(0, 1); // Because I'm using getline for this it sticks the space on as well, so we're just getting rid of that.
	}
	input = "";
	while (input != "=") // Doing this again until the next = so I can get to the next bit. While you are correct in that this is redundant code, if I move this to a function it'll start at the beginning again, which is a problem. Maybe there's a way to indicate a start point, but I couldn't figure it out.
	{
		inDataFile >> input;
	}
	inDataFile >> currSym; // Originally I designated this to a character. However, research shows me that there are currencies around the world that use more than one letter in their symbol (e.g. polish zloty uses zl, which is two characters). Crazy stuff!
	input = "";
	while (input != "=") // Doing this again until the next = so I can get to the next bit. While you are correct in that this is redundant code, if I move this to a function it'll start at the beginning again, which is a problem. Maybe there's a way to indicate a start point, but I couldn't figure it out.
	{
		inDataFile >> input;
	}
	while (input != "=") // Doing this again until the next = so I can get to the character. While you are correct in that this is redundant code, if I move this to a function it'll start at the beginning again, which is a problem. Maybe there's a way to indicate a start point, but I couldn't figure it out.
	{
		inDataFile >> input;
	}
	inDataFile >> admPass;

	if (inDataFile.eof()) // This indicates data was missing from the file and needs to be remade.
	{
		cout << "File did not read correctly. Resetting. Program will reboot." << endl; // Reboots afterwards to ensure the program has good data again.
		createFiles(ver);
		FileCheck("SimplePosData.dat", ver);
		FileCheck("SimplePosMenu.dat", ver);
		cout << "Press any key to continue...";
		_getch(); // Yes I know the value is ignored I don't care.
		exit(EXIT_FAILURE);
	}
	else
	{
		cout << "Main data file correctly read." << endl;
	}
}

void MenuFileLoad(vector<MenuItem> &menuItems) // This loads the menu list into memory. This will also be used to refresh the menu should the need arise.
{
	menuItems.clear(); // We want to make sure we're working with an empty vector here.
	ifstream inMenuFile;
	inMenuFile.open("SimplePosMenu.dat", ios::in);
	{
		int id = 1; // ID is assigned by a counter here. Item IDs are assigned in order starting at 1.
		string name;
		double price;
		while (!inMenuFile.eof()) // While the end of the file has not been reached.
		{
			inMenuFile >> name;
			inMenuFile >> price;
		
			menuItems.push_back(MenuItem::MenuItem()); // Creates the stack of menu items until the end of the file. Yes, this will fail if the data is tampered with.
			menuItems.back().LoadFromFile(id, price, name); // Fills in the last item in the list with the data we need. Since the last item of the vector will always be what we're working with here, this works.
			id += 1;
		}
	}
	inMenuFile.close();
	cout << "Menu data file correctly read." << endl;
}

void update(Status &statusTracker, string adminPass, vector<OrderItem> &orderItems, string currSymbol) // This line will clear the screen and then update with all the necessary information. This one is also important so it stays near the top.
{
	system("cls"); // See above when I call this function in Initialize() for why I hate this
	int status = statusTracker.GetStatus();
	statusTracker.PrintPassthroughTop(); // This prints any passthrough message at the top of the screen.
	switch (status)
	{
	case 0:
		statusTracker.UpdateStatus(Boot(statusTracker));
		break;
	case 1:
		if (!(statusTracker.orderTakerFresh()))
		{
			newOrder(statusTracker, orderItems);
			statusTracker.setOrderTakerFresh(true); // This little chunk makes sure the order isn't reset every time update() is called.
		}
		OrderTaker(statusTracker, orderItems, currSymbol);
		break;
	case 2:
		statusTracker.UpdateStatus(Exit(adminPass, statusTracker));
		break;
	}
	statusTracker.PrintPassthroughBottom(); // Prints a passthrough message above the command line if neccessary. 
}

int main()
{
	string versionNum = "1.0.0"; // I set this to an in-code variable at the top of main because it means I can change this easily everywhere I need to.

	string inString; // This string takes in raw user input.
	vector<string> cmdLine(0); // This vector will contain the command line for the program.
	string adminPass;
	string restaurantName;
	string currencySymbol;
	vector<MenuItem> menuItems(0);
	vector<OrderItem> orderItems(0);
	Status statusTracker;
	
	Initialize(versionNum); // This line initializes everything and gets all the data ready. This will need to be updated.
	dataFileLoad(restaurantName, currencySymbol, adminPass, versionNum);
	MenuFileLoad(menuItems);
	cout << "Loading complete. Press any key to continue..." << endl;
	_getch(); // How many times do I have to teach you this lesson old man
	while (true) // I want this program to continue until I tell it to stop. So yes, this infinite loop is intentional.
	{
		cmdLine.clear(); // Make sure our vector is empty.
		update(statusTracker, adminPass, orderItems, currencySymbol);
		cmdLine = readLine();
		executeCmd(statusTracker, cmdLine, orderItems, menuItems, adminPass);
		/* // The following are test lines that I've just comment blocked when they're not being used. No cause for alarm.

		cout << cmdLine.size() << endl;
		cout << cmdLine.empty() << endl;
		cout << cmdCode << endl;

		for (int i = 0; i < vectLength; ++i)
		{
			cout << cmdLine.at(i) << " ";
		}
		cout << endl;
		*/ 

	}
}