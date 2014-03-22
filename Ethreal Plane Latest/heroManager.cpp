#include "life.h"
#include "heroManager.h"
#include "userinput.h"
#include "utilities.h"
#include "item.h"
#include "inventory.h"
#include "fullEquipment.h"
#include "equipmentSlots.h"
#include "lifeRepeatable.h"
#include "states.h"
#include "attributes.h"

/* Constructor */
HeroManager::HeroManager()
{
	hmCurrentFreeSlot_ = 0;
	hmTotalHeroes_ = 1;
	hmHeroBeingManaged_ = 0;

	hmHero_ = new MainHero;
	hmMenu_ = new MenuInput;

	for (int i = 0; i < 3; i++)
		hmPartyHero_[i] = new PartyMember();
}

/* Private Methods */
void HeroManager::swapHeroes(int a, int b)
{
	PartyMember *tempHero = new PartyMember();

	tempHero = hmPartyHero_[a];
	hmPartyHero_[a] = hmPartyHero_[b];
	hmPartyHero_[b] = tempHero;
}

/* Called by addPartyMember to set party names */
void HeroManager::setName(int genName[], string strName[])
{
	for (int i = 0; i < 5; i++) {
        if (genName[i] == 1)
    		strName[i] = "Roxan";
    	else if (genName[i] == 2)
    		strName[i] = "Zander";
		else if (genName[i] == 3)
    		strName[i] = "Blake";
    	else if (genName[i] == 4)
    		strName[i] = "Jaquin";
		else if (genName[i] == 5)
    		strName[i] = "Serena";
		else if (genName[i] == 6)
    		strName[i] = "Larry";
		else if (genName[i] == 7)
    		strName[i] = "Maximum";
		else if (genName[i] == 8)
    		strName[i] = "Jackson";
		else if (genName[i] == 9)
    		strName[i] = "Shawna";
		else if (genName[i] == 10)
    		strName[i] = "Larissa";
     }
}

/* Public Methods */

/* This method will return a hero object referring the created hero */
PartyMember* HeroManager::getHero(int x) { 
	
	/* Return the main hero if 1 is entered */
	if (x == 0) 
		return hmHero_; 
	/* Else return a party member from 0-2 */
	else if (x > 0) 
		return hmPartyHero_[x-1];

	/* By default return Hero 1 */
	return hmHero_;
}

/* Removes a party Members */
void HeroManager::removePartyMember()
{
	/* Variable Declarations */
	int dropHero = 0; /* Created on the user access level */
	
	/* If the 2nd hero slot isn't active, then no hero slot can be active and therfore display error message and leave funtion */
	if (hmTotalHeroes_ == 1)
		cout << "Sorry but you have no active party member to remove. ";
	else {
		/* Get user choice on party member to remove */
		hmMenu_->takeInput("Which party member would you like to remove?\n" + returnPartyNames(0), "You did not pick a party member.", (hmTotalHeroes_-1), 1);

		if (hmMenu_->inputIsErrorNumber()) {
			cout << "You have decided to not remove a party member.\n";
		}
		else {

			hmMenu_->convertInputProgrammerLevel();

			/* Clear all of the heroes properties */
			hmPartyHero_[hmMenu_->getInput()]->getBaseLifeRepeatable()->getStates()->setAlive(0);

			if (hmMenu_->getInput() == 0) {

				/* swap down 2nd hero if Active... */
				if (hmPartyHero_[1]->getCreated() == 1) {
	
					/* Swap down the third hero if active */
					if (hmPartyHero_[2]->getCreated() == 1) {
						swapHeroes(1,0);
						swapHeroes(2,1);
					}
					else {
						swapHeroes(1,0);
					}
				}
			}
			else if (hmMenu_->getInput() == 1) {			
				/* Swap down 3rd hero if active */
				if (hmPartyHero_[2]->getCreated() == 1) {
					swapHeroes(2,1);
				}
			}

			/* Decrease hmTotalHeroes_ */
			hmTotalHeroes_--;
			hmCurrentFreeSlot_--;
		}
	}
}

