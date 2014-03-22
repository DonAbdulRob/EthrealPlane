#ifndef _ITEM_H_
#define _ITEM_H_

/* Specify File includes and define namespace */
#include <istream>
#include <string>
using namespace std;

/* class forward declarations */
class Attributes;
class Resistances;
class Enchantment;

/***********************************************************************
Notes for item.h:

1.) Inheritance Structure

	1. Item
		A. Consumable
		C. Equipment
			a. Weapon
			b. 2nd Hand
			c. Body Armor
			d. Leg Armor
			e. Ring
			f. Ring 2
			g. Necklace
		D. Randon Junk
			a. Fish
			b. Ores

***********************************************************************/

class Item
{
protected:
	string name_;
	string description_;
	int value_;

public:
	Item();
	
	/* Set Item Properties */
	void setItemProperties(string, string, int);

	/* Gets */
	string getName        () {return name_;}
	string getDescription () {return description_;}
	
	int getValue        () {return value_;}  	
};

class Consumable: public Item
{
protected:
	/* Allowable targets */
	bool targetEnemy_;
	bool targetHero_;
	
	/* Effects */
	int heal_;
	int damage_;
	Attributes *attributes_;

public:
	Consumable();
	int setMiscProperties();

	/* General */
	void setConsumableProperties(bool, bool, int, int, int, int, int, int);
	void useConsumable();
	void displayInformation();
	void dropConsumable(int x);
	void setAll(string, string, int, bool, bool, int, int, int, int, int, int);

	/* Sets */
	int setHeal           (int x) {heal_ = x;}
	int setDamage         (int x) {damage_ = x;}

	/* Gets */
	int getHeal           () {return heal_;}
	int getDamage         () {return damage_;}
};

class Equipment: public Item
{
protected:
	/* Variables */
	string fullName_;
	string rarityName_;
	int levelRequirement_;
	int rarity_;
	int plusValue_;
	int socket_[2];

	Attributes *baseAttributes_;
	Attributes *modifiedAttributes_;

	/* Methods */
	void updateRarityModified();

public:
	Equipment();

	/* General */
	void setEquipmentProperties(int, int[]);
	void setSocketsAndRarity(int, int, int);
	bool checkCreated();
	void printEquipmentInformation();
	void setFullName();

	/* Sets */
	void setLevelRequirement (int x) {levelRequirement_ = x;}
	void setRarity           (int x) {rarity_ = x; updateRarityModified();}
	void setPlusValue        (int x) {plusValue_ = x;}

	void setSocket(int x, int y) {socket_[x] = y;} 
	
	void setBaseAttributes(Attributes*);
	void setModifiedAttributes(Attributes*);

	/* Gets */
	string getFullName() {return fullName_;}
	string getRarityName() {return rarityName_;}
	
	int getLevelRequirement () {return levelRequirement_;}
	int getRarity           () {return rarity_;}
	int getPlusValue        () {return plusValue_;}

	int getSocket(int x) {return socket_[x];}

	Attributes *getBaseAttributes();
	Attributes *getModifiedAttributes();

	/* Increments */
	void incrementPlusValue() {plusValue_++;}
	
	/* Decrements */
	void decrementPlusValue() {plusValue_--;}
};

class Weapon: public Equipment
{
protected:
	int minimumDamage_;
	int maximumDamage_;

public:
	Weapon();
	
	/* General */
	void setWeaponProperties(int, int);
	void printWeaponInformation();
	void setAll(string, string, int, int, int[], int[]);

	/* Gets */
	int getMinimumDamage() {return minimumDamage_;}
	int getMaximumDamage() {return maximumDamage_;}
};

class Shield: public Equipment
{
protected:
	int dodgeChance_;
	int physicalArmor_;

public:
	Shield();

	/* General */
	void setShieldProperties(int, int);
	void printShieldInformation();
	void setAll(string, string, int, int, int[], int, int);

	/* Gets */
	int getDodgeChance() {return dodgeChance_;}
	int getPhysicalArmor() {return physicalArmor_;}
};

class BodyArmor: public Equipment
{
protected:
	int physicalArmor_;

public:
	BodyArmor();
	
	/* General */
	void setBodyArmorProperties(int);
	void printBodyArmorInformation();
	void setAll(string, string, int, int, int[], int);

	/* Gets */
	int getPhysicalArmor() {return physicalArmor_;}

};

class LegArmor: public Equipment
{
protected:
	int physicalArmor_;

public:
	LegArmor();
	
	/* General */
	void setLegArmorProperties(int);
	void printLegArmorInformation();
	void setAll(string, string, int, int, int[], int);

	/* Gets */
	int getPhysicalArmor() {return physicalArmor_;}
};

class Ring: public Equipment
{
protected:
	Enchantment *enchantment_; /* Points to the enchantment the ring has */
	Enchantment *enchantment2_;

public:
	Ring() {};

	/* General */
	void printRingInformation();
	void setAll(string, string, int, int, int[]);

	/* Sets */
	void setRingEnchantment  (int);
	void setRingEnchantment2 (int);
};

class Necklace: public Equipment
{
protected:
	Enchantment *enchantment_;
	Enchantment *enchantment2_;
	
	Resistances *resistances_;

public:
    Necklace();

	void setAll(string, string, int, int, int[]);

	/* General */
	void setNecklaceEnchantment  (int);
	void setNecklaceEnchantment2 (int);
	void printNecklaceInformation();
};

class RandomJunk: public Item
{



};

#endif
