/* Declare files to include and the namespace */

#include "life.h"
#include "world.h"
#include "fullEquipment.h"
#include "equipmentSlots.h"
#include "item.h"
#include "inventory.h"
#include "userinput.h"
#include "resistances.h"
#include "elementaldamages.h"
#include "utilities.h"
#include "attributes.h"
#include "lifeRepeatable.h"
#include "states.h"

/*************
Constructors
*************/

/* Life Constructor */
Life::Life()
{
	name_ = "Undefined";
	created_ = 0;
	level_ = 1;
	
	currentHitPoints_ = 0;
	currentHitPoints_ = 0;

	baseLifeRepeatable_ = new LifeRepeatable;
	totalLifeRepeatable_ = new LifeRepeatable;
}

PowerPlayer::PowerPlayer()
{
	for (int i = 0; i < 3; i++) {
		class_[i] = "Undefined";
	}
	
	race_ = "None";
	element_ = 0;

	spellRepeatable_ = new LifeRepeatable;
	equipmentRepeatable_ = new LifeRepeatable;
	fullEquipment_ = new FullEquipment;
	consumableInventory_ = new ConsumableInventory(20);
	equipmentInventory_ = new EquipmentInventory(20);
}

PartyMember::PartyMember()
{
	experience_ = 0;
	statPoints_ = 5;
}

MainHero::MainHero()
{
	created_ = 1;

	gold_ = 100;
	coordinate_[0] = 100;
	coordinate_[1] = 100;
	respawnCoordinates_[0] = 100;
	respawnCoordinates_[1] = 100;

	activeQuest_ = 0;
	mapZoom_ = 30;
	questInventory_ = new QuestInventory();
	junkInventory_ = new JunkInventory();
}

Opponent::Opponent()
{
	gold_ = 0;
	experience_ = 0;
}

Summon::Summon()
{
	turnLifeTime_ = 0;
}

/*****************
Public Functions
*****************/

void Life::restoreHitPoints()
{
	currentHitPoints_ = totalLifeRepeatable_->getMaximumHitPoints();
}

void Life::restoreManaPoints()
{
	currentManaPoints_ = totalLifeRepeatable_->getMaximumManaPoints();
}

void Life::fullHeal()
{
	restoreHitPoints();
	restoreManaPoints();

}

void Life::increaseCurrentHitPoints(int x)
{
	currentManaPoints_ += x; 
	
	if (currentManaPoints_ > totalLifeRepeatable_->getMaximumManaPoints()) 
		currentManaPoints_ = totalLifeRepeatable_->getMaximumManaPoints(); 
}

void Life::increaseCurrentManaPoints(int x)
{
	currentHitPoints_ += x;

	if (currentHitPoints_ > totalLifeRepeatable_->getMaximumHitPoints())
		currentHitPoints_ = totalLifeRepeatable_->getMaximumHitPoints();
}

void PowerPlayer::calculateStats()
{
	calculateBaseStats();
	calculateEquipmentStats();
}