/* Called by guild to add a party member - returns 1 if a party member was successfully added else returns 0 */
bool HeroManager::generateNewRandomPartyMember()
{	
	/* Mainly function related Variables*/
	string message;
	int count = 0;

	/* Mainly Character Stat Generation Related Variables */
	
	/* Calculate and hold level */
	int pLevel = hmHero_->getLevel();
	int levelDeviation = int(pLevel - (pLevel / 4));

	cout << "pLevel: " << pLevel << endl;
	system("cls");

	/* Hold randomly generated values */
	string strRace[6];
	string strClass[6];
	string strName[6];
	string tempRace[6];
	string tempClass[6];
    int genName[6];
	int genClass[6];
	int genRace[6];
	int genLevel[6];
	int genElement[6];

	/* Hold final value */
	string newName;
	int newClass;
	int newRace;
	int newLevel;
	int newElement;

	/* Add the hero to the first available non-Active Party Member Slot */
	if (hmCurrentFreeSlot_ == 3) {
		system("cls");
		cout << "You have no room to add a hero! Sorry. \n\n";
	}
	else {
		/***********************
			Generate Values
		***********************/
		
		/* Initialize Levels for each tavernHero */
		for (int i = 0; i < 5; i++)
			genLevel[i] = ((rand() % levelDeviation) + pLevel);
		
		/* initialize Names */
		for (int i = 0; i < 5; i++)
			genName[i] = ((rand() % 10) + 1);

		/* Generate new names and store in strName array */
		setName(genName, strName);
		
		/* Initialize Races */
		for (int i2 = 0; i2 < 5; i2++) {
			genRace[i2] = ((rand() % 3) + 1);
			if (genRace[i2] == 1)
			    tempRace[i2] = "Human";
            else if (genRace[i2] == 2)
                tempRace[i2] = "Elf";
            else
                tempRace[i2] = "Orc";
        }
		
		/* Initialize Classes */ 
		for (int i3 = 0; i3 < 5; i3++) {
			genClass[i3] = ((rand() % 3) + 1);
			if (genClass[i3] == 1)
			   tempClass[i3] = "Warrior";
            else if (genClass[i3] == 2)
               tempClass[i3] = "Mage";
            else
               tempClass[i3] = "Rouge";
        }
		
		/* Initialize and Set Element */
		for (int j = 0; j < 5; j++)
			genElement[j] = rand() % 7;
		
		/********************************
			Let User Select Hero
		********************************/

		/* Set message for taking user input */
		message = "Welcome! There is a wide selection of heroes looking for a group!\n";
		for (int i = 0; i < 5; i++) {
			message.append(" ");
			if (i == 0)
				message.append("1");
			else if (i == 1)
				message.append("2");
			else if (i == 2)
				message.append("3");
			else if (i == 3)
				message.append("4");
			else if (i == 4)
				message.append("5");
				message.append(".) " + strName[i] + " the level ");
				message.append(genLevel[i] + " " + tempRace[i] + " " + tempClass[i]);
			if (i < 4)
				message.append("\n");
		}
		
		/* Get who the user wants to add into their group */
		hmMenu_->takeInput(message, "You have not picked a hero! Please pick one of the listed heroes.\n", 5, 1);
		
		/* Convert to programmer level */
		hmMenu_->convertInputProgrammerLevel();
		
		/* Formatting */
		system("cls");

		/*****************************
			Store selected Hero
		*****************************/

		/* Determine hero to add to party */
		if ((hmMenu_->getInput() >= 0) && (hmMenu_->getInput() < 6)) {
			
			/* Assign Array variables so that you pass only a single value instead of an array of values */
			newName	= strName[hmMenu_->getInput()];
			newClass = genClass[hmMenu_->getInput()];
			newRace = genRace[hmMenu_->getInput()];
			newLevel = genLevel[hmMenu_->getInput()];
			newElement = genElement[hmMenu_->getInput()];
			
			/* Make sure that the new Party Hero name isn't a duplicate of a previous party member */
			for (int j = 0; j < 3; j++) {
				if (newName == hmPartyHero_[j]->getName()) {
					if (count == 0)
						newName += " The Second";
					else if (count == 1)
						newName += " The Third";
				}
			}

			/* Put new stats into hero. */
			hmPartyHero_[hmCurrentFreeSlot_]->setPowerPlayerProperties(newName, newLevel, newClass, newRace, newElement);
			hmPartyHero_[hmCurrentFreeSlot_]->calculateStats();
			hmPartyHero_[hmCurrentFreeSlot_]->fullHeal();
		
			/* Print Hero Stats */
			hmPartyHero_[hmCurrentFreeSlot_]->printStats();
			
			/* Display message that the hero was added to the party */
			cout << hmPartyHero_[hmCurrentFreeSlot_]->getName() << " has been added to your party!!!\n\n";

			/* Increase hmTotalHeroes_ */
			hmTotalHeroes_++;
			hmCurrentFreeSlot_++;

			/* Everything succeeded so return 1 */
			return 1;
		}
		else {
			system("cls");
			cout << "You have chosen to add nobody to your party";
			system("pause");
		}
	}

	/* A party member wasn't added so return 0 */
	return 0;
}

/* Return a string showing all hero names */
string HeroManager::returnPartyNames(bool includeMainHero)
{	
	/* Variable Declarations */
	string partyNames;
	int menuCounter = 1;

	/* Go through all party members to display their name */
	for (int i = 0; i < hmTotalHeroes_; i++) {
		
		/* If we don't want to include the main hero, then increase i by 1 to skip the main hero */
		if ((includeMainHero == 0) && (i == 0)) {
			i++;
		}

		/* If the hero is active */
		if (getHero(i)->getCreated() == 1) {

			/* Append the new party number to the menu along with the hero information */
			partyNames += " " + returnString(menuCounter) + ".) Hero " + getHero(i)->getName();
			
			if (i < (hmTotalHeroes_ - 1))
				partyNames += "\n";

			menuCounter++;
		}
	}
	
	/* Return the newly formed string */
	return partyNames;
}

/* Display all party Names */
void HeroManager::showFullPartyNames()
{	
	/* Display hero name */
	cout << "Hero 1. " << getMainHero()->getName();

	/* Display party member names */
	for (int i = 0; i < hmTotalHeroes_; i++) {
		/* If the party member is active, then display name and keep looping */
		if (getHero(i)->getCreated() == 1)
			cout << endl << getHero(i)->getName();
		/* else end the loop */
		else
			i = hmTotalHeroes_;
	}
}

/* Let user select hero and then display that heroes stats. */
void HeroManager::showFullPartyStats()
{
	/* Variable Declarations */

	/* Get user input on the hero to view */
	hmMenu_->takeInput("Which heroes stats would you like to view?\n" + returnPartyNames(1), "You didn't select a hero", hmTotalHeroes_, 1);

	/* If the user didn't choose to exit, then display the stats */
	if (hmMenu_->inputIsErrorNumber() == 0) {
		
		/* Put userChoice on programmer level */
		hmMenu_->convertInputProgrammerLevel();

		/* Formatting */
		system("cls");

		/* Show extra stats */
		getMainHero()->printMainStats();
	
		/* Formatting */
		cout << endl;

		/* Show stats of the chosen hero */
		getHero(hmMenu_->getInput())->printStats();

		system("pause");
	}
}

