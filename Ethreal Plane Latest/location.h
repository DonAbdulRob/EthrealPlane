#ifndef _CLASSTOWN_H_
#define _CLASSTOWN_H_

#include <string>
#include <iostream>
using namespace std;

class EquipmentInventory;

class Location
{
protected:
	string tName_;
    string tWelcomeMessage_;
	int tXCoordinate_;
	int tYCoordinate_;
	int tInnRestFee_;
	EquipmentInventory *tShopEquipment_[10];
	
	void inn();

	//void createShopItems();
	//int tGuild_;
	//int tQuest_[5];
			
public:
    Location();

	/* General */
	void enterTown(int);
	void createTown(int, int, int, string, string);
	
	/* Variable Sets */
	
	/* Gets */
	string getTownWelcome() {return tWelcomeMessage_;}
	string getTownName()    {return tName_;}
	int getInnFee()         {return tInnRestFee_;}
	int getTXLoc()          {return tXCoordinate_;}
	int getTYLoc()          {return tYCoordinate_;}

};

#endif