void PowerPlayer::calculateBaseStats()
{
	/* No Variable Declarations */

	/* Reset the equipment repeatable */
	delete baseLifeRepeatable_;
	baseLifeRepeatable_ = new LifeRepeatable;

	/* Set base damage from stats. */
	if (class_[0] == "Warrior") {
		baseLifeRepeatable_->getAttributes()->setAttribute(0, 3*level_);
		baseLifeRepeatable_->getAttributes()->setAttribute(1, 1*level_);
		baseLifeRepeatable_->getAttributes()->setAttribute(2, 2*level_);
		baseLifeRepeatable_->getAttributes()->setAttribute(3, 1*level_);
		
		baseLifeRepeatable_->setCriticalHitChance(3);
		baseLifeRepeatable_->setDoubleStrikeChance(3);
		baseLifeRepeatable_->setDivineStrikeChance(0);
		baseLifeRepeatable_->setDodgeChance(1);

		baseLifeRepeatable_->setPhysicalDamageMinimum(int(baseLifeRepeatable_->getAttributes()->getAttribute(0) * .5 + 1));
		baseLifeRepeatable_->setPhysicalDamageMaximum(int(baseLifeRepeatable_->getAttributes()->getAttribute(0) * 1.5 + 3));
	}
	else if (class_[0] == "Mage") {
	  	baseLifeRepeatable_->getAttributes()->setAttribute(0, 3*level_);
		baseLifeRepeatable_->getAttributes()->setAttribute(1, 3*level_);
		baseLifeRepeatable_->getAttributes()->setAttribute(2, 3*level_);
		baseLifeRepeatable_->getAttributes()->setAttribute(3, 1*level_);

		baseLifeRepeatable_->setCriticalHitChance(1);
		baseLifeRepeatable_->setDoubleStrikeChance(1);
		baseLifeRepeatable_->setDivineStrikeChance(0);
		baseLifeRepeatable_->setDodgeChance(1);
		
		baseLifeRepeatable_->setPhysicalDamageMinimum(int(baseLifeRepeatable_->getAttributes()->getAttribute(1) * .5 + 1));
		baseLifeRepeatable_->setPhysicalDamageMaximum(int(baseLifeRepeatable_->getAttributes()->getAttribute(1) * 1.5 + 3));
		
	}
	else if (class_[0] == "Rouge") {
		baseLifeRepeatable_->getAttributes()->setAttribute(0, 2*level_);
		baseLifeRepeatable_->getAttributes()->setAttribute(1, 1*level_);
		baseLifeRepeatable_->getAttributes()->setAttribute(2, 3*level_);
		baseLifeRepeatable_->getAttributes()->setAttribute(3, 1*level_);
		
		baseLifeRepeatable_->setCriticalHitChance(10);
		baseLifeRepeatable_->setDoubleStrikeChance(10);
		baseLifeRepeatable_->setDivineStrikeChance(2);
		baseLifeRepeatable_->setDodgeChance(5);

		baseLifeRepeatable_->setPhysicalDamageMinimum(int(baseLifeRepeatable_->getAttributes()->getAttribute(2) * .5 + 1));
		baseLifeRepeatable_->setPhysicalDamageMaximum(int(baseLifeRepeatable_->getAttributes()->getAttribute(2) * 1.5 + 3));
	}

	/* Set base Health and Mana from attributes. */
	baseLifeRepeatable_->setMaximumHitPoints((baseLifeRepeatable_->getAttributes()->getAttribute(0) * 5) + 50);
	baseLifeRepeatable_->setMaximumManaPoints((baseLifeRepeatable_->getAttributes()->getAttribute(1) * 3) + 15);

	calculateTotalStats();
}

void PowerPlayer::calculateEquipmentStats()
{
	/* No Variable Declarations */

	/* Reset the equipment repeatable */
	delete equipmentRepeatable_;
	equipmentRepeatable_ = new LifeRepeatable;

	/* Increase attributes from equipment. */
	for (int i = 0; i < 4; i++) {
		equipmentRepeatable_->getAttributes()->increaseAttribute(i, fullEquipment_->getSlot1()->getWeapon()->getModifiedAttributes()->getAttribute(i));
		equipmentRepeatable_->getAttributes()->increaseAttribute(i, fullEquipment_->getSlot2()->getShield()->getModifiedAttributes()->getAttribute(i));
		equipmentRepeatable_->getAttributes()->increaseAttribute(i, fullEquipment_->getSlot3()->getBodyArmor()->getModifiedAttributes()->getAttribute(i));
		equipmentRepeatable_->getAttributes()->increaseAttribute(i, fullEquipment_->getSlot4()->getLegArmor()->getModifiedAttributes()->getAttribute(i));
		equipmentRepeatable_->getAttributes()->increaseAttribute(i, fullEquipment_->getSlot5()->getRing()->getModifiedAttributes()->getAttribute(i));
		equipmentRepeatable_->getAttributes()->increaseAttribute(i, fullEquipment_->getSlot6()->getRing()->getModifiedAttributes()->getAttribute(i));
		equipmentRepeatable_->getAttributes()->increaseAttribute(i, fullEquipment_->getSlot7()->getNecklace()->getModifiedAttributes()->getAttribute(i));
	}

	/* Increase damage from weapon. */
	equipmentRepeatable_->increasePhysicalDamageMinimum(fullEquipment_->getSlot1()->getWeapon()->getMinimumDamage() + fullEquipment_->getSlot2()->getWeapon()->getMinimumDamage());
	equipmentRepeatable_->increasePhysicalDamageMaximum(fullEquipment_->getSlot1()->getWeapon()->getMaximumDamage() + fullEquipment_->getSlot2()->getWeapon()->getMaximumDamage());

	/* Set base armor to equipment armor. */
	equipmentRepeatable_->getResistances()->setPhysicalArmor ( 
		fullEquipment_->getSlot2()->getShield()->getPhysicalArmor() + fullEquipment_->getSlot3()->getBodyArmor()->getPhysicalArmor() + fullEquipment_->getSlot4()->getLegArmor()->getPhysicalArmor()
	);

	equipmentRepeatable_->setMaximumHitPoints((equipmentRepeatable_->getAttributes()->getAttribute(0) * 5));
	equipmentRepeatable_->setMaximumManaPoints((equipmentRepeatable_->getAttributes()->getAttribute(1) * 3));

	calculateTotalStats();
}