/* This function will give an amount of experience to all party members. This will also check for levelups and handle them. */
void HeroManager::giveExperience(int experienceGainTotal)
{
	/* Variable Declarations */
	int nextLevel[4];
	int currentExperience[4];
	int experienceRequired[4];
	int trueExperienceRequired[4];

	/* Initialize next level to the heroes current level + 1 */
	for (int i = 0; i < hmTotalHeroes_; i++)
		nextLevel[i] = getHero(i)->getLevel() + 1;

	for (int i = 0; i < hmTotalHeroes_; i++) {
		/* Set true experience Required */
		trueExperienceRequired[i] = getHero(i)->getLevel() * 100;

		/* Store base current Exp */
		currentExperience[0] = getHero(i)->getExperience();
		
		/* Give hero exp for killing enemy */
		getHero(i)->increaseExperience(experienceGainTotal);
		currentExperience[1] = getHero(i)->getExperience();
		
		/* Display exp reward */
		cout << getHero(i)->getName() << ":\n Exp Gain: " << experienceGainTotal << " : New Total Exp: ";
		cout << currentExperience[1] << "\n";

		/* Calculate experience required */
		experienceRequired[i] = trueExperienceRequired[i] - currentExperience[1];

		/* If the heroes current experience is higher than what is required to level... levelup! */
		if (experienceRequired[i] > 0)
			cout << " Exp Till Levelup:  " << experienceRequired[i] << "\n";   
		else {
			/* Display levelup message */
			cout << "LEVELUP!!!\n";

			/* Increase Level */
			getHero(i)->incrementLevel();
			cout << getHero(i)->getName() << " has leveled up to " << nextLevel[i] << "!\n";
			
			/* Set the heroes new experience to his current experience minu the amount needed to levelup */
			currentExperience[2] = currentExperience[1] - experienceRequired[i];
			getHero(i)->setExperience(currentExperience[2]);
			
			/* Increase attributes */
			getHero(i)->getBaseLifeRepeatable()->getAttributes()->increaseAttribute(0, 2);
			getHero(i)->getBaseLifeRepeatable()->getAttributes()->increaseAttribute(1, 2);
			getHero(i)->getBaseLifeRepeatable()->getAttributes()->increaseAttribute(2, 2);
			getHero(i)->getBaseLifeRepeatable()->getAttributes()->increaseAttribute(3, 2);
			
			/* Recalculate stats for the hero */
			getHero(i)->calculateStats();
		}
		cout << endl;
	}
}

void HeroManager::fullHealWholeParty()
{
	/* Heal all Heroes */
	for (int i = 0; i < hmTotalHeroes_; i++)
		getHero(i)->fullHeal();
}

void HeroManager::healthRestoreWholeParty()
{
	/* Restore hit points to heroes */
	for (int i = 0; i < hmTotalHeroes_; i++)
		getHero(i)->restoreHitPoints();
}

void HeroManager::manaRestoreWholeParty()
{
	/* Restore mana to heroes */
	for (int i = 0; i < hmTotalHeroes_; i++)
		getHero(i)->restoreManaPoints();
}

bool HeroManager::aquireWeapon(string aquireMethod, Weapon *newWeapon)
{
	/* Variable Declarations */
	int success = 0;
	bool keepLooping = 1;

	/* Keep looping until a proper action is chosen for the item */
	while (keepLooping == 1) {

		/* Choose what to do with the item  */
		hmMenu_->takeInput(aquireMethod + newWeapon->getFullName() + "\n What would you like to do with the item?\n 1. Equip\n 2. Put in Inventory\n 3. Drop on the ground: ", 
			"Please pick an action to perform ", 3, 0);

		/* Formatting */
		cout <<  endl;

		/* Go through the possible options of how the handle the item */
		switch (hmMenu_->getInput()) {

			/* Equip the item */
			case 1:

				/* Let the user pick the hero to equip on */
				setHeroBeingManaged("Which hero would you like to equip this on?\n" + returnPartyNames(1));

				/* If the user chose to exit, then... */
				if (hmHeroBeingManaged_ == getTotalHeroes()) {

					/* Display that the user didn't want to equip the item. */
					cout << "You have decided to equip this item on nobody.\n";
				}
				else {
					/* Add the weapon the hero inventory */
					success = getHero(hmHeroBeingManaged_)->wearWeapon(newWeapon);

					if (success == 1) {
					
						/* Display Success Message */
						messagePlus("You have successfully equipped the item!\n\n");

						/* Compute Stats for hero or Party Member */
						getHero(hmHeroBeingManaged_)->calculateStats();

						/* Return 1 to indicate the item was properly stored. */
						return 1;
					}
					else if (success == 2) {
						aquireTargetWeapon(hmHeroBeingManaged_);

						/* Return 1 to indicate the item was properly stored. */
						return 1;
					}
				}

			break;

			/* Store the item */
			case 2:

				/* Let user decide who to store the item on. Include exit option. */
				setHeroBeingManaged("Which hero's inventory would you like to put this item in?\n" + returnPartyNames(1));

				/* If the user chose to exit, then... */
				if (hmHeroBeingManaged_ == getTotalHeroes()) {

					/* Display to the user that he exited, pause, and set keepLooping to 0 to break loop. */
					messagePlus("You have selected to give the item to no hero.\n");
					
					/* Pause to let the user see the message */
					system("pause");

					/* Formatting */
					system("cls");
					
				}
				else {

					/* Add the weapon the hero inventory */
					success = getHero(hmHeroBeingManaged_)->getEquipmentInventory()->addWeapon(newWeapon);

					/* If successfully stored, then... */
					if (success == 1) {

						/* Display Success Message */
						messagePlus("You have successfully stored the " + newWeapon->getFullName() + "!\n\n");

						/* Return 1 to indicate the item was properly stored. */
						return 1;
					}
				}

			break;

			case 3:

				/* Display dropped message */
				messagePlus("You dropped the item on the ground with a shrug.\n\n");
				
				/* Set keepLooping to 0 to break loop */
				return 0;

			break;

			default:

				cout << "Error somewhere\n";

			break;
		}
	}

	/* Return 0 to indicate the item was NOT stored! */
	return 0;
}

