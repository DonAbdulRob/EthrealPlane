#include "location.h"

/* Constructors */

Location::Location()
{
	tName_ = "Undefined";
	tWelcomeMessage_ = "Undefined";
	tInnRestFee_ = 0;
	tXCoordinate_ = 0;
	tYCoordinate_ = 0;
}

/* Public Functions */

/* Initializes a town by setting it's value based on passed arguments */
void Location::createTown(int xCoordinate, int yCoordinate, int tInnRestFee, string tName, string tWelcomeMessage)
{
	  tXCoordinate_ = xCoordinate;
	  tYCoordinate_ = yCoordinate;
	  tInnRestFee_ = tInnRestFee;
	  tName_ = tName;
	  tWelcomeMessage_ = tWelcomeMessage;
}