void PowerPlayer::calculateTotalStats()
{
	/* No Variable Declarations */

	/* Reset the total life repeatable */
	delete totalLifeRepeatable_;
	totalLifeRepeatable_ = new LifeRepeatable;

	/* Increase attributes from base, weapons, and whatever else */
	for (int i = 0; i < 4; i++) {
		totalLifeRepeatable_->getAttributes()->increaseAttribute(i, baseLifeRepeatable_->getAttributes()->getAttribute(i));
		totalLifeRepeatable_->getAttributes()->increaseAttribute(i, equipmentRepeatable_->getAttributes()->getAttribute(i));
	}

	totalLifeRepeatable_->setPhysicalDamageMinimum(
		baseLifeRepeatable_->getPhysicalDamageMinimum() +
		equipmentRepeatable_->getPhysicalDamageMinimum()
	);

	totalLifeRepeatable_->setPhysicalDamageMaximum(
		baseLifeRepeatable_->getPhysicalDamageMaximum() +
		equipmentRepeatable_->getPhysicalDamageMaximum()
	);

	totalLifeRepeatable_->setCriticalHitChance (
		baseLifeRepeatable_->getCriticalHitChance() +
		equipmentRepeatable_->getCriticalHitChance()
	);

	totalLifeRepeatable_->setDoubleStrikeChance(
		baseLifeRepeatable_->getDoubleStrikeChance() +
		equipmentRepeatable_->getDoubleStrikeChance()
	);

	totalLifeRepeatable_->setDivineStrikeChance (
		baseLifeRepeatable_->getDivineStrikeChance() +
		equipmentRepeatable_->getDivineStrikeChance()
	);

	totalLifeRepeatable_->setDodgeChance(
		baseLifeRepeatable_->getDodgeChance() +
		equipmentRepeatable_->getDodgeChance()
	);
	
	totalLifeRepeatable_->setMaximumHitPoints(
		baseLifeRepeatable_->getMaximumHitPoints() +
		equipmentRepeatable_->getMaximumHitPoints()
	);

	totalLifeRepeatable_->setMaximumManaPoints(
		baseLifeRepeatable_->getMaximumManaPoints() +
		equipmentRepeatable_->getMaximumManaPoints()
	);

	if (currentHitPoints_ > totalLifeRepeatable_->getMaximumHitPoints())
		currentHitPoints_ = totalLifeRepeatable_->getMaximumHitPoints();
	
	if (currentManaPoints_ > totalLifeRepeatable_->getMaximumManaPoints())
		currentManaPoints_ = totalLifeRepeatable_->getMaximumManaPoints();
}

void PowerPlayer::setPowerPlayerProperties(string name, int level, int newClass, int race, int element)
{
    /* Variable Assignments */
	name_ = name;
	element_ = element;

	if (level < 1)
		level_ = 1;
	else
		level_ = level;

	/* Set attributes and class based on newClass */
	if (newClass == 1) {
		class_[0] = "Warrior";
    }
    else if (newClass == 2) {
		class_[0] = "Mage";
    }
    else if (newClass == 3) {
		class_[0] = "Rouge";
    }
	
	/* Set race based on the argument race */
	switch (race) {
		case 1:
			race_ = "Human";
			break;
		case 2:
			race_ = "Elf";
			break;
		case 3:
			race_ = "Orc";
			break;
		default:
			break;
	}

	/* Set created */
	created_ = 1;
}