bool HeroManager::aquireShield(string aquireMethod, Shield *newShield)
{
	/* Variable Declarations */
	int success = 0;
	bool keepLooping = 1;

	/* Keep looping until a proper action is chosen for the item */
	while (keepLooping == 1) {

		/* Choose what to do with the item  */
		hmMenu_->takeInput(aquireMethod + newShield->getFullName() + "\n What would you like to do with the item?\n 1. Equip\n 2. Put in Inventory\n 3. Drop on the ground: ", 
			"Please pick an action to perform ", 3, 0);

		/* Formatting */
		cout <<  endl;

		/* Go through the possible options of how the handle the item */
		switch (hmMenu_->getInput()) {

			/* Equip the item */
			case 1:

				/* Let the user pick the hero to equip on */
				setHeroBeingManaged("Which hero would you like to equip this on?\n" + returnPartyNames(1));

				/* If the user chose to exit, then... */
				if (hmHeroBeingManaged_ == getTotalHeroes()) {

					/* Display that the user didn't want to equip the item. */
					cout << "You have decided to equip this item on nobody.\n";
				}
				else {
					/* Add the weapon the hero inventory */
					success = getHero(hmHeroBeingManaged_)->wearShield(newShield);

					if (success == 1) {
					
						/* Display Success Message */
						messagePlus("You have successfully equipped the item!\n\n");

						/* Compute Stats for hero or Party Member */
						getHero(hmHeroBeingManaged_)->calculateStats();

						/* Return 1 to indicate the item was properly stored. */
						return 1;
					}
					else if (success == 2) {
						aquireTargetShield(hmHeroBeingManaged_);

						/* Return 1 to indicate the item was properly stored. */
						return 1;
					}
				}

			break;

			/* Store the item */
			case 2:

				/* Let user decide who to store the item on. Include exit option. */
				setHeroBeingManaged("Which hero's inventory would you like to put this item in?\n" + returnPartyNames(1));

				/* If the user chose to exit, then... */
				if (hmHeroBeingManaged_ == getTotalHeroes()) {

					/* Display to the user that he exited, pause, and set keepLooping to 0 to break loop. */
					messagePlus("You have selected to give the item to no hero.\n");
					
					/* Pause to let the user see the message */
					system("pause");

					/* Formatting */
					system("cls");
					
				}
				else {

					/* Add the weapon the hero inventory */
					success = getHero(hmHeroBeingManaged_)->getEquipmentInventory()->addShield(newShield);

					/* If successfully stored, then... */
					if (success == 1) {

						/* Display Success Message */
						messagePlus("You have successfully stored the " + newShield->getFullName() + "!\n\n");

						/* Return 1 to indicate the item was properly stored. */
						return 1;
					}
				}

			break;

			case 3:

				/* Display dropped message */
				messagePlus("You dropped the item on the ground with a shrug.\n\n");
				
				/* Set keepLooping to 0 to break loop */
				return 0;

			break;

			default:

				cout << "Error somewhere\n";

			break;
		}
	}

	/* Return 0 to indicate the item was NOT stored! */
	return 0;
}

bool HeroManager::aquireBodyArmor(string aquireMethod, BodyArmor *newBodyArmor)
{
	/* Variable Declarations */
	int success = 0;
	bool keepLooping = 1;

	/* Keep looping until a proper action is chosen for the item */
	while (keepLooping == 1) {

		/* Choose what to do with the item  */
		hmMenu_->takeInput(aquireMethod + newBodyArmor->getFullName() + "\n What would you like to do with the item?\n 1. Equip\n 2. Put in Inventory\n 3. Drop on the ground: ", 
			"Please pick an action to perform ", 3, 0);

		/* Formatting */
		cout <<  endl;

		/* Go through the possible options of how the handle the item */
		switch (hmMenu_->getInput()) {

			/* Equip the item */
			case 1:

				/* Let the user pick the hero to equip on */
				setHeroBeingManaged("Which hero would you like to equip this on?\n" + returnPartyNames(1));

				/* If the user chose to exit, then... */
				if (hmHeroBeingManaged_ == getTotalHeroes()) {

					/* Display that the user didn't want to equip the item. */
					cout << "You have decided to equip this item on nobody.\n";
				}
				else {
					/* Add the weapon the hero inventory */
					success = getHero(hmHeroBeingManaged_)->wearBodyArmor(newBodyArmor);

					if (success == 1) {
					
						/* Display Success Message */
						messagePlus("You have successfully equipped the item!\n\n");

						/* Compute Stats for hero or Party Member */
						getHero(hmHeroBeingManaged_)->calculateStats();

						/* Return 1 to indicate the item was properly stored. */
						return 1;
					}
					else if (success == 2) {
						aquireTargetBodyArmor(hmHeroBeingManaged_);

						/* Return 1 to indicate the item was properly stored. */
						return 1;
					}
				}

			break;

			/* Store the item */
			case 2:

				/* Let user decide who to store the item on. Include exit option. */
				setHeroBeingManaged("Which hero's inventory would you like to put this item in?\n" + returnPartyNames(1));

				/* If the user chose to exit, then... */
				if (hmHeroBeingManaged_ == getTotalHeroes()) {

					/* Display to the user that he exited, pause, and set keepLooping to 0 to break loop. */
					messagePlus("You have selected to give the item to no hero.\n");
					
					/* Pause to let the user see the message */
					system("pause");

					/* Formatting */
					system("cls");
					
				}
				else {

					/* Add the weapon the hero inventory */
					success = getHero(hmHeroBeingManaged_)->getEquipmentInventory()->addBodyArmor(newBodyArmor);

					/* If successfully stored, then... */
					if (success == 1) {

						/* Display Success Message */
						messagePlus("You have successfully stored the " + newBodyArmor->getFullName() + "!\n\n");

						/* Return 1 to indicate the item was properly stored. */
						return 1;
					}
				}

			break;

			case 3:

				/* Display dropped message */
				messagePlus("You dropped the item on the ground with a shrug.\n\n");
				
				/* Set keepLooping to 0 to break loop */
				return 0;

			break;

			default:

				cout << "Error somewhere\n";

			break;
		}
	}

	/* Return 0 to indicate the item was NOT stored! */
	return 0;
}

