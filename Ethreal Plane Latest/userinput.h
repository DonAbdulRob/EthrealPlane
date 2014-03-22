#ifndef _USERINPUTTEMPLATE_H_
#define _USERINPUTTEMPLATE_H_

#include <string>
using namespace std;

class UserInput
{
protected:
	string iMessage_;
	string iErrorMessage_;
	
public:
	UserInput();

	//void takeInput() = 0;
};

class MenuInput : public UserInput
{
protected:
	int mi_;
	int miRangeUpperLimit_;
	int miErrorInputNumber_;
	bool miIncludeErrorNumber_;

public:
	MenuInput();

	void takeInput(string, string, int, bool);
	void convertInputProgrammerLevel() {mi_ -= 1;}
	int getInput() {return mi_;}
	
	int getErrorNumber() {return miRangeUpperLimit_ + 1;}
	bool inputIsErrorNumber() {if (mi_ == miErrorInputNumber_) return 1; else return 0; return 0;}
};

class StringInput : public UserInput
{
protected:
	string si_;
	
public:
	StringInput();

	void takeInput(string, string);
	string getInput() {return si_;}
};

class YesNoInput : public UserInput
{
protected:
	char yni_;

public:
	YesNoInput();

	void takeInput(string);
	bool isYes() {if (yni_ == 'y') return 1; else return 0; return 0;}
	char getInput() {return yni_;}
};


#endif