int PowerPlayer::wearWeapon(Weapon *newWeapon)
{
	/* Variable Declarations */
	bool success = 0;
	YesNoInput *input = new YesNoInput;

	/* If the user is too low a level to equip the item, then tell him. */
	if (level_ < newWeapon->getLevelRequirement()) { 

		/* Set the error message */
		cout <<  "You must be level " << newWeapon->getLevelRequirement() << " to wear this weapon." << endl << endl;

		/* Pause to give the user a chance to see the message */
		system("pause");

		/* Formatting */
		cout << endl;

		/* Return 0 to indicate no item was equipped */
		return 0;
	}

	/* Else if the hero meets the level requirement */
	else {
		
		/* Put into the free slot. */
		if (fullEquipment_->getSlot1()->isFull() == 0) {

			/* Attempt to put the item into the slot */
			success = fullEquipment_->getSlot1()->setWeapon(newWeapon);

			/* If putting it into the slot succeeded return 1 */
			if (success == 1)
				return 1;
		}
		/* Else if it failed, then try to put into slot 2 */
		else {
			/* Attempt to put the item into the slot */
			success = fullEquipment_->getSlot2()->setWeapon(newWeapon);

			/* If putting it intot he slot failed, try another method */
			if (success == 0) {
				
				/* Ask if the user would empty the slot to put in the weapon */
				input->takeInput("Would you like to empty a slot to make room for this weapon?: ");

				/* If the user chooses yes, then... */
				if (input->isYes()) {

					/* Then attempt to empty the slot in the hero manager by returning 2. */
					return 2;
				}
			}
			else {
				return 1;
			}
		}
	}

	/* Return success */
	return success;
}

int PowerPlayer::wearShield(Shield *newShield)
{
	/* Variable Declarations */
	bool success = 0;
	YesNoInput *input = new YesNoInput;

	/* If the user is too low a level to equip the item, then tell him. */
	if (level_ < newShield->getLevelRequirement()) { 

		/* Set the error message */
		cout <<  "You must be level " << newShield->getLevelRequirement() << " to wear this shield." << endl;
		
		/* Pause to give the user a chance to see the message */
		system("pause");

		/* Formatting */
		cout << endl;

		/* Return 0 to indicate no item was equipped */
		return 0;
	}
	/* Else if the hero meets the level requirement */
	else {
		/* Attempt to put the item into the slot */
		success = fullEquipment_->getSlot2()->setShield(newShield);

		/* If putting it intot he slot failed, try another method */
		if (success == 0) {
				
			/* Ask if the user would empty the slot to put in the weapon */
			input->takeInput("Would you like to empty a slot to make room for this shield?");
				
			/* If the user chooses yes, then... */
			if (input->isYes()) {

				/* Then attempt to empty the slot in the hero manager by returning 2. */
				return 2;
			}
		}
		else {
			return 1;
		}
	}

	/* Return success */
	return success;
}

int PowerPlayer::wearBodyArmor(BodyArmor *newBodyArmor)
{
	/* Variable Declarations */
	bool success = 0;
	YesNoInput *input = new YesNoInput;

	/* If the user is too low a level to equip the item, then tell him. */
	if (level_ < newBodyArmor->getLevelRequirement()) {

		/* Set the error message */
		cout <<  "You must be level " << newBodyArmor->getLevelRequirement() << " to wear this body armor." << endl;
		
		/* Pause to give the user a chance to see the message */
		system("pause");

		/* Formatting */
		cout << endl;

		/* Return 0 to indicate no item was equipped */
		return 0;
	}

	/* Else if the hero meets the level requirement */
	else {

		/* Attempt to put the item into the slot */
		success = fullEquipment_->getSlot3()->setBodyArmor(newBodyArmor);

		/* If putting it intot he slot failed, try another method */
		if (success == 0) {
				
			/* Ask if the user would empty the slot to put in the weapon */
			input->takeInput("Would you like to empty a slot to make room for this body armor?");
				
			/* If the user chooses yes, then... */
			if (input->isYes()) {

				/* Then attempt to empty the slot in the hero manager by returning 2. */
				return 2;
			}
		}
		else {
			return 1;
		}
	}

	/* Return success */
	return success;
}