bool HeroManager::aquireLegArmor(string aquireMethod, LegArmor *newLegArmor)
{
	/* Variable Declarations */
	int success = 0;
	bool keepLooping = 1;

	/* Keep looping until a proper action is chosen for the item */
	while (keepLooping == 1) {

		/* Choose what to do with the item  */
		hmMenu_->takeInput(aquireMethod + newLegArmor->getFullName() + "\n What would you like to do with the item?\n 1. Equip\n 2. Put in Inventory\n 3. Drop on the ground: ", 
			"Please pick an action to perform ", 3, 0);

		/* Formatting */
		cout <<  endl;

		/* Go through the possible options of how the handle the item */
		switch (hmMenu_->getInput()) {

			/* Equip the item */
			case 1:

				/* Let the user pick the hero to equip on */
				setHeroBeingManaged("Which hero would you like to equip this on?\n" + returnPartyNames(1));

				/* If the user chose to exit, then... */
				if (hmHeroBeingManaged_ == getTotalHeroes()) {

					/* Display that the user didn't want to equip the item. */
					cout << "You have decided to equip this item on nobody.\n";
				}
				else {
					/* Add the weapon the hero inventory */
					success = getHero(hmHeroBeingManaged_)->wearLegArmor(newLegArmor);

					if (success == 1) {
					
						/* Display Success Message */
						messagePlus("You have successfully equipped the item!\n\n");

						/* Compute Stats for hero or Party Member */
						getHero(hmHeroBeingManaged_)->calculateStats();

						/* Return 1 to indicate the item was properly stored. */
						return 1;
					}
					else if (success == 2) {
						aquireTargetLegArmor(hmHeroBeingManaged_);

						/* Return 1 to indicate the item was properly stored. */
						return 1;
					}
				}

			break;

			/* Store the item */
			case 2:

				/* Let user decide who to store the item on. Include exit option. */
				setHeroBeingManaged("Which hero's inventory would you like to put this item in?\n" + returnPartyNames(1));

				/* If the user chose to exit, then... */
				if (hmHeroBeingManaged_ == getTotalHeroes()) {

					/* Display to the user that he exited, pause, and set keepLooping to 0 to break loop. */
					messagePlus("You have selected to give the item to no hero.\n");
					
					/* Pause to let the user see the message */
					system("pause");

					/* Formatting */
					system("cls");
					
				}
				else {

					/* Add the weapon the hero inventory */
					success = getHero(hmHeroBeingManaged_)->getEquipmentInventory()->addLegArmor(newLegArmor);

					/* If successfully stored, then... */
					if (success == 1) {

						/* Display Success Message */
						messagePlus("You have successfully stored the " + newLegArmor->getFullName() + "!\n\n");

						/* Return 1 to indicate the item was properly stored. */
						return 1;
					}
				}

			break;

			case 3:

				/* Display dropped message */
				messagePlus("You dropped the item on the ground with a shrug.\n\n");
				
				/* Set keepLooping to 0 to break loop */
				return 0;

			break;

			default:

				cout << "Error somewhere\n";

			break;
		}
	}

	/* Return 0 to indicate the item was NOT stored! */
	return 0;
}

bool HeroManager::aquireRing(string aquireMethod, Ring *newRing)
{
	/* Variable Declarations */
	int success = 0;
	bool keepLooping = 1;

	/* Keep looping until a proper action is chosen for the item */
	while (keepLooping == 1) {

		/* Choose what to do with the item  */
		hmMenu_->takeInput(aquireMethod + newRing->getFullName() + "\n What would you like to do with the item?\n 1. Equip\n 2. Put in Inventory\n 3. Drop on the ground: ", 
			"Please pick an action to perform ", 3, 0);

		/* Formatting */
		cout <<  endl;

		/* Go through the possible options of how the handle the item */
		switch (hmMenu_->getInput()) {

			/* Equip the item */
			case 1:

				/* Let the user pick the hero to equip on */
				setHeroBeingManaged("Which hero would you like to equip this on?\n" + returnPartyNames(1));

				/* If the user chose to exit, then... */
				if (hmHeroBeingManaged_ == getTotalHeroes()) {

					/* Display that the user didn't want to equip the item. */
					cout << "You have decided to equip this item on nobody.\n";
				}
				else {
					/* Add the weapon the hero inventory */
					success = getHero(hmHeroBeingManaged_)->wearRing(newRing);

					if (success == 1) {
					
						/* Display Success Message */
						messagePlus("You have successfully equipped the item!\n\n");

						/* Compute Stats for hero or Party Member */
						getHero(hmHeroBeingManaged_)->calculateStats();

						/* Return 1 to indicate the item was properly stored. */
						return 1;
					}
					else if (success == 2) {
						aquireTargetRing(hmHeroBeingManaged_);

						/* Return 1 to indicate the item was properly stored. */
						return 1;
					}
				}

			break;

			/* Store the item */
			case 2:

				/* Let user decide who to store the item on. Include exit option. */
				setHeroBeingManaged("Which hero's inventory would you like to put this item in?\n" + returnPartyNames(1));

				/* If the user chose to exit, then... */
				if (hmHeroBeingManaged_ == getTotalHeroes()) {

					/* Display to the user that he exited, pause, and set keepLooping to 0 to break loop. */
					messagePlus("You have selected to give the item to no hero.\n");
					
					/* Pause to let the user see the message */
					system("pause");

					/* Formatting */
					system("cls");
					
				}
				else {

					/* Add the weapon the hero inventory */
					success = getHero(hmHeroBeingManaged_)->getEquipmentInventory()->addRing(newRing);

					/* If successfully stored, then... */
					if (success == 1) {

						/* Display Success Message */
						messagePlus("You have successfully stored the " + newRing->getFullName() + "!\n\n");

						/* Return 1 to indicate the item was properly stored. */
						return 1;
					}
				}

			break;

			case 3:

				/* Display dropped message */
				messagePlus("You dropped the item on the ground with a shrug.\n\n");
				
				/* Set keepLooping to 0 to break loop */
				return 0;

			break;

			default:

				cout << "Error somewhere\n";

			break;
		}
	}

	/* Return 0 to indicate the item was NOT stored! */
	return 0;
}

