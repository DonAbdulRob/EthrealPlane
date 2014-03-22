#include "allInventories.h"
#include "inventory.h"
#include "item.h"
#include "utilities.h"

#include <fstream>
#include <iostream>

AllInventories::AllInventories()
{
	fiConsumables_ = new ConsumableInventory(99);
	fiEquipment_ = new EquipmentInventory(99);
	fiQuestItems_ = new QuestInventory;
	fiJunkItems_ = new JunkInventory;

	//Consumable *newComsumables = new Comsumable(5);
}

FileItems::FileItems()
{
	// Initialize file location. Use relative path. (Was using absolute before!)
	fileLocation = "Reference\\ItemGenerator\\";
}

void FileItems::readAll()
{
	/* Call functions that will set the properties of every item */
	
	/* Quest Items */
	//createQuestItems();

	/* consumables */
	//createConsumables();
	
	/* Equipment */
	readWeapons();	
	readShields();
	readBodyArmors();
	readLegArmors();
	readRings();
	readNecklaces();
}

void FileItems::readWeapons()
{
	/* Variable Declarations */
	Weapon **w = new Weapon*[99];
	for (int i = 0; i < 99; i++)
		w[i] = new Weapon;

	int count = 0;

	ifstream f(fileLocation + "Weapons.txt");
	
	string contents = "";
	string header = "";
	int currentHero = 0;
	int len = 0;

	string name;
	string description;
	int value;
	int levelRequirement;
	int a[4];
	int d[2];

	while (!f.eof()) {

		getline(f, contents);
		len = contents.length();

		name = contents.substr(0, len);

		getline(f, contents);
		len = contents.length();

		description = contents.substr(0, len);

		getline(f, contents);
		len = contents.length();

		value = returnNumber(contents.substr(0, len));

		getline(f, contents);
		len = contents.length();

		levelRequirement = returnNumber(contents.substr(0, len));

		for (int i = 0; i < 4; i++) {
			getline(f, contents);
			len = contents.length();
		
			a[i] = returnNumber(contents.substr(0,len));
		}

		for (int i = 0; i < 2; i++) {
			getline(f, contents);
			len = contents.length();

			d[i] = returnNumber(contents.substr(0,len));
		}

		w[count]->setAll(name, description, value, levelRequirement, a, d);

		fiEquipment_->addWeapon(w[count]);

		count++;
	}

	f.close();
}

void FileItems::readShields()
{
	/* Variable Declarations */
	Shield **s = new Shield*[99];
	for (int i = 0; i < 99; i++)
		s[i] = new Shield;

	int count = 0;

	ifstream f(fileLocation + "Shields.txt");

	string contents = "";
	string header = "";
	int currentHero = 0;
	int len = 0;

	string name;
	string description;
	int value;
	int levelRequirement;
	int a[4];
	int dodge;
	int armor;

	while (!f.eof()) {

		getline(f, contents);
		len = contents.length();

		name = contents.substr(0, len);

		getline(f, contents);
		len = contents.length();

		description = contents.substr(0, len);

		getline(f, contents);
		len = contents.length();

		value = returnNumber(contents.substr(0, len));

		getline(f, contents);
		len = contents.length();

		levelRequirement = returnNumber(contents.substr(0, len));

		for (int i = 0; i < 4; i++) {
			getline(f, contents);
			len = contents.length();
		
			a[i] = returnNumber(contents.substr(0,len));
		}

		getline(f, contents);
		len = contents.length();

		dodge = returnNumber(contents.substr(0,len));

		getline(f, contents);
		len = contents.length();

		armor = returnNumber(contents.substr(0,len));

		s[count]->setAll(name, description, value, levelRequirement, a, dodge, armor);

		fiEquipment_->addShield(s[count]);

		count++;
	}

	f.close();
}

void FileItems::readBodyArmors()
{
	/* Variable Declarations */
	BodyArmor **ba = new BodyArmor*[99];
	for (int i = 0; i < 99; i++)
		ba[i] = new BodyArmor;

	int count = 0;

	ifstream f(fileLocation + "BodyArmors.txt");
	
	string contents = "";
	string header = "";
	int currentHero = 0;
	int len = 0;

	string name;
	string description;
	int value;
	int levelRequirement;
	int a[4];
	int armor;

	while (!f.eof()) {

		getline(f, contents);
		len = contents.length();

		name = contents.substr(0, len);

		getline(f, contents);
		len = contents.length();

		description = contents.substr(0, len);

		getline(f, contents);
		len = contents.length();

		value = returnNumber(contents.substr(0, len));

		getline(f, contents);
		len = contents.length();

		levelRequirement = returnNumber(contents.substr(0, len));

		for (int i = 0; i < 4; i++) {
			getline(f, contents);
			len = contents.length();
		
			a[i] = returnNumber(contents.substr(0,len));
		}

		getline(f, contents);
		len = contents.length();

		armor = returnNumber(contents.substr(0,len));

		ba[count]->setAll(name, description, value, levelRequirement, a, armor);

		fiEquipment_->addBodyArmor(ba[count]);

		count++;
	}

	f.close();
}

