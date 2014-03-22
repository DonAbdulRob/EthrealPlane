#include "inventory.h"
#include "world.h"
#include "item.h"
#include "fullEquipment.h"
#include "equipmentSlots.h"
#include "heroManager.h"
#include "utilities.h"

#include <iostream>
#include <string>
using namespace std;

/*******************
    Constructors
*******************/

Inventory::Inventory()
{
	/* Set total Slots to 1 */
	iTotalSlots_ = 1;

	/* Set the total amount of items to 0 */
	iTotalItems_ = 0;

	/* Set last empty slot to 0 */
	iLastEmptySlot_ = 0;
}

ConsumableInventory::ConsumableInventory(int totalSlots)
{
	iTotalSlots_ = totalSlots;

	ciConsumables_ = new Consumable[totalSlots];

	ciTotalConsumables_ = 0;
}

EquipmentInventory::EquipmentInventory(int totalSlots)
{
    /* Set total Number of slots */
    iTotalSlots_ = totalSlots;

	eiWeapons_ = new Weapon*[totalSlots];
	eiShields_ = new Shield*[totalSlots];
	eiBodyArmors_ = new BodyArmor*[totalSlots];
	eiLegArmors_ = new LegArmor*[totalSlots];
	eiRings_ = new Ring*[totalSlots];
	eiNecklaces_ = new Necklace*[totalSlots];

	for (int i = 0; i < totalSlots; i++) {
		eiWeapons_[i] = new Weapon;
		eiShields_[i] = new Shield;
		eiBodyArmors_[i] = new BodyArmor;
		eiLegArmors_[i] = new LegArmor;
		eiRings_[i] = new Ring;
		eiNecklaces_[i] = new Necklace;
	}

	/* Initialize totals to 0 */
	for (int i = 0; i < 6; i++) {
		eiEquipmentRanges_[i] = 0;
	}
} 

/*************
    Methods 
**************/

bool Inventory::checkSlotsFull()
{
	/* No Variable Declarations */

	/* If there are 20 items, then return 1 for full */
	if (iTotalItems_ == iTotalSlots_)
		return 1;
	/* Else there are less than 20 and return empty. */
	else
		return 0;
}

/* This will return a Consumable */
Consumable ConsumableInventory::getConsumable(int x)
{
	 return ciConsumables_[x];
}

/* Adds a consumables */
bool ConsumableInventory::addConsumables(Consumable nc)
{
	/* Variable Declarations */
	bool slotsAreFull = 0;
	int itemPosition = 0;

	/* Check to see if you totalItems == totalSlots */
	slotsAreFull = checkSlotsFull();

	if (slotsAreFull == 1)
		/* Return 1 since the item wasn't stored */
		return 1;
	else {
		/* Store the items */
		ciConsumables_[ciTotalConsumables_] = nc;
		
		/* Display message that the item was stored */
		cout << "Your item was successfully put into bag1!!\n";

		/* Diplay new inventory */
		displayAllConsumables();

		/* Give the user a chance to take all the information in. Then clear */
		cout << endl; system("pause"); system("cls");

		/* Increase total item of equipmentType by 1 */
		ciTotalConsumables_++;

		/* Increase total items */
		incrementTotalItems();
	}

	/* Return 0 since the item was stored */
	return 0;
}

/* Displays all consumables */
bool ConsumableInventory::displayAllConsumables()
{
	/* Variable Declarations */
	int menuCount = 1;

	/* Display all items */	
	cout << "Consumable Inventory Items: ";

	/* Weapons */
	for (int j = 0; j < ciTotalConsumables_; j++) {
		if ((ciConsumables_[j].getName() != "Undefined") && (ciConsumables_[j].getName() != "")) {
			cout << "\n " << menuCount << ".) " << ciConsumables_[j].getName();
			menuCount++;
		}
	}
	
	/* If there are no items, then display a message that there are no items */
	if (menuCount == 1) {
		cout << " None!\n --There are no consumables in this Consumable Inventory!!!--\n\n";
		system("pause");
		return 0;
	}
	else {
		cout << endl;
	}

	return 1;
}

/* This drops all consumables */
void ConsumableInventory::dropAllConsumables()
{
	ciConsumables_ = new Consumable[iTotalSlots_];
	ciTotalConsumables_ = 0;

	iTotalItems_ = 0;
	ciTotalConsumables_ = 0;
}

/* This drops a single consumable */
void ConsumableInventory::dropConsumable(int x)
{
	/* Shift all consumables down. Make sure that we don't go out of bounds by lowering the toalSlots by 1. 
	     This makes sense because we don't need to set the last item to 1 more item than we have total. */
	
	ciTotalConsumables_--;
	iTotalItems_--;

	for (int i = x; x < ciTotalConsumables_; i++)
		ciConsumables_[x] = ciConsumables_[x+1];
}