bool HeroManager::aquireNecklace(string aquireMethod, Necklace *newNecklace)
{
	/* Variable Declarations */
	int success = 0;
	bool keepLooping = 1;

	/* Keep looping until a proper action is chosen for the item */
	while (keepLooping == 1) {

		/* Choose what to do with the item  */
		hmMenu_->takeInput(aquireMethod + newNecklace->getFullName() + "\n What would you like to do with the item?\n 1. Equip\n 2. Put in Inventory\n 3. Drop on the ground: ", 
			"Please pick an action to perform ", 3, 0);

		/* Formatting */
		cout <<  endl;

		/* Go through the possible options of how the handle the item */
		switch (hmMenu_->getInput()) {

			/* Equip the item */
			case 1:

				/* Let the user pick the hero to equip on */
				setHeroBeingManaged("Which hero would you like to equip this on?\n" + returnPartyNames(1));

				/* If the user chose to exit, then... */
				if (hmHeroBeingManaged_ == getTotalHeroes()) {

					/* Display that the user didn't want to equip the item. */
					cout << "You have decided to equip this item on nobody.\n";
				}
				else {
					/* Add the weapon the hero inventory */
					success = getHero(hmHeroBeingManaged_)->wearNecklace(newNecklace);

					if (success == 1) {
					
						/* Display Success Message */
						messagePlus("You have successfully equipped the item!\n\n");

						/* Compute Stats for hero or Party Member */
						getHero(hmHeroBeingManaged_)->calculateStats();

						/* Return 1 to indicate the item was properly stored. */
						return 1;
					}
					else if (success == 2) {
						aquireTargetNecklace(hmHeroBeingManaged_);

						/* Return 1 to indicate the item was properly stored. */
						return 1;
					}
				}

			break;

			/* Store the item */
			case 2:

				/* Let user decide who to store the item on. Include exit option. */
				setHeroBeingManaged("Which hero's inventory would you like to put this item in?\n" + returnPartyNames(1));

				/* If the user chose to exit, then... */
				if (hmHeroBeingManaged_ == getTotalHeroes()) {

					/* Display to the user that he exited, pause, and set keepLooping to 0 to break loop. */
					messagePlus("You have selected to give the item to no hero.\n");
					
					/* Pause to let the user see the message */
					system("pause");

					/* Formatting */
					system("cls");
					
				}
				else {

					/* Add the weapon the hero inventory */
					success = getHero(hmHeroBeingManaged_)->getEquipmentInventory()->addNecklace(newNecklace);

					/* If successfully stored, then... */
					if (success == 1) {

						/* Display Success Message */
						messagePlus("You have successfully stored the " + newNecklace->getFullName() + "!\n\n");

						/* Return 1 to indicate the item was properly stored. */
						return 1;
					}
				}

			break;

			case 3:

				/* Display dropped message */
				messagePlus("You dropped the item on the ground with a shrug.\n\n");
				
				/* Set keepLooping to 0 to break loop */
				return 0;

			break;

			default:

				cout << "Error somewhere\n";

			break;
		}
	}

	/* Return 0 to indicate the item was NOT stored! */
	return 0;
}

void HeroManager::setHeroBeingManaged(string message)
{
	/* Get hero that you want to equip the item on */
	hmMenu_->takeInput(message, "You have not selected a proper hero.", getTotalHeroes(), 1);
				
	/* Put on programmers level */
	hmMenu_->convertInputProgrammerLevel();

	/* Let user decide who to equip the item on. Include exit option. */
	hmHeroBeingManaged_ = hmMenu_->getInput();
}

void HeroManager::messagePlus(string message)
{
	/* Display to the user that he exited, pause, and set keepLooping to 0 to break loop. */
	cout << message << endl;
					
	/* Pause to let the user see the message */
	system("pause");

	/* Formatting */
	system("cls");
}

/* Acts as a starter to call the inventory managers. */
void HeroManager::manageInventories()
{
	/* Variable Declarations */
	int heroChoice = 0;
	int equipmentChoice;

	/* Get input on hero to manage inventories of */
	hmMenu_->takeInput("Pick a hero to manage the inventories of:\n" + returnPartyNames(1), "You did not pick a proper hero", hmTotalHeroes_, 1);
	
	/* If the user chose to exit, then... */
	if (hmMenu_->inputIsErrorNumber()) {

		/* Display message verifying this */
		cout << "You have decided to manage no inventories.";
	}
	else {
		
		/* Put on programmer level */
		hmMenu_->convertInputProgrammerLevel();

		/* Save the hero the user selected */
		hmHeroBeingManaged_ = hmMenu_->getInput();

		/* Formatting */
		cout << endl;

		/* Get input on inventory to view */
		hmMenu_->takeInput("Which inventory would you like to view?\n 1.) Consumables Inventory\n 2.) Equipment Inventory\n 3.) Currently Equipped Items: ",
			"You didn't choose an inventory to view", 3, 1);

		/* Formatting */
		cout << endl;

		switch (hmMenu_->getInput()) {
			case 1:
			
				/* Call function that allows you to manage the items in the consumables inventory */
				manageConsumables();
			break;

			case 2:

				/* If at least one equipment was displayed, then show options to manage equipment */
				if (getHero(hmHeroBeingManaged_)->getEquipmentInventory()->displayAllEquipment() == 1) {
					
					/* Formatting */
					cout << endl;
					/* Get user input on equipment. */
					cout << "Enter the equipment that you want to manage: ";
					cin >> equipmentChoice;
					
					/* Formatting */
					cout <<  endl;

					/* Go to manage the equipment inventory manager */
					manageEquipment(equipmentChoice);
				}

			break;

			case 3:
			
				/* Go to equipment manager */
				getHero(hmHeroBeingManaged_)->manageEquipment();
			break;
			
			default:
			
				/* Else tell the user they chose no inventory */
				cout << "AIGHT\n";
			break;
		}
	}
}

/* Manages consumables */
void HeroManager::manageConsumables()
{
	/* Variable Declarations */
	int consumableChoice = 0;

	/* If at least one consumable was displayed, then show options to manage consumables */
	if (getHero(hmHeroBeingManaged_)->getConsumableInventory()->displayAllConsumables() == 1) {
		
		/* Get user input on consumable. */
		hmMenu_->takeInput("Pick the consumable that you want to manage. You can enter \"1595\" if you want to drop all consumables. ",
			"You did not pick an item", getHero(hmHeroBeingManaged_)->getConsumableInventory()->getTotalConsumables(), 1);

		/* Save the chosen consumable */
		consumableChoice = hmMenu_->getInput();

		/* If the user chose to drop all consumables then... */
		if (hmMenu_->getInput() == 1595) {

			/* Drop all consumables */
			getHero(hmHeroBeingManaged_)->getConsumableInventory()->dropAllConsumables();
		}
		else if (hmMenu_->inputIsErrorNumber() == 0) {
			
			/* Get action to perform on the item. */
			hmMenu_->takeInput("What would you like to do with this item?\n 1.) Use Consumable\n 2.) View Consumable Properties\n 3.) Drop Consumable: ", "You did not pick an action to perform.\n", 3, 1);
		
			switch (hmMenu_->getInput()) {
				case 1:
					/* Use the consumable on a new hero target */
					hmMenu_->takeInput("Pick a hero to use the consumable on:\n" + returnPartyNames(1), "You did not pick a proper hero", hmTotalHeroes_, 1);

					/* If the user chose to use on nobody then... */
					if (hmMenu_->inputIsErrorNumber()) {

						/* Display message verifying this */
						cout << "You have decided to use this consumable on nobody.";
					}
					else {
						/* Apply the healing effect of the consumable to the hero */
						getHero(hmMenu_->getInput())->increaseCurrentHitPoints(getHero(hmHeroBeingManaged_)->getConsumableInventory()->getConsumable(consumableChoice).getHeal());
					}
					break;
				case 2:
					getHero(hmHeroBeingManaged_)->getConsumableInventory()->getConsumable(consumableChoice).displayInformation();
					break;
				case 3:
					getHero(hmHeroBeingManaged_)->getConsumableInventory()->dropConsumable(consumableChoice);
					break;
				default:
					cout << "You have chose no action.\n";
			}
		}
		else
			cout << "You have chose no item.\n";
	}
}