void FileItems::readLegArmors()
{
	/* Variable Declarations */
	LegArmor **la = new LegArmor*[99];
	for (int i = 0; i < 99; i++)
		la[i] = new LegArmor;

	int count = 0;

	ifstream f(fileLocation + "LegArmors.txt");
	
	string contents = "";
	string header = "";
	int currentHero = 0;
	int len = 0;

	string name;
	string description;
	int value;
	int levelRequirement;
	int a[4];
	int armor;

	while (!f.eof()) {

		getline(f, contents);
		len = contents.length();

		name = contents.substr(0, len);

		getline(f, contents);
		len = contents.length();

		description = contents.substr(0, len);

		getline(f, contents);
		len = contents.length();

		value = returnNumber(contents.substr(0, len));

		getline(f, contents);
		len = contents.length();

		levelRequirement = returnNumber(contents.substr(0, len));

		for (int i = 0; i < 4; i++) {
			getline(f, contents);
			len = contents.length();
		
			a[i] = returnNumber(contents.substr(0,len));
		}

		getline(f, contents);
		len = contents.length();

		armor = returnNumber(contents.substr(0,len));

		la[count]->setAll(name, description, value, levelRequirement, a, armor);

		fiEquipment_->addLegArmor(la[count]);

		count++;
	}

	f.close();
}

void FileItems::readRings()
{
	/* Variable Declarations */
	Ring **r = new Ring*[99];
	for (int i = 0; i < 99; i++)
		r[i] = new Ring;

	int count = 0;

	ifstream f(fileLocation + "Rings.txt");
	
	string contents = "";
	string header = "";
	int currentHero = 0;
	int len = 0;

	string name;
	string description;
	int value;
	int levelRequirement;
	int a[4];

	while (!f.eof()) {

		getline(f, contents);
		len = contents.length();

		name = contents.substr(0, len);

		getline(f, contents);
		len = contents.length();

		description = contents.substr(0, len);

		getline(f, contents);
		len = contents.length();

		value = returnNumber(contents.substr(0, len));

		getline(f, contents);
		len = contents.length();

		levelRequirement = returnNumber(contents.substr(0, len));

		for (int i = 0; i < 4; i++) {
			getline(f, contents);
			len = contents.length();
		
			a[i] = returnNumber(contents.substr(0,len));
		}

		r[count]->setAll(name, description, value, levelRequirement, a);

		fiEquipment_->addRing(r[count]);

		count++;
	}

	f.close();
}

void FileItems::readNecklaces()
{
	/* Variable Declarations */
	Necklace **n = new Necklace*[99];
	for (int i = 0; i < 99; i++)
		n[i] = new Necklace;

	int count = 0;

	ifstream f(fileLocation + "Necklaces.txt");
	
	string contents = "";
	string header = "";
	int currentHero = 0;
	int len = 0;

	string name;
	string description;
	int value;
	int levelRequirement;
	int a[4];

	while (!f.eof()) {

		getline(f, contents);
		len = contents.length();

		name = contents.substr(0, len);

		getline(f, contents);
		len = contents.length();

		description = contents.substr(0, len);

		getline(f, contents);
		len = contents.length();

		value = returnNumber(contents.substr(0, len));

		getline(f, contents);
		len = contents.length();

		levelRequirement = returnNumber(contents.substr(0, len));

		for (int i = 0; i < 4; i++) {
			getline(f, contents);
			len = contents.length();
		
			a[i] = returnNumber(contents.substr(0,len));
		}

		n[count]->setAll(name, description, value, levelRequirement, a);

		fiEquipment_->addNecklace(n[count]);

		count++;
	}

	f.close();
}


/* Creates Quest Items 
void World::createQuestItems()
{
	Item *qi = new Item;

	qi.setItemProperties("Sacred Fish", "This fish is an ancient relic for the god TEL -OK- MAHN. You must find a way to destroy this.", 0);
	wQuestItems_->addItem(qi);

	qi.setItemProperties("Black Wand", "This wand was once owned by the dark mage Regnok. Return this to his grave!", 0);
	wQuestItems_->addItem(qi);
}


void World::createConsumables()
{
	/***************************************************************************** 
	
	 Create Equipment -- Template = 
	 
	 setItemProperty - Name, descroption, value
	 setconsumableProperty - targetEnemy, targetHero, heal strength, damage strength
		attribute 1, attribute 2, attribute 3, attribute 4.

	*****************************************************************************

	Consumable c[99];

	c[1].setAll("Small Healing Potion", "This potion will heal a small amount of hit points.", 20, 0, 1, 30, 0, 0, 0, 0, 0);
	c[2].setAll("Medium Healing Potion", "This potion will heal a medium amount of hit points.", 300,0, 1, 400, 0, 0, 0, 0, 0);
	c[3].setAll("Large Healing Potion", "This potion will heal a large amount of hit points.", 1000, 0, 1, 4000, 0, 0, 0, 0, 0);

	//wConsumables_->addConsumables(c);
}

*/