/* Drops all equipment */
void EquipmentInventory::resetInventory()
{
    delete [] eiWeapons_;
	delete [] eiShields_;
	delete [] eiBodyArmors_;
	delete [] eiLegArmors_;
	delete [] eiRings_;
	delete [] eiNecklaces_;

	/* Set the pointers to be an array of type ??? -- ???[totalSlots] */
    Weapon *eiWeapons_ = new Weapon[iTotalSlots_];
    Shield *eiShields_ = new Shield[iTotalSlots_];
    BodyArmor *eiBodyArmors_ = new BodyArmor[iTotalSlots_];
    LegArmor *eiLegArmors_ = new LegArmor[iTotalSlots_];
    Ring *eiRings_ = new Ring[iTotalSlots_];
    Necklace *eiNecklaces_ = new Necklace[iTotalSlots_];

	/* Initialize totals to 0 */
	for (int i = 0; i < 6; i++) {
		eiEquipmentRanges_[i] = 0;
	}
}

/* Displays all equipment */
bool EquipmentInventory::displayAllEquipment()
{
	/* Variable Declarations */
	int menuCount = 1;

	/* Display all items */	
	cout << "Here is your Equipment Inventory:";

	/* Weapons */
	for (int j = 0; j < iTotalItems_; j++) {
		if (eiWeapons_[j]->getName() != "Undefined") {
			cout << "\n " << menuCount << ".) " << eiWeapons_[j]->getFullName();
			menuCount++;
		}
	}
	/* Shield */
	for (int j = 0; j < iTotalItems_; j++) {
		if (eiShields_[j]->getName() != "Undefined") {
			cout << "\n " << menuCount << ".) " << eiShields_[j]->getFullName();
			menuCount++;
		}
	}
	/* Body Armor */
	for (int j = 0; j < iTotalItems_; j++) {
		if (eiBodyArmors_[j]->getName() != "Undefined") {
			cout << "\n " << menuCount << ".) " << eiBodyArmors_[j]->getFullName();
			menuCount++;
		}
	}
	/* Leg Armor */
	for (int j = 0; j < iTotalItems_; j++) {
		if (eiLegArmors_[j]->getName() != "Undefined") {
			cout << "\n " << menuCount << ".) " << eiLegArmors_[j]->getFullName();
			menuCount++;
		}
	}
	/* Ring */
	for (int j = 0; j < iTotalItems_; j++) {
		if (eiRings_[j]->getName() != "Undefined") {
			cout << "\n " << menuCount << ".) " << eiRings_[j]->getFullName();
			menuCount++;
		}
	}
	/* Neckalce */
	for (int j = 0; j < iTotalItems_; j++) {
		if (eiNecklaces_[j]->getName() != "Undefined") {
			cout << "\n " << menuCount << ".) " << eiNecklaces_[j]->getFullName();
			menuCount++;
		}
	}

	/* If there are no items, then display a message that there are no items */
	if (menuCount == 1) {
		cout << " None!\n --There is no Equipment in this Equipment Inventory!!!--\n\n";
		system("pause");
		return 0;
	}
	else {
		cout << "\n " << menuCount << ".) Exit";
	}

	return 1;
}

/* Displays every slot */
void EquipmentInventory::displayEquipmentStats(int userChoice)
{
	/* Put on programmers level */
	int x = userChoice - 1;
	int t = x;

	if (x < eiEquipmentRanges_[0]) {
		eiWeapons_[t]->printWeaponInformation();
		eiWeapons_[t]->printEquipmentInformation();
	}
	else if (x < eiEquipmentRanges_[1]) {
		t -= eiEquipmentRanges_[0];
		eiShields_[t]->printShieldInformation();
		eiShields_[t]->printEquipmentInformation();
	}
	else if (x < eiEquipmentRanges_[2]) {
		t -= eiEquipmentRanges_[1];
		eiBodyArmors_[t]->printBodyArmorInformation();
		eiBodyArmors_[t]->printEquipmentInformation();
	}	
	else if (x < eiEquipmentRanges_[3]) {
		t -= eiEquipmentRanges_[2];	
		eiLegArmors_[t]->printLegArmorInformation();
		eiLegArmors_[t]->printEquipmentInformation();
	}
	else if (x < eiEquipmentRanges_[4]) {
		t -= eiEquipmentRanges_[3];
		eiRings_[t]->printRingInformation();
		eiRings_[t]->printEquipmentInformation();
	}
	else if (x < eiEquipmentRanges_[5]) {
		t -= eiEquipmentRanges_[4];
		eiNecklaces_[t]->printNecklaceInformation();
		eiNecklaces_[t]->printEquipmentInformation();
	}
}