/* Manages equipment */
void HeroManager::manageEquipment(int equipmentChoice)
{
	/* Variable Declarations */
	int success = 0;
	bool keptItem = 0;

	int itemType = 0;
	int targetHero = 0;
	
	if (equipmentChoice == 1595) {

		/* Drop all equipment */
		getHero(hmHeroBeingManaged_)->getEquipmentInventory()->resetInventory();
	}
	/* If the user chose to drop all equipment then... */
	else if ((equipmentChoice <= 0) || (equipmentChoice > getHero(hmHeroBeingManaged_)->getEquipmentInventory()->getTotalItems())) {

		/* Display an error message */
		"You did not pick an item to manage.";
	}
	/* The equipment choice is valid. Proceed. */
	else {

		while (success == 0) {

			/* Get userChoice */
			hmMenu_->takeInput("What would you like to do with this item?\n 1.) Equip Item \n 2.) View Item Stats\n 3.) Drop Item\n 4.) Move to another Heroes Inventory ",
				"You did not pick an action to perform.\n", 4, 1);
			
			/* Formatting */
			cout <<  endl;

			switch (hmMenu_->getInput()) {

				/* Equip the Item */
				case 1:

					/* Get the new target hero to put the equipment on. */
					hmMenu_->takeInput("Pick a hero to equip this equipment on:\n" + returnPartyNames(1), "You did not pick a proper hero", hmTotalHeroes_, 1);

					/* Formatting */
					cout <<  endl;

					/* If the user chose to use on nobody then... */
					if (hmMenu_->inputIsErrorNumber()) {

						/* Display message verifying this */
						messagePlus("You have decided to equip this equipment on nobody.");
					}
					else {

						/* Put the input on the programmer level */
						hmMenu_->convertInputProgrammerLevel();

						/* Get the item type of the selected item */
						itemType = getHero(hmHeroBeingManaged_)->getEquipmentInventory()->getItemType(equipmentChoice);


						/* Set the user equipment choice to the programmer array access level */
						getHero(hmHeroBeingManaged_)->getEquipmentInventory()->setEquipmentNumber(equipmentChoice);

						/* Equip the item on the proper hero. */
						switch (itemType) {
							case 0:

								/* Add the item from the selected hero to the new hero. */
								success = getHero(hmMenu_->getInput())->wearWeapon(getHero(hmHeroBeingManaged_)->getEquipmentInventory()->getWeapon(equipmentChoice));

								/* If the user wants to try to dequip an item, then try that */
								if (success == 2) {
									aquireTargetWeapon(hmMenu_->getInput());
									success = 1;
								}

							break;

							case 1:
								success = getHero(hmMenu_->getInput())->wearShield(getHero(hmHeroBeingManaged_)->getEquipmentInventory()->getShield(equipmentChoice));

								if (success == 2) {
									aquireTargetShield(hmMenu_->getInput());
									success = 1;
								}

							break;

							case 2:
								success = getHero(hmMenu_->getInput())->wearBodyArmor(getHero(hmHeroBeingManaged_)->getEquipmentInventory()->getBodyArmor(equipmentChoice));

								if (success == 2) {
									aquireTargetBodyArmor(hmMenu_->getInput());
									success = 1;
								}

							break;

							case 3:
								success = getHero(hmMenu_->getInput())->wearLegArmor(getHero(hmHeroBeingManaged_)->getEquipmentInventory()->getLegArmor(equipmentChoice));

								if (success == 2) {
									aquireTargetLegArmor(hmMenu_->getInput());
									success = 1;
								}

							break;

							case 4:
								success = getHero(hmMenu_->getInput())->wearRing(getHero(hmHeroBeingManaged_)->getEquipmentInventory()->getRing(equipmentChoice));

								if (success == 2) {
									aquireTargetRing(hmMenu_->getInput());
									success = 1;
								}

							break;

							case 5:
								success = getHero(hmMenu_->getInput())->wearNecklace(getHero(hmHeroBeingManaged_)->getEquipmentInventory()->getNecklace(equipmentChoice));

								if (success == 2) {
									aquireTargetNecklace(hmMenu_->getInput());
									success = 1;
								}

							break;


							default:
								cout << "No item type specified";
							break;
						}
					}
				break;

				case 2:

					/* Display the stats of the selected item */
					getHero(hmHeroBeingManaged_)->getEquipmentInventory()->displayEquipmentStats(equipmentChoice);

					/* Formatting */
					cout << endl;
					
					/* Pause the game */
					system("pause");

				break;

				case 3:

					/* Drop the item that the user picked */
					getHero(hmHeroBeingManaged_)->getEquipmentInventory()->dropItem(equipmentChoice);

					/* Break the loop */
					success = 1;
				break;

				case 4:

					hmMenu_->takeInput("What hero would you like to move this item to?\n" + returnPartyNames(1), "You didn't pick a hero.", hmTotalHeroes_, 1);
					
					if (hmMenu_->inputIsErrorNumber()) {
						cout << "You have chosen to move this item to nobody.\n\n";
					}
					else {

						/* Put the input on the programmer level */
						hmMenu_->convertInputProgrammerLevel();

						targetHero = hmMenu_->getInput();

						/* Get the item type of the selected item */
						itemType = getHero(hmHeroBeingManaged_)->getEquipmentInventory()->getItemType(equipmentChoice);

						/* Set the user equipment choice to the programmer array access level */
						getHero(hmHeroBeingManaged_)->getEquipmentInventory()->setEquipmentNumber(equipmentChoice);
						
						/* Put the item in the inventory of the proper hero */
						switch (itemType) {
							case 0:

								/* Add the item from the selected hero to the new hero. */
								getHero(hmMenu_->getInput())->getEquipmentInventory()->addWeapon(getHero(hmHeroBeingManaged_)->getEquipmentInventory()->getWeapon(equipmentChoice));

								/* Remove the item from the original hero. */
								getHero(hmHeroBeingManaged_)->getEquipmentInventory()->dropItem(equipmentChoice);
								
								/* Display success message */
								cout << "You successfully transferred the item.\n\n";

							/* Break the case statement */
							break;

							case 1:

								getHero(hmMenu_->getInput())->getEquipmentInventory()->addShield(getHero(hmHeroBeingManaged_)->getEquipmentInventory()->getShield(equipmentChoice));
								getHero(hmHeroBeingManaged_)->getEquipmentInventory()->dropItem(equipmentChoice);
								cout << "You successfully transferred the item.\n\n";
							break;

							case 2:

								getHero(hmMenu_->getInput())->getEquipmentInventory()->addBodyArmor(getHero(hmHeroBeingManaged_)->getEquipmentInventory()->getBodyArmor(equipmentChoice));
								getHero(hmHeroBeingManaged_)->getEquipmentInventory()->dropItem(equipmentChoice);
								cout << "You successfully transferred the item.\n\n";
							break;

							case 3:

								getHero(hmMenu_->getInput())->getEquipmentInventory()->addLegArmor(getHero(hmHeroBeingManaged_)->getEquipmentInventory()->getLegArmor(equipmentChoice));
								getHero(hmHeroBeingManaged_)->getEquipmentInventory()->dropItem(equipmentChoice);
								cout << "You successfully transferred the item.\n\n";
							break;

							case 4:

								getHero(hmMenu_->getInput())->getEquipmentInventory()->addRing(getHero(hmHeroBeingManaged_)->getEquipmentInventory()->getRing(equipmentChoice));
								getHero(hmHeroBeingManaged_)->getEquipmentInventory()->dropItem(equipmentChoice);
								cout << "You successfully transferred the item.\n\n";
							break;

							case 5:

								getHero(hmMenu_->getInput())->getEquipmentInventory()->addNecklace(getHero(hmHeroBeingManaged_)->getEquipmentInventory()->getNecklace(equipmentChoice));
								getHero(hmHeroBeingManaged_)->getEquipmentInventory()->dropItem(equipmentChoice);
								cout << "You successfully transferred the item.\n\n";
							break;

							default:

								cout << "No item type specified";
							break;
						}
					}

				break;

				case 5:

					/* The suer wants to exit so simply to set success to 1. */
					success = 1;
				break;

				default:

					cout << "You have chose no action.\n";
				break;
			}
		}
	}
}