int PowerPlayer::wearLegArmor(LegArmor *newLegArmor)
{
	/* Variable Declarations */
	bool success = 0;
	YesNoInput *input = new YesNoInput;

	/* If the user is too low a level to equip the item, then tell him. */
	if (level_ < newLegArmor->getLevelRequirement()) { 

		/* Set the error message */
		cout <<  "You must be level " << newLegArmor->getLevelRequirement() << " to wear this leg armor." << endl;
		
		/* Pause to give the user a chance to see the message */
		system("pause");

		/* Formatting */
		cout << endl;

		/* Return 0 to indicate no item was equipped */
		return 0;
	}

	/* Else if the hero meets the level requirement */
	else {

		/* Attempt to put the item into the slot */
		success = fullEquipment_->getSlot4()->setLegArmor(newLegArmor);

		/* If putting it intot he slot failed, try another method */
		if (success == 0) {
				
			/* Ask if the user would empty the slot to put in the weapon */
			input->takeInput("Would you like to empty a slot to make room for this leg armor?");
				
			/* If the user chooses yes, then... */
			if (input->isYes()) {

				/* Then attempt to empty the slot in the hero manager by returning 2. */
				return 2;
			}
		}
		else {
			return 1;
		}
	}

	/* Return success */
	return success;
}

int PowerPlayer::wearRing(Ring *newRing)
{
	/* Variable Declarations */
	bool success = 0;
	YesNoInput *input = new YesNoInput;

	/* If the user is too low a level to equip the item, then tell him. */
	if (level_ < newRing->getLevelRequirement()) { 

		/* Set the error message */
		cout <<  "You must be level " << newRing->getLevelRequirement() << " to wear this ring." << endl;
		
		/* Pause to give the user a chance to see the message */
		system("pause");

		/* Formatting */
		cout << endl;

		/* Return 0 to indicate no item was equipped */
		return 0;
	}

	/* Else if the hero meets the level requirement */
	else {
		if (fullEquipment_->getSlot5()->isFull() == 0) {

			success = fullEquipment_->getSlot5()->setRing(newRing);
		}
		else if (success == 0) {

			/* Attempt to put the item into the slot */
			success = fullEquipment_->getSlot6()->setRing(newRing);

			/* If putting it intot he slot failed, try another method */
			if (success == 0) {
				
				/* Ask if the user would empty the slot to put in the weapon */
				input->takeInput("Would you like to empty a slot to make room for this ring?");
				
				/* If the user chooses yes, then... */
				if (input->isYes()) {

					/* Then attempt to empty the slot in the hero manager by returning 2. */
					return 2;
				}
			}
			else {
				return 1;
			}
		}
	}

	/* Return success */
	return success;
}

int PowerPlayer::wearNecklace(Necklace *newNecklace)
{
	/* Variable Declarations */
	bool success = 0;
	YesNoInput *input = new YesNoInput;

	/* If the user is too low a level to equip the item, then tell him. */
	if (level_ < newNecklace->getLevelRequirement()) { 

		/* Set the error message */
		cout <<  "You must be level " << newNecklace->getLevelRequirement() << " to wear this necklace." << endl;
		
		/* Pause to give the user a chance to see the message */
		system("pause");

		/* Formatting */
		cout << endl;

		/* Return 0 to indicate no item was equipped */
		return 0;
	}

	/* Else if the hero meets the level requirement */
	else {

		/* Attempt to put the item into the slot */
		success = fullEquipment_->getSlot7()->setNecklace(newNecklace);

		/* If putting it intot he slot failed, try another method */
		if (success == 0) {
				
			/* Ask if the user would empty the slot to put in the weapon */
			input->takeInput("Would you like to empty a slot to make room for this leg armor?");
				
			/* If the user chooses yes, then... */
			if (input->isYes()) {

				/* Then attempt to empty the slot in the hero manager by returning 2. */
				return 2;
			}
		}
		else {
			return 1;
		}
	}

	/* Return success */
	return success;
}	

void PowerPlayer::clearSlot(int x)
{
	switch (x) {
		case 1:
			fullEquipment_->getSlot1()->clear();
			break;
		case 2:
			fullEquipment_->getSlot2()->clear();
			break;
		case 3:
			fullEquipment_->getSlot3()->clear();
			break;
		case 4:
			fullEquipment_->getSlot4()->clear();
			break;
		case 5:
			fullEquipment_->getSlot5()->clear();
			break;
		case 6:
			fullEquipment_->getSlot6()->clear();
			break;
		case 7:
			fullEquipment_->getSlot7()->clear();
			break;
		default:
			cout << "No slot specified to clear.";
			break;
	}
}


