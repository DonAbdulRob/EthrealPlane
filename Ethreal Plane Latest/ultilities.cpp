#include "utilities.h"

#include <iostream>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int returnNumber(string x)
{
	int intReturn;

	intReturn = atoi(x.c_str());

	return intReturn;	
}

string returnString(int x)
{
	string s;
	stringstream out;

	out << x;
	s = out.str();

	return s;
}