void HeroManager::aquireTargetWeapon(int targetHero)
{
	/*Variable Declarations */
	int keptItem;

	/* Let the user choose the slot to empty */
	hmMenu_->takeInput("Which slot would you like to empty (1 or 2):   ", "You did not choose a slot", 2, 0);

	if (hmMenu_->getInput() == 1) {

		/* Aquire the item from that slot */
		keptItem = aquireWeapon("Dequiped and now being managed: ", getHero(targetHero)->getFullEquipment()->getSlot1()->getWeapon());

		/* If the hero kept the item. */
		if (keptItem == 1) {

			/* Then clear out the original item from the hero we are managing. */
			getHero(hmHeroBeingManaged_)->clearSlot(1);
		}
	}
	else {
		keptItem = aquireWeapon("Dequiped and now being managed: ", getHero(targetHero)->getFullEquipment()->getSlot2()->getWeapon());
		if (keptItem == 1) {
			getHero(hmHeroBeingManaged_)->clearSlot(2);
		}
	}
}

void HeroManager::aquireTargetShield(int targetHero)
{
	int keptItem;
	keptItem = aquireShield("Dequiped and now being managed: ", getHero(targetHero)->getFullEquipment()->getSlot2()->getShield());
	if (keptItem == 1) {
		getHero(hmHeroBeingManaged_)->clearSlot(2);
	}
}

void HeroManager::aquireTargetBodyArmor(int targetHero)
{
	int keptItem;
	keptItem = aquireBodyArmor("Dequiped and now being managed: ", getHero(targetHero)->getFullEquipment()->getSlot3()->getBodyArmor());
	if (keptItem == 1) {
		getHero(hmHeroBeingManaged_)->clearSlot(3);
	}
}

void HeroManager::aquireTargetLegArmor(int targetHero)
{
	int keptItem;
	keptItem = aquireLegArmor("Dequiped and now being managed: ", getHero(targetHero)->getFullEquipment()->getSlot4()->getLegArmor());
	if (keptItem == 1) {
		getHero(hmHeroBeingManaged_)->clearSlot(4);
	}
}

void HeroManager::aquireTargetRing(int targetHero)
{
	int keptItem;
	hmMenu_->takeInput("Which slot would you like to empty (1 or 2):   ", "You did not choose a slot", 2, 0);
	if (hmMenu_->getInput() == 1) {
		keptItem = aquireRing("Dequiped and now being managed: ", getHero(targetHero)->getFullEquipment()->getSlot5()->getRing());
		if (keptItem == 1) {
			getHero(hmHeroBeingManaged_)->clearSlot(5);
		}
	}
	else {
		keptItem = aquireRing("Dequiped and now being managed: ", getHero(targetHero)->getFullEquipment()->getSlot6()->getRing());
		if (keptItem == 1) {
			getHero(hmHeroBeingManaged_)->clearSlot(6);
		}
	}
}

void HeroManager::aquireTargetNecklace(int targetHero)
{
	int keptItem;
	keptItem = aquireNecklace("Dequiped and now being managed: ", getHero(targetHero)->getFullEquipment()->getSlot7()->getNecklace());
	if (keptItem == 1) {
		getHero(hmHeroBeingManaged_)->clearSlot(7);
	}
}