void PartyMember::printStats()
{
    /* No Variable declarations */
    
	/* Display hero base stats */
	cout << "Stats for " << name_  << ", the " << race_ << " " << class_[0] << "." << "\n\n";  
	cout << "Level " << level_ << " with " << experience_ << " experience points.\n";
    cout << "Health Points: (" << currentHitPoints_ << "," << totalLifeRepeatable_->getMaximumHitPoints() << ").\n";
    cout << "Mana Points ("<< currentManaPoints_ << "," << totalLifeRepeatable_->getMaximumManaPoints() << ")\n\n";
    cout << "Vitility: " << totalLifeRepeatable_->getAttributes()->getAttribute(0) << " Magick: " << totalLifeRepeatable_->getAttributes()->getAttribute(1) << endl;
	cout << "Dexterity: " << totalLifeRepeatable_->getAttributes()->getAttribute(2) << " Luck: " << totalLifeRepeatable_->getAttributes()->getAttribute(3) << endl << endl;
	cout << "Deals: " << totalLifeRepeatable_->getPhysicalDamageMinimum() << " base damage and " << totalLifeRepeatable_->getPhysicalDamageMaximum()  << " max damage \n\n";
}

void PartyMember::manageEquipment()
{
	/* Variable Declarations */
	MenuInput *menu = new MenuInput;

	/* Keep looping while you haven't picked a proper slot */
	do {
		/* Get user input on slot to view */
		menu->takeInput("Which piece of equipment would you like to view detailed information on?\n 1.) Weapon\n 2.) Second Hand\n 3.) Body Armor\n 4.) Leg Armor\n 5.) Ring 1\n 6.) Ring 2\n 7.) Necklace",
			"You didn't pick a proper slot.", 7, 1);

		if (menu->inputIsErrorNumber() == 0) {

			/* Formatting */
			system("cls");

			switch (menu->getInput()) {
				case 1:
					/* Call the slots information display function */
					fullEquipment_->getSlot1()->printInformation();

				break;

				case 2:
				
					/* Call the slots information display function */
					fullEquipment_->getSlot2()->printInformation();
				break;

				case 3:
				
					/* Call the slots information display function */
					fullEquipment_->getSlot3()->printInformation();
				break;

				case 4:
				
					/* Call the slots information display function */
					fullEquipment_->getSlot4()->printInformation();
				break;
			
				case 5:
				
					/* Call the slots information display function */
					fullEquipment_->getSlot5()->printInformation();
				break;
			
				case 6:
				
					/* Call the slots information display function */
					fullEquipment_->getSlot6()->printInformation();
				break;
			
				case 7:
				
					/* Call the slots information display function */
					fullEquipment_->getSlot7()->printInformation();
				break;

				default:

					cout << "You selected no item to view.";
				break;
			}
		}

		/* formatting */
		cout << endl;

	}  while (menu->getInput() < menu->getErrorNumber());

	/* Formatting */
	cout << endl;
}

string PartyMember::getSaveInformation()
{
	/* Variable Declarations */
	string info = "";

	if (name_ != "No Name") {

		/* Store name */
		info += "Name" + name_  + "\n";

		/* Store Attributes */
		for (int i = 0; i < 4; i++) {
			info += "Attribute" + returnString(i) + returnString(totalLifeRepeatable_->getAttributes()->getAttribute(i)) + "\n";
		}

		/* -Store other information from life through powerplayer. */
		info += "Class" + class_[0] + "\n";
		info += "Level" + returnString(level_) + "\n";
		info += "Experience" + returnString(experience_) + "\n";
		info += "StatPoints" + returnString(statPoints_) + "\n";

		/* Store Equipment information */

	}

	return info;
}


string MainHero::getSaveInformation2()
{
	string info = "";

	info += "Gold" + returnString(gold_) + "\n";
	info += "XCoordinate" + returnString(coordinate_[0]) + "\n";
	info += "YCoordinate" + returnString(coordinate_[1]) + "\n";
	info += "MapZoom" + returnString(mapZoom_) + "\n";

	return info;
}

void MainHero::printMainStats()
{
	cout << "Party Gold: " << gold_ << "." << endl;
	cout << "Party Location: (" << coordinate_[0] << "," << coordinate_[1] << ")." << endl;
}

void MainHero::hasDied()
{
	/* Formatting */
	system("cls");

	/* Display message */
	cout << "Your Main hero has died! :(\n Don't worry though, my kindness will heal you and move you back to (100,100).\n However, the penalty is 1/2 of your gold and 1/5 of your progress to the next level.\n";	

	/* Handle everything that occurs due to the death */
	fullHeal();
	gold_ = (gold_ / 2);
	experience_ = (experience_ - (level_ * 5));
	
	/* Relocate the hero */
	respawn();

	system("pause");
	system("cls");
}