/* Takes the slot of the item to drop */
void EquipmentInventory::dropItem(int userChoice)
{
	/* Variable Declaration */
	int useGroup = 0;
	int itemType;
	Weapon *w = new Weapon;
	Shield *s = new Shield;
	BodyArmor *b = new BodyArmor;
	LegArmor *l = new LegArmor;
	Ring *r = new Ring;
	Necklace *n = new Necklace;

	/* Set the item type */
	itemType = getItemType(userChoice);

	/* Set the remove number to the programmer-array access level */
	setEquipmentNumber(userChoice);

	/* We drop the item by setting the slot to null. */ 
	switch (itemType) {
		case 0:
			/* If a weapon, then set the weapon to an empty weapon */
			eiWeapons_[userChoice] = w;

			/* Break switch statement */
			break;
		case 1:
			eiShields_[userChoice] = s;
			break;
		case 2:
			eiBodyArmors_[userChoice] = b;
			break;
		case 3:
			eiLegArmors_[userChoice] = l;
			break;
		case 4:
			eiRings_[userChoice] = r;
			break;
		case 5:
			eiNecklaces_[userChoice] = n;
			break;
		default:
			cout << "No item was specified to be dropped.";
			break;
	}

	/* Then we decrease the total number of weapons */
	itemRemoved(itemType, userChoice);

	/* Decrease total items */
	iTotalItems_--;
}

/* Decreases totals of equipment */
void EquipmentInventory::itemRemoved(int itemType, int removeNumber)
{
	/* Shift all item ranges down for the item and everything above. */
	for (int i = 6; i > itemType; i--) {
		eiEquipmentRanges_[i]--;
	}

	/* Keep the array COMPACT. Remove gaps. */
	switch (itemType) {
		case 0:
			for (int i = removeNumber; i < eiEquipmentRanges_[0] - 1; i++)
				eiWeapons_[i] = eiWeapons_[i+1];
			break;
		case 1:
			for (int i = removeNumber; i < eiEquipmentRanges_[1] - 1; i++)
				eiShields_[i] = eiShields_[i+1];
			break;
		case 2:
			for (int i = removeNumber; i < eiEquipmentRanges_[2] - 1; i++)
				eiBodyArmors_[i] = eiBodyArmors_[i+1];
			break;
		case 3:
			for (int i = removeNumber; i < eiEquipmentRanges_[3] - 1; i++)
				eiLegArmors_[i] = eiLegArmors_[i+1];
			break;
		case 4:
			for (int i = removeNumber; i < eiEquipmentRanges_[4] - 1; i++)
				eiRings_[i] = eiRings_[i+1];
			break;
		case 5:
			for (int i = removeNumber; i < eiEquipmentRanges_[5] - 1; i++)
				eiNecklaces_[i] = eiNecklaces_[i+1];
			break;
		default:
			cout << "HORRIBLE ERRORS!\n";
			system("pause");
			break;
	}
}

/* Increasees totals of equipment */
void EquipmentInventory::itemAdded(int itemType)
{
	/* Shift all items up in the list */
	for (int i = itemType; i < 6; i++) {
		eiEquipmentRanges_[i]++;
	}

	/* Increase total items */
	iTotalItems_++;
}

int EquipmentInventory::getItemType(int x)
{
	for (int i = 0; i < 6; i++) {
		if (x <= eiEquipmentRanges_[i]) {
			return i;
		}
	}
	return 0;
}

void EquipmentInventory::setEquipmentNumber(int &x)
{
	/* Set to array access level... */
	x = x - 1;

	/* Evaluate all equipment ranges */
	for (int i = 0; i < 6; i++) {
		
		/* If x is greater than the total items in that range, then... */
		if (x > eiEquipmentRanges_[i]) {
			
			/* Decrease x so that it can access the array element of the proper item array */
			x -= eiEquipmentRanges_[i];
			
			/* Break loop */
			i = 6;
		}
	}
}

