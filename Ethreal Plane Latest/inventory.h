#ifndef _INVENTORY_H_
#define _INVENTORY_H_

class Item;

class Consumable;

class Equipment;
class Weapon;
class Shield;
class BodyArmor;
class LegArmor;
class Ring;
class Necklace;

class HeroManager;

class Inventory
{
protected:
	
	/* Private Variables */

	/* Both created on the user access level. */
	int iTotalSlots_;
	int iTotalItems_;

	/* Created on programmer level */
	int iLastEmptySlot_;

	/* Private Methods */
	bool checkSlotsFull();
	
	void incrementTotalItems() {iTotalItems_++;}

public:
	Inventory();

	int getTotalItems() {return iTotalItems_;}
};

/* Item Group One will contain Consumables */
class ConsumableInventory: public Inventory
{
protected:
	Consumable *ciConsumables_;

	int ciTotalConsumables_;

public:
	ConsumableInventory() {};
	ConsumableInventory(int);

	/* General */
	bool addConsumables(Consumable);
	void dropConsumable(int);
	bool displayAllConsumables();
	void manageConsumables(HeroManager*);
	void dropAllConsumables();

	/* Gets */
	Consumable getConsumable(int x);
	int getTotalConsumables() {return ciTotalConsumables_;}
};

/* Item Group Two will contain Equipment */
class EquipmentInventory: public Inventory
{
protected:
	Weapon **eiWeapons_;
	Shield **eiShields_;
	BodyArmor **eiBodyArmors_;
	LegArmor **eiLegArmors_;
	Ring **eiRings_;
	Necklace **eiNecklaces_;

	int eiEquipmentRanges_[6];

	/* Private methods */
	void incrementTotalEquipment(int);
	void itemRemoved(int, int);

public:
	EquipmentInventory() {};
	EquipmentInventory(int);

	/* General */
	void dropItem(int);
	
	bool displayAllEquipment();
	
	void manageEquipment();
	void resetInventory();
	void displayEquipmentStats(int x);
	void equipItem(int x);
	int getItemType(int);
	void setEquipmentNumber(int &);

	/* Adds */
	bool addWeapon(Weapon*);
	bool addShield(Shield*);
	bool addBodyArmor(BodyArmor*);
	bool addLegArmor(LegArmor*);
	bool addRing(Ring*);
	bool addNecklace(Necklace*);

	void itemAdded(int);

	/* Gets */
	Weapon *getWeapon       (int x);
	Shield *getShield       (int x);
	BodyArmor *getBodyArmor (int x);
	LegArmor *getLegArmor   (int x);
	Ring *getRing           (int x);
	Necklace *getNecklace   (int x);

};

/* Item Group Three will contain Quest Items */
class QuestInventory: public Inventory
{
protected:
	//Item *qeItems;

public:
	QuestInventory() {}
};

/* Item Group Four will contain Junk */
class JunkInventory: public Inventory
{
protected:
public:
	JunkInventory() {}
};



#endif