#ifndef _LIFE_H_
#define _LIFE_H_

#include <iostream>
#include <string>
using namespace std;

/* Class forward Declarations */
class FullEquipment;
class Weapon;
class Shield;
class BodyArmor;
class LegArmor;
class Ring;
class Necklace;

class EquipmentInventory;
class ConsumableInventory;
class QuestInventory;
class JunkInventory;

class MenuInput;

class LifeRepeatable;

/***********************************************************************
Notes for all function headers:

1.) Standard Function Order: 
	General - Get - Set - Increase - Decrease

Notes for life.h:

1.) Inheritance Structure

	1. Life
		A. PowerPlayer
			a. Opponnent
			b. PartyMember
				i. MainHero
		B. Summon

***********************************************************************/

/* Tier 1 Class */
class Life 
{
protected:
	string name_;
	bool created_;
	int level_;

	int currentHitPoints_;
	int currentManaPoints_;

	LifeRepeatable *baseLifeRepeatable_;
	LifeRepeatable *totalLifeRepeatable_;

public:
	Life();

	/* General */
	void restoreHitPoints();
	void restoreManaPoints();
	void fullHeal();

	/* Gets */
	string getName  () {return name_;}
	bool getCreated () {return created_;}
	int getLevel    () {return level_;}
	int getCurrentHitPoints  () {return currentHitPoints_;}
	int getCurrentManaPoints () {return currentManaPoints_;}
	
	LifeRepeatable *getBaseLifeRepeatable() {return baseLifeRepeatable_;}
	LifeRepeatable *getTotalLifeRepeatable() {return totalLifeRepeatable_;}

	/* Sets */
	void setName (string x) {name_ = x;}
	void setCreated (bool x) {created_ = x;}
	void setLevel   (int x) {level_ = x;}
	void setCurrentHitPoints  (int x) {currentHitPoints_ = x;}
	void setCurrentManaPoints (int x) {currentHitPoints_ = x;}
	void setBaseLifeRepeatable  (LifeRepeatable *newRepeatable) {baseLifeRepeatable_ = newRepeatable;}
	void setTotalLifeRepeatable (LifeRepeatable *newRepeatable) {totalLifeRepeatable_ = newRepeatable;}

	/* Increases */
	void incrementLevel() {level_++;}
	void increaseCurrentHitPoints(int x);
	void increaseCurrentManaPoints(int x);

	/* Decreases */
	void decreaseCurrentHitPoints  (int x) {currentHitPoints_ -= x;}
	void decreaseCurrentManaPoints (int x) {currentManaPoints_ -= x;}
};

/* Tier 2 Class - Power Players are players that are meant to fight. This class serves as a template mostly for inheritance purposes. */
class PowerPlayer: public Life
{
protected:
	/* Base Player Variables */
	string class_[3];
	string race_;
	int element_;

	/* Give them an extra set of stats to account for bonuses (Spells, equipment, consumables, etc. */
	LifeRepeatable *spellRepeatable_;
	LifeRepeatable *equipmentRepeatable_;

	/* Give them full equipment slots */
	FullEquipment *fullEquipment_;

	/* Give them a consumable and equipment inventory */
	ConsumableInventory *consumableInventory_;
	EquipmentInventory *equipmentInventory_;

public:
	PowerPlayer();

	/* General Purpose */
	void setPowerPlayerProperties (string, int, int, int, int);
	
	void calculateStats();
	void calculateBaseStats();
	void calculateEquipmentStats();
	void calculateTotalStats();
  
	void clearSlot(int x);

	int wearWeapon(Weapon*);
	int wearShield(Shield*);
	int wearBodyArmor(BodyArmor*);
	int wearLegArmor(LegArmor*);
	int wearRing(Ring*);
	int wearNecklace(Necklace*);
	
	/* Sets */
	void setClass (int x, string y) {class_[x] = y;}
	void setRace  (string x) {race_ = x;}
	void setElement (int x) {element_ = x;}

	void setFullEquipment (FullEquipment* x) {fullEquipment_ = x;}
	void setConsumableInventory (ConsumableInventory* x) {consumableInventory_ = x;}
	void setEquipmentInventory (EquipmentInventory* x) {equipmentInventory_ = x;}
	