/* Adds items to EI */
bool EquipmentInventory::addWeapon(Weapon *newWeapon)
{
	/* Variable Declarations */
	bool success = 0;

	/* Store weapon into first empty slot */
	for (int i = 0; i < iTotalSlots_; i++) {

		/* Get first available weapon array location and store the item there */
		if (eiWeapons_[i]->getName() == "Undefined") {

			/* Add the item to the items array. */
			eiWeapons_[i] = newWeapon;

			/* Adjust item totals. */
			itemAdded(0);

			/* Set that the item was sucessfully stored */
			success = 1;

			/* End the loop */
			i = iTotalSlots_;
		}
	}

	/* Return success */
	return success;
}
bool EquipmentInventory::addShield(Shield *newShield)
{
	bool success = 0;
	for (int i = 0; i < iTotalSlots_; i++) {
		if (eiShields_[i]->getName() == "Undefined") { eiShields_[i] = newShield; itemAdded(1); success = 1; }
	} return success;
}
bool EquipmentInventory::addLegArmor(LegArmor *newLegArmor)
{
	bool success = 0;
	for (int i = 0; i < iTotalSlots_; i++) {
		if (eiLegArmors_[i]->getName() == "Undefined") { eiLegArmors_[i] = newLegArmor; itemAdded(2); success = 1; }
	} return success;
}
bool EquipmentInventory::addBodyArmor(BodyArmor *newBodyArmor)
{
	bool success = 0;
	for (int i = 0; i < iTotalSlots_; i++) {
		if (eiBodyArmors_[i]->getName() == "Undefined") { eiBodyArmors_[i] = newBodyArmor; itemAdded(3); success = 1; }
	} return success;
}
bool EquipmentInventory::addRing(Ring *newRing)
{
	bool success = 0;
	for (int i = 0; i < iTotalSlots_; i++) {
		if (eiRings_[i]->getName() == "Undefined") { eiRings_[i] = newRing; itemAdded(4); success = 1; }
	} return success;
}
bool EquipmentInventory::addNecklace(Necklace *newNecklace)
{
	bool success = 0;
	for (int i = 0; i < iTotalSlots_; i++) {
		if (eiNecklaces_[i]->getName() == "Undefined") { eiNecklaces_[i] = newNecklace; itemAdded(5); success = 1; }
	} return success;
}

/* Gets */
Weapon *EquipmentInventory::getWeapon(int x)
{
	return eiWeapons_[x];
}
Shield *EquipmentInventory::getShield(int x)
{
	return eiShields_[x];
}
BodyArmor *EquipmentInventory::getBodyArmor(int x)
{
	return eiBodyArmors_[x];
}
LegArmor *EquipmentInventory::getLegArmor(int x)
{
	return eiLegArmors_[x];
}
Ring *EquipmentInventory::getRing(int x)
{
	return eiRings_[x];
}
Necklace *EquipmentInventory::getNecklace(int x)
{
	return eiNecklaces_[x];
}

/*

Breakdown of how the inventory works.

You have 6 arrays of items. You can add items or remove them from this array at will.
You can also access these arrayss at will. The EI is simply a collection of these with added
functionality that allows you to moniter them AND keep the arrays compact.
In fact, I'll probably seperate them out later.

class equipmentCollection.

Anyway, the added functionality is being able to add or remove items in a list style.
This list style makes sure that you can only have a certain total of items. All of this
is monitered with eiEquipmentRanges.

Another added feature of using the inventory class is that every new item is assigned a slot number.
This is the slot that the item will take up. This will allow items to be displayed in the order that you
recieved them leading to a more shuffled display of items.

*/

/* Shift all of the items in that equipment down */


	/*

	/* Set the pointers to be an array of type ??? -- ???[totalSlots]
	
	Goal = make an Array of pointers.
	
	[] of *


	

	for (int i = 0; i < totalSlots; i++) {
		eiWeapons_[i] = new Weapon;
	}

	for (int j = 0; j < totalSlots; j++) {
		for (int k = 0; k < totalSlots; k++) {
			eiWeapons_[j][k] = new Weapon[totalSlots];
		}
	}

	system("pause");

	eiWeapons_ = new Weapon;

	for (int i = 0; i < totalSlots; i++) {
		eiWeapons_[i] = new Weapon[totalSlots]; //[totalSlots]
	}
	*/
	/*
	

	*eiWeapons_ = new Weapon[1][20];
	*eiShields_ = new Shield*;
	*eiBodyArmors_ = new BodyArmor*;
	*eiLegArmors_ = new LegArmor*;
	*eiRings_ = new Ring*;
	*eiNecklaces_ = new Necklace*;

    *eiWeapons_ = new Weapon[totalSlots];
    *eiShields_ = new Shield[totalSlots];
    *eiBodyArmors_ = new BodyArmor[totalSlots];
    *eiLegArmors_ = new LegArmor[totalSlots];
    *eiRings_ = new Ring[totalSlots];
    *eiNecklaces_ = new Necklace[totalSlots];
	*/
	/*
	The goal is to be able to do

	eiWeapons_[5]->

	*eiWeapons_[5].
	*/