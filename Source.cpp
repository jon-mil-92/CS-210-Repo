// Jonathan Miller - CS210 - Project 3
#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

void CallProcedure(string pName);
int CallProcedureWithReturn(string pName);
int callIntFunc(string proc, string param);
string nCharString(char c, size_t n);
void displayMenu(char borderChar);
void getOption(int& userOption);
void displayHistogram(char frequencyChar);

// Menu option number constants.
const int PRINT_LIST = 1;
const int PRINT_ITEM = 2;
const int PRINT_HISTOGRAM = 3;
const int EXIT_PROG = 4;

int main()
{
	bool exitProgram = false; // Sentinel value for main program loop.
	int userOption = 0; // Set to 0 for safe entry into the main program loop.
	string fileName;
	string itemName;
	int itemFrequency;

	// Keep running the program until the user enters the number 4 for the menu option selection.
	while (!exitProgram) {
		displayMenu('*'); // Print the program menu for the four available options and an asterisk for the border character.
		getOption(userOption); // Get the menu option number selection from the user.

		switch (userOption) { // Switch through the valid option number selections from the user.
		case PRINT_LIST: // If the user entered 1.
			// Print the total inventory header with line dividers.
			cout << nCharString('-', 15) << endl;
			cout << "TOTAL INVENTORY" << endl;
			cout << nCharString('-', 15) << endl;

			// Use Python to get the inventory from the "items.txt" file and then print each item name and the number of times that item appears in the input file.
			CallProcedure("determineInventory");
			cout << endl;
			break;

		case PRINT_ITEM: // If the user entered 2.
			cout << "Please enter an item to get its frequency: ";
			cin >> itemName; // Get the item's name from the user.
			cout << endl;

			itemFrequency = callIntFunc("determineFrequency", itemName); // Use Python to get the frequency for the given item.

			// Display the user's entered item name followed by the amount of times it appears in the "items.txt" input file.
			if (itemFrequency == 1) { // Check if the item appears one time or multiple times to output the correct grammar.
				cout << itemName << " purchased " << itemFrequency << " time." << endl << endl;
			}
			else {
				cout << itemName << " purchased " << itemFrequency << " times." << endl << endl;
			}
			break;

		case PRINT_HISTOGRAM: // If the user entered 3.
			CallProcedure("output"); // Use Python to write each item and its frequency to the "frequency.dat" file.
			displayHistogram('*'); // Print the histogram to the console with an asterisk to represent the frequency of purchase for each item.
			cout << endl;
			break;

		case EXIT_PROG: // If the user entered 4.
			cout << "Program finished." << endl; // Ending program message.
			exitProgram = true; // Update the sentinel value to exit the main program loop.
			break;
		}
	}
	return 0;
}

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName) {
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	// Initialize the Python Interpreter
	Py_Initialize();
	// Load the Python module object
	PyObject* pModule = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	// Load the Python function object
	PyObject* pFunction = PyObject_GetAttrString(pModule, procname);
	// Call the specified Python function
	PyObject* pResult = PyObject_CallObject(pFunction, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	The return value from the Python function being called.
*/
int CallProcedureWithReturn(string pName) {
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	// Initialize the Python Interpreter
	Py_Initialize();
	// Load the Python module object
	PyObject* pModule = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	// Load the Python function object
	PyObject* pFunction = PyObject_GetAttrString(pModule, procname);
	// Call the specified Python function
	PyObject* pResult = PyObject_CallObject(pFunction, NULL);
	Py_Finalize();

	delete[] procname;

	return _PyLong_AsInt(pResult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	The return value from the Python function being called.
*/
int callIntFunc(string proc, string param) {
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/**
 * Returns a string of length n, each character a c.
 * For example, nCharString(5, '*') should return "*****"
 *
 * @param n string length, >=0
 * @return string of n c's
 */
string nCharString(char c, size_t n) {
	string charString = ""; // Initialize to empty string.

	// Build the character string for the given size n.
	for (int i = 0; i < n; ++i) {
		charString += c; // Append char c to the current character string.
	}

	return charString;
}

/**
* This function displays a menu for the program with four options for user selection.
* 
* @param borderChar - The character used to make the border of the menu.
*/
void displayMenu(char borderChar) {
	string option1 = " 1. Display purchased items with frequency of purchases. ";
	string option2 = " 2. Get the frequency of a specific item. ";
	string option3 = " 3. Display purchased item's frequency histogram. ";
	string option4 = " 4. Exit program. ";

	// The length of the longest menu option is the first option string.
	int maxOptionLength = option1.length();
	// The menu border length is the length of the first option string plus the two border characters that surround the option string.
	int menuBorderLength = maxOptionLength + 2;
	// The space between the end of the second option string and the right side of the menu border is the length of the longest option string minus the second option string.
	int option2SpacePadLen = maxOptionLength - option2.length();
	// The space between the end of the third option string and the right side of the menu border is the length of the longest option string minus the third option string.
	int option3SpacePadLen = maxOptionLength - option3.length();
	// The space between the end of the fourth option string and the right side of the menu border is the length of the longest option string minus the fourth option string.
	int option4SpacePadLen = maxOptionLength - option4.length();

	cout << nCharString(borderChar, menuBorderLength) << endl; // Top menu border.
	cout << nCharString(borderChar, 1) << option1 << nCharString(borderChar, 1) << endl;
	cout << nCharString(borderChar, 1) << option2 << nCharString(' ', option2SpacePadLen) << nCharString(borderChar, 1) << endl;
	cout << nCharString(borderChar, 1) << option3 << nCharString(' ', option3SpacePadLen) << nCharString(borderChar, 1) << endl;
	cout << nCharString(borderChar, 1) << option4 << nCharString(' ', option4SpacePadLen) << nCharString(borderChar, 1) << endl;
	cout << nCharString(borderChar, menuBorderLength) << endl << endl; // Bottom menu border.
}

/**
* This function prompts for the menu option number selection from the user, and then it validates whether it is in the menu option number range.
* If the user enters a number that is not in range, then an error message is displayed. The user must enter an integer.
*
* @param &userOption - The referenced user menu option number that will be used in the main program logic.
*/
void getOption(int& userOption) {
	bool validOption = false; // Set to false to enter input validation loop.

	while (!validOption) { // Keep getting user input until a valid integer is entered.

		cout << "Enter your selection as a number 1, 2, 3, or 4: ";
		cin >> userOption; // Get the menu option from the user.
		cout << endl;

		if ((userOption <= 4) && (userOption >= 1)) { // If the input is 1, 2, 3, or 4, stop the input loop.
			validOption = true;
		}
		else { // Otherwise, output an error message.
			cout << "ERROR: Please enter a valid option number." << endl << endl;
		}
	}
}

/**
* This function prints a formatted histogram to the console. The data for the histogram is read in from the frequency.dat file.
* 
* @param frequencyChar - The character used to represent the frequency in the histogram.
*/
void displayHistogram(char frequencyChar) {
	ifstream frequencyFileStream;
	string itemName;
	int itemFrequency;
	const string ITEM_HEADER_TEXT = "Items";
	const string FREQUENCY_HEADER_TEXT = "Purchase Frequency";
	HANDLE consoleTextColor = GetStdHandle(STD_OUTPUT_HANDLE); // Define an output buffer handle for the console color.

	// Get the max item name string length from Python. This value is used for histogram formatting.
	int maxItemNameLength = CallProcedureWithReturn("getMaxItemNameLength");
	// Get the max item purchase frequency from Python. This value is used for determining the length of the histogram header / data line divider.
	int maxFrequency = CallProcedureWithReturn("getMaxFrequency");

	// Check if the item histogram header text length is longer than the max item name string length.
	if (ITEM_HEADER_TEXT.length() > maxItemNameLength) {
		maxItemNameLength = ITEM_HEADER_TEXT.length(); // Update the max item name string length to the item header text length.
	}

	// Calculate and store the number of spaces between the item header text and purchase frequency header text divider string (" | ").
	string itemHeaderSpaces = nCharString(' ', maxItemNameLength - ITEM_HEADER_TEXT.length());

	// Print the histogram header.
	cout << "| " << ITEM_HEADER_TEXT << itemHeaderSpaces << " | " << FREQUENCY_HEADER_TEXT << endl;

	// Print a line divider between the histogram header text and the histogram data.
	if (FREQUENCY_HEADER_TEXT.length() > maxFrequency) {
		// Line divider length is the sum of the length for each part of the header text.
		cout << nCharString('-', (2 + ITEM_HEADER_TEXT.length() + itemHeaderSpaces.length() + 3 + FREQUENCY_HEADER_TEXT.length())) << endl;
	}
	else { // Extend the header / data line divider to the end of the max frequency.
		// Line divider length is the sum of the length for each part of the header text plus the max item frequency.
		cout << nCharString('-', (2 + ITEM_HEADER_TEXT.length() + itemHeaderSpaces.length() + 3 + maxFrequency)) << endl;
	}

	// Open the frequency.dat file for reading.
	frequencyFileStream.open("frequency.dat");

	// Print an error message if the file could not be opened.
	if (!frequencyFileStream.is_open()) {
	cout << "File could not be successfully opened." << endl;
	}
	else { // Process the frequency.dat file if it can be opened.

		// Read in the item name and frequency until the end of the file.
		while (!frequencyFileStream.eof() && !frequencyFileStream.fail()) {

			// Read in the item name and frequency from the current line.
			frequencyFileStream >> itemName >> itemFrequency;

			/**
			* Format the left side of the histogram.
			* The left side of the histogram has each item name with a dynamic number of spaces to align the start of the frequency characters for each item.
			*/
			cout << "| ";
			SetConsoleTextAttribute(consoleTextColor, 10); // Change the item name color to light green (color code 10).
			cout << itemName;
			SetConsoleTextAttribute(consoleTextColor, 15); // Change the text color back to white (color code 15) after printing the item name.
			cout << nCharString(' ', maxItemNameLength - itemName.length()) << " | ";

			// Print 'itemFrequency' amount of histogram characters.
			for (int i = 0; i < itemFrequency; ++i) {
				SetConsoleTextAttribute(consoleTextColor, 9); // Set the color of the histogram frequency characters to light blue (color code 9);
				cout << frequencyChar;
				SetConsoleTextAttribute(consoleTextColor, 15); // Change the text color back to white (color code 15) after printing the histogram frequency characters.
			}
			cout << endl;
		}
	}
	frequencyFileStream.close(); // Done reading from the file, so close the stream.
}