void MainHero::moveHero(int newPosition[])
{
    /* No Variable Declarations */

    /* Set the heroes new position */
	coordinate_[0] = newPosition[0];
	coordinate_[1] = newPosition[1];
}

void MainHero::activateCheats()
{
	class_[0] = "God";
	race_ = "Divine";
	element_ = 0;
	level_ = 100;
	gold_ = 999999999;
	
	for (int i = 0; i < 4; i++)
         totalLifeRepeatable_->getAttributes()->setAttribute(i,999);
	
	experience_ = 0;
}

void MainHero::respawn()
{
	coordinate_[0] = respawnCoordinates_[0];
	coordinate_[1] = respawnCoordinates_[1];
}
	

void Opponent::generateRandomOpponent(int heroLevel)
{	
	/* Declarations and Initializations... of variables.. */
	int name = (rand() % 10) + 1;
	int newClass = (rand() % 3) + 1;
	int race = (rand() % 3) + 1;
	int levelDeviation = ((rand() % heroLevel) + (heroLevel * (heroLevel / 20)));
	element_ = (rand() % 5) + 1;
	level_ = heroLevel + levelDeviation;
	gold_ = 5 * level_;
	experience_ = level_ * 20;
	
   /* Set enemy class/stats/spells based on the class */
	switch (newClass) {
		case 1:
			class_[0] = "Warrior";
			break;
		case 2:
			class_[0] = "Mage";
			break;
		case 3:
			class_[0] = "Rouge";
			break;
	}
	
	/* Set race based on race */
	switch (race) {
		case 1:
			race_ = "Human";
			break;
		case 2:
			race_ = "Elf";
			break;
		case 3:
			race_ = "Orc";
			break;
	}
	
	/* Set name based on randomly generated name variable */
	switch (name) {
		case 1:
			name_ = "Everist the White";
			break;
		case 2:
			name_ = "Sir Ralthword";
			break;
		case 3:
			name_ = "Crystal Sage Jerald";
			break;
		case 4:
			name_ = "Grand Magi";
			break;
		case 5:
			name_ = "Amethyst Dragon";
			break;
		case 6:
			name_ = "Golden Sphinx";
			break;
		case 7:
			name_ = "Mutant Rat";
			break;
		case 8:
			name_ = "Devil Incarnate";
			break;
		case 9:
			name_ = "Sad Dwarf";
			break;
		case 10:
			name_ = "Ruxor The Destroyer";
			break;
	}

	created_ = 1;
	baseLifeRepeatable_->getStates()->setAlive(1);
	calculateStats();
	fullHeal();
}

void Opponent::modifyStrength(double changePercentage)
{
	/*This method will weaken players by an amount that is specified.

	Each "changePercentage" will change the strength of the opponent by that amount.

	50 = 50% strength (easy)
	100 = 100% strength (normal)
	150 = 150% strength (hard) */
	
	/* No Variable Declarations */
	
	/* Lower attributes */
	for (int i = 0; i < 4; i++) {
		baseLifeRepeatable_->getAttributes()->setAttribute(i, int(totalLifeRepeatable_->getAttributes()->getAttribute(i) * changePercentage));
	}

	/* Recalculate stats */
	calculateStats();

	/* Lower health */
	totalLifeRepeatable_->setMaximumHitPoints(int(totalLifeRepeatable_->getMaximumHitPoints() * changePercentage));

	/* Adjust health to not be higher than max. */
	if (currentHitPoints_ > totalLifeRepeatable_->getMaximumHitPoints())
		currentHitPoints_ = totalLifeRepeatable_->getMaximumHitPoints();
	
	if (currentManaPoints_ > totalLifeRepeatable_->getMaximumManaPoints())
		currentManaPoints_ = totalLifeRepeatable_->getMaximumManaPoints();

	/* Lower damage min and max */
	totalLifeRepeatable_->setPhysicalDamageMinimum(int(totalLifeRepeatable_->getPhysicalDamageMaximum() * changePercentage));
	totalLifeRepeatable_->setPhysicalDamageMaximum(int(totalLifeRepeatable_->getPhysicalDamageMinimum() * changePercentage));

	
}