	/* Gets */
	string getClass (int x) {return class_[x];}
	string getRace () {return race_;}
	int getElement () {return element_;}
	
	LifeRepeatable *getSpellRepeatable         () {return spellRepeatable_;}
	LifeRepeatable *getEquipmentRepeatable     () {return equipmentRepeatable_;}
	FullEquipment* getFullEquipment            () {return fullEquipment_;}
	EquipmentInventory* getEquipmentInventory () {return equipmentInventory_;}
	ConsumableInventory* getConsumableInventory () {return consumableInventory_;}
};

/* Tier 3 Class */
class PartyMember: public PowerPlayer
{
protected:
	int experience_;
	int statPoints_;

public:
	PartyMember();

	/* General Purpose */
	string getSaveInformation ();
	void printStats();
	void manageEquipment();
	//void levelupIncreaseStats();

	/* Gets */
	int getExperience () {return experience_;}
	int getStatPoints () {return statPoints_;}

	/* Sets */
	void setExperience (int x) {experience_ = x;}
	void setStatPoints (int x) {statPoints_ = x;}

	/* Increases */
	void increaseExperience (int x) {experience_ += x;}
	void increaseStatPoints (int x) {statPoints_ += x;}
};

/* Tier 4 Class */
class MainHero: public PartyMember
{
protected:
	int gold_;
	int coordinate_[2]; /* x = 0, y = 1 */
	int respawnCoordinates_[2];
	int activeQuest_;
	int mapZoom_;

	/* Give main hero a group 3,4 inventories */
	QuestInventory *questInventory_;
	JunkInventory *junkInventory_;

public:
	MainHero();
	
	/* General Purpose */
	string getSaveInformation2();

	void moveHero(int []);
	void hasDied();
	void activateCheats();
	void printMainStats();
	void respawn();

	/* Sets */
	void setGold (int x) {gold_ = x;}
	void setMapZoom(int x) {mapZoom_ = x;}
	void setXCoordinate(int x) {coordinate_[0];}
	void setYCoordinate(int x) {coordinate_[1];}
	void setCoordinates(int x, int y) {coordinate_[0] = x; coordinate_[1] = y;}
	void setRespawnCoordinates(int x, int y) {respawnCoordinates_[0] = x; respawnCoordinates_[1] = y;}

	void setQuestInventory(QuestInventory* x) {questInventory_ = x;}
	void setJunkInventory(JunkInventory* x) {junkInventory_ = x;}

	/* Gets */
	int getGold         () {return gold_;}
	int getXCoordinate  () {return coordinate_[0];}
	int getYCoordinate  () {return coordinate_[1];}
	int *getCoordinates () {return coordinate_;}
	int getMapZoom      () {return mapZoom_;}
	int *getRespawnCoordinates() {return coordinate_;}
	int getXRespawnCoordinate() {return respawnCoordinates_[0];}
	int getYRespawnCoordinate() {return respawnCoordinates_[1];}

	QuestInventory* getQuestInventory () {return questInventory_;}
	JunkInventory* getJunkInventory   () {return junkInventory_;}

	/* Increases */
	void increaseGold     (int x) {gold_ = gold_ + x;}

	/* Decreases */
	void decreaseGold (int x) {gold_ = gold_ - x;}
};

/* Tier 3 Class */
class Opponent: public PowerPlayer
{
protected:
	int gold_;
	int experience_;

public:
	Opponent();

	/* General Purpose Function */
	void generateRandomOpponent(int);
	void modifyStrength(double);

	/* Gets */
	int getGold ()       {return gold_;}
	int getExperience () {return experience_;}
	
	/* Sets */
	void setGold       (int x) {gold_ = x;}
	void setExperience (int x) {experience_ = x;}

	/* Increases */
	void increaseGold (int x) {gold_ += x;}

};

/* Tier 2 Class */
class Summon: public Life
{
protected:
	int turnLifeTime_;

public:
	Summon();

	/* Sets */
	void setTurnLifeTime(int x) {turnLifeTime_ = x;}

	/* Gets */
	int getTurnLifeTime() {return turnLifeTime_;}

	/* Decreases */
	void decreaseTurnLifeTime() {turnLifeTime_ -= 1;}
};
		
#endif