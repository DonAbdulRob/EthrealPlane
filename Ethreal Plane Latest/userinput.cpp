#include "userinput.h"
#include "utilities.h"

#include <iostream>

UserInput::UserInput()
{
	iMessage_ = "";
	iErrorMessage_ = "";
}


MenuInput::MenuInput()
{
	int mi_ = 0;
	int miRangeUpperLimit_ = 0;
	int miErrorInputNumber_ = 0;
	bool miIncludeErrorNumber_ = 0;
}

StringInput::StringInput()
{
	si_ = "";
}

YesNoInput::YesNoInput()
{
	yni_ = '#';
}

/* Serves as a standard template for taking user instructions throughout the program */
void MenuInput::takeInput(string message, string errorMessage, int upperLimit, bool includeErrorNumber)
{
	/* Variable Declarations */
	bool keepLooping = 1;
	bool error1 = 0;
	string userChoice;

	/* Set class variables to the passed arguments */
	iMessage_ = message;
	iErrorMessage_ = errorMessage;
	miRangeUpperLimit_ = upperLimit;
	miErrorInputNumber_ = upperLimit + 1;
	miIncludeErrorNumber_ = includeErrorNumber;

	/* While keepLooping is true (true for first run) */
	while (keepLooping == 1) {

		/* Display argument menuOptions */
		cout << iMessage_;

		/* Include include error message is true then include it. */
		if (miIncludeErrorNumber_ == 1) {
			cout << "\n " << miErrorInputNumber_ << ".) Exit: ";
		}

		/* Take user input */
		cin >> userChoice;
		
		mi_ = returnNumber(userChoice);

		/* If the input isn't a number, then tell the user that they didn't enter a number.
			0 is the default for bad input. */
		if (mi_ == 0) {
			system("cls");
			cout << "You didn't enter a number.\n";
			error1 = 1;
		}
		else {
			error1 = 0;
		}

		/* If an error wasn't previously given, then continue execution */
		if (error1 == 0) {
			
			/* If the number is out of range then display the errorMessage and keep Looping.
				Or else end the loop. */
			if (miIncludeErrorNumber_ == 1) {
				if ((mi_ < 1) || (mi_ > miErrorInputNumber_)) {
					cout << iErrorMessage_ << endl;
					keepLooping = 1;
				}
				else {
					keepLooping = 0;
				}
			}
			else {
				if ((mi_ < 1) || (mi_ > miRangeUpperLimit_)) {
					cout << iErrorMessage_ << endl;
					keepLooping = 1;
				}
				else {
					keepLooping = 0;
				}
			}
		} /* End Error If */
	} /* End While */
}

/* Will perform profanity check on entered strings. */
void StringInput::takeInput(string message, string errorMessage)
{
	/* Variable Declarations */
	string input;
	string badWords[12];
	bool improper = 1; //0 - Clean Word, 1 - Found an improper Word, 

	/* Set class variables to the passed arguments */
	iMessage_ = message;
	iErrorMessage_ = errorMessage;

	badWords[0] = "damn";
	badWords[1] = "bitch";
	badWords[2] = "nigger";
	badWords[3] = "fucker";
	badWords[4] = "fuck";
	badWords[5] = "dick";
	badWords[6] = "cock";
	badWords[7] = "ass";
	badWords[8] = "cunt";
	badWords[9] = "Donald Sucks";
	badWords[10] = "I am better than Donald";
	badWords[11] = "vibitchagra.";
	
	while (improper == 1) {
		/* Reset improper to be evaluated */
		improper = 0;

		/* Display message and take input */
		cout << iMessage_;
		cin >> input;

		/* Compare the input with the bad word list */
		for (int i = 0; i < 11; i++) {
			if (input == badWords[i]) {
				cout << "Inproperiate Message Entered.";
				improper = 1;
				i = 12;
			}
		}
	}

	si_ = input;
}

/* Serves as a standard template for taking user instructions throughout the program */
void YesNoInput::takeInput(string message)
{
	/* Variable Declarations */
	char userChoice;
	bool keepLooping = 1;

	/* Set class variables to the passed arguments */
	iMessage_ = message;

	/* While keepLooping is true (true for first run) */
	while (keepLooping == 1) {

		/* Clear userChoice */
		userChoice = '#';

		/* Display argument "message" */
		cout << message;

		/* Take user input */
		cin >> userChoice;

		/* If the input is y or n then... */ 
		if ((userChoice == 'y') || (userChoice == 'n')) {

			/* set yni to userChoice */
			yni_ = userChoice;

			/* Break the loop */
			keepLooping = 0;
		}
		/* Else tell the user to enter y/n and keep looping. */
		else
			cout << "You didn't type the single character y or n. Please try again.\n";	
	}
}

