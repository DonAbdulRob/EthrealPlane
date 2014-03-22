#include "battle.h"
#include "world.h"
#include "life.h"
#include "fighter.h"
#include "heroManager.h"
#include "userinput.h"
#include "item.h"
#include "allInventories.h"
#include "inventory.h"
#include "lifeRepeatable.h"
#include "attributes.h"
#include "states.h"

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <list>

/* Constructor */
Battle::Battle(HeroManager *&newParty, FileItems *fileItems)
{
	/* Variable Declarations and initializations */
	enemy_ = new Opponent[4];
	heroParty_ = new HeroManager;
	fighter_ = new Fighter[8];
	fileItems_ = new FileItems;
	menu_ = new MenuInput;

	fileItems_ = fileItems;

	totalEnemies_ = 0;
	totalBattlers_ = 0;
	currentRound_ = 1;
	currentFighter_ = 0;
	heroTarget_ = 0;
	hasFled_ = 0;
	mainHeroDied_ = 0;

	/* Set bHeroParty to POINT to what the pointer to the hero party being passed in is pointing at. */
	heroParty_ = newParty;

	/* Create Enemies */
	createEnemies();

	/* Clear the screen */
	system("cls");
}

void Battle::createEnemies()
{
	/* Variable Declarations and initializations */
	int nameChangeCount = 0;

	/* Generate random amount of enemies based on main hero level and total party size. */ 
    if ((heroParty_->getMainHero()->getLevel() > 15) || (heroParty_->getTotalHeroes() == 4))
        totalEnemies_ = 3;
    else if ((heroParty_->getMainHero()->getLevel() > 5) || (heroParty_->getTotalHeroes() > 1))
        totalEnemies_ = 2;
	else
	    totalEnemies_ = 1;
	
	/* Create the enemy_. Generate stats. Then assign important stats to key variables */
	for (int i = 0; i < totalEnemies_; i++) {
			enemy_[i].generateRandomOpponent(heroParty_->getMainHero()->getLevel());
			enemy_[i].modifyStrength(.50);
	}

	/* Set total battlers */
	totalBattlers_ = heroParty_->getTotalHeroes() + totalEnemies_;

	/* Change enemy_ names to number enemies that have the same name. */
	for (int j = 0; j < totalEnemies_; j++) {
		for (int k = 0; k < totalEnemies_; k++) {
			if (j < k) {
				if (enemy_[j].getName() == enemy_[k].getName()) {
					if (nameChangeCount == 0) {
						enemy_[k].setName((enemy_[k].getName()).append(" 2"));
						nameChangeCount++;
					}
					else if (nameChangeCount == 1) {
						enemy_[k].setName((enemy_[k].getName()).append(" 3"));
						nameChangeCount++;
					}
					else if (nameChangeCount == 2) {
						enemy_[k].setName((enemy_[k].getName()).append(" 4"));
						nameChangeCount++;
					}
				}
			}
		} /* End k loop */
		nameChangeCount = 0;
	} /* End j loop */

}

void Battle::displayEncounterMessage()
{
	/* Encounter message */
	cout << "You have encountered " << totalEnemies_;

	/* Display proper suffix (s) */
	if (totalEnemies_ == 1)
		cout << " opponent";
	else
		cout << " opponents";

	/* End message */
	cout << "!!!\n";
	
	/* Then display the level and name of all the enemies */
	for (int i = 0; i < totalEnemies_; i++)
		cout << "Level " << enemy_[i].getLevel() << " " << enemy_[i].getName() << "\n";
}

/* Handles fights between randomly generated adventurers while the player is exploring */
void Battle::fight()
{
	/* Declare Variables */
	bool keepBattling = 1;
	int playersWhoTookTurn = 0;
	int newRound = 0;
	int x = 0; /* x will store the player number for who is taking the current turn */
	int count = 0;

	list<Fighter> turnOrder; /* Create List */
	list<Fighter>::iterator it; /* Declare iterator to move through list */

	/* Display an encounter message */
	displayEncounterMessage();

	/* Battle Loop */
    while (keepBattling == 1) {

		/*****
		  I - read documentation at bottom to understand the bTurnOrder_Manager function
			 -Make sure that bTurnOrder_ is calculated at the start of a battle. 
		*****/

		/* If it's the first round then we need to set newRound to 1 so that the turn Order is calculated at the start. Also initialize the count to 0. */
		if (currentRound_ == 1) {
			newRound = 1;
			playersWhoTookTurn = 0;
		}
		/* If the last player just took his turn, then reset the index so all player take turns again and set newRond to true */
		else if (playersWhoTookTurn == (totalBattlers_)) {
			/* Increase round */
			currentRound_++;

			/* Increase and Display round */
			cout << "Next Round! Current Round: " << currentRound_ << ".\n";
		
			/* Formatting */
			system("pause");

			/* Set new round to true */
			newRound = 1;

			/* Reset the counter */
			playersWhoTookTurn = 0;
		}
		/* If it's not the last players turn, increase playersWhoTookTurn to show that a player has (well, is about to realistically) taken their turn. */
		else
			playersWhoTookTurn++;



		/*******
		   II. - Calculate turn order if it's a new round.
		********/

		/* If it's a newRound, then we will calculate the turn order */
		if (newRound == 1) {

			/* Set that the new round is over */
			newRound = 0;
		
			/* 1. Clear list of turnorders. */
			turnOrder.clear();

			/* 2. Calculate who goes first based on dexterity. */

			/* Store information about all living players into fighter_. */
			for (int i = 0; i < totalBattlers_; i++) {
				if ((i >= 0) && (i < heroParty_->getTotalHeroes())) {
					if (heroParty_->getHero(i)->getCreated() == 1) {
						fighter_[count].setDexterity(heroParty_->getHero(i)->getTotalLifeRepeatable()->getAttributes()->getAttribute(2));
						fighter_[count].setPlayerNumber(i);
						count++;
					}
				}
				else if ((i >= heroParty_->getTotalHeroes()) && (i < totalBattlers_)) {
					fighter_[count].setDexterity(enemy_[i-heroParty_->getTotalHeroes()].getTotalLifeRepeatable()->getAttributes()->getAttribute(2));
					fighter_[count].setPlayerNumber(i);
					count++;
				}
			}

			/* Populate list with fighter_s */
			for (int i = 0; i < totalBattlers_; i++) {
				turnOrder.push_back(fighter_[i]);
			}

			/* Sort List of Fighters */
			turnOrder.sort();

			/* Reverse order of fighter_s so that it goes from highest to lowerst */
			turnOrder.reverse();
		}
	
		/**********
			III.  - Account for States
		**********/

		/* empty for now */

		/**********
			IV.  - Let Players Take Turns
		**********/

		/* So now we have a bunch of sorted Battle Fighters in the list...
			Read out the battle fighters (class object) position (variable) 1 by 1 so they
			take their turn  */
		for (it = turnOrder.begin(); it != turnOrder.end(); it++) {

			/* Only keep reading from the list if the user hasn't fled the batttle */
			if ((hasFled_ == 0) && (keepBattling == 1)) {

				/* Store player number into x. Doing this increases code readability. */
				x = (*it).getPlayerNumber();

				/* If the currentFighter is 0-3 (a hero)... */
				if ((x >= 0) && (x < heroParty_->getTotalHeroes())) {

					/* If active, then... */
					if (heroParty_->getHero(x)->getTotalLifeRepeatable()->getStates()->getAlive() == 1) {
						
						currentFighter_ = x;

						/* Take turn */
						heroTakeTurn();
					
						/* Formatting */
						cout << endl;
					}	
				}
				/* If the currentFighter is 4-7 (opponent)... */
				else  {
				
					/* Decrease by totalHeroesMinus one to set to Enemy array access level */
					x -= heroParty_->getTotalHeroes();

					/* If the Opponent is active, then take turn */
					if (enemy_[x].getTotalLifeRepeatable()->getStates()->getAlive() == 1) {

						/* Decrease by heroParty_->getTotalHeroes()Minus one to set to enemy_ array access level */
						currentFighter_ =  x;

						/* Take turn */
						computerTakeTurn();
					
						/* Formatting */
						cout << endl;
					}
				}
			}
		
			/* If still battling, determine whether to keep battling or not */
			if (keepBattling == 1)
				keepBattling = handleDeath();

		} /* List reading for loop */
	}
}

/* Lets heroes choose what action they will perform based on user input */
void Battle::heroTakeTurn()
{	
	/* Variable Declarations */
	
	bool keepLooping = 1;
	int genFleeChance;
	
	/* Formatting */
	cout << endl;

	/******************************
	  Display battle statistics.
	******************************/

	/* Display the the hero name of the current fighter. */
	cout << "--- Hero " << heroParty_->getHero(currentFighter_)->getName() << "'s turn --- \n";

	/* Display hero information */
	showHeroPartyInformation();

	/* Display enemy_ Information */
	showEnemyPartyInformation();

	/* Formatting */
	cout << endl;

	/************************************
	  Handle User Input/Hero Actions
	************************************/
	
	/* Take user input on what he would like to do */
	

	/* Keep looping while the hero doesn't perform an action */
	while (keepLooping == 1) {

		/* Get user input */
		menu_->takeInput("What would you like to do?\n 1.) Attack\n 2.) Cast Magic -- Doesn't Work\n 3.) Flee: ", "Please select a valid action.", 3, 0);

		/* Formatting */
		cout << endl;

		 /* Future features 3 - Use Item, 4 - Equip, 5 - Defend, 6 - */

		/* If the user entered 1, then attack */
		if (menu_->getInput() == 1) {
			keepLooping = heroAttack();
		}
		/* If 2, then Cast Spell */
		else if (menu_->getInput() == 2) {
			cout << "Doesn't work yet.\n";
			keepLooping = 1;
		}
		/* If 3, then flee */
		else if (menu_->getInput() == 3) {
			
			/* Generate a value from 1-100. */ 
			genFleeChance = (rand() % 100) + 1;

			/* If less than 30, set hasFled_ true to end the battle! */
			if (genFleeChance < 30) {
				/* Set has fled to true to prevent further player turns */
				hasFled_ = 1;
				/* Break the loop */
				keepLooping = 0;
				/* Tell the player that he/she successfully fled the battle */
				cout << "You have successfully fled from the battle!\n";
			}
			/* Else if the value was >= 30, then keep battle and display failure message */
			else {
				/* Break the loop */
				keepLooping = 0;

				/* Display escape failure message */
				system("cls");
				cout << "You failed to escape!\n";
				system("pause");
			}
		}
	} /* End While Loop */
}

/* Generates Computer Actions */
void Battle::computerTakeTurn()
{
	/* Variable Declarations */
	int genAction;

	/******************************
		Handle Computer Actions
	******************************/

	/*Generate a random action for the computer to perform */
	genAction = rand() % 101 + 1;

	/* Perform that action */
	if ((genAction > 0) && (genAction <= 101))
		enemyAttack();
	/* Spell Cast -- else if (pickAction > 50) && (computerAction <= 100) cCast(Hero[0],enemy_); */
	/* Flee -- else if (pickAction == 101) endBattle = cFlee(Hero[0],enemy_); */
}

/* Handles attack called in the playerTakeTurn function */
bool Battle::heroAttack()
{
	/* Variable Declarations */
	string message;
	int realDamage = 0;

	/**************************************************************
	Determine the enemies that are targetable or not
	Let user select from targetable enemies.
	If the targetted enemy_ is alive, then attack that enemy_.
	**************************************************************/

	/* Set abstract value canTarget based on enemy physicalTargetable state */

	/* If the hero has not exited, then attack */
	if (getUserTarget() == 0) {
		
		/* Set real damage based on min and max damage of hero */
		realDamage = (rand() %
			(heroParty_->getHero(currentFighter_)->getTotalLifeRepeatable()->getPhysicalDamageMaximum() - heroParty_->getHero(currentFighter_)->getTotalLifeRepeatable()->getPhysicalDamageMinimum())
					 ) +heroParty_->getHero(currentFighter_)->getTotalLifeRepeatable()->getPhysicalDamageMinimum();

		/* Deal Damage to Target */
		enemy_[heroTarget_].decreaseCurrentHitPoints(realDamage);

		/* Formatting */
		system("cls");

		/* Display damage dealt message */
		cout << heroParty_->getHero(currentFighter_)->getName() << " deals " << realDamage << " damage to " << enemy_[heroTarget_].getName() << endl;

		/* Return 0 to break the loop */
		return 0;
	}

	/* Return 1 to keep looping by default. */
	return 1;
}

/* Gets user input on who they want to target. Also makes sure that the target is the REAL target. */
bool Battle::getUserTarget()
{
	/* Variable Declarations */
	string message = "";
	bool keepLooping = 1;
	bool canTarget[4];
	int userChoice = 0;
	int totalTargetableEnemies = 0;

	/* Use loop to set the enemies that are targetable */
	for (int i = 0; i < totalEnemies_; i++) {
		if (enemy_[i].getTotalLifeRepeatable()->getStates()->getPhysicalTargetable() == 1) {
			totalTargetableEnemies++;
			canTarget[i] = 1;
		}
		else
			canTarget[i] = 0;
	}

	/************************************************************
	 Set the message to menu list of heroes that are targetable
	*************************************************************/
	
	/* Variable Declarations */
	bool append1 = 0;
	bool append2 = 0;
	bool append3 = 0;

	/* Begin forming message for user input template */
	message = "Who would you like to target?\n ";

	/* Display targetable enemies */
	for (int i = 0; i < totalEnemies_; i++) {
		if (canTarget[i] == 1) {
			if (append1 == 0) {
				message.append("1.) " + enemy_[i].getName()) + "\n";
				append1 = 1;
			}
			else if (append2 == 0) {
				message.append("\n 2.) " + enemy_[i].getName()) + "\n";
				append2 = 1;
			}
			else if (append3 == 0) {
				message.append("\n 3.) " + enemy_[i].getName()) + "\n";
				append3 = 1;
			}
			else
				message.append("\n 4.) " + enemy_[i].getName()) + "\n";
		}
	}

	while (keepLooping == 1) {		
		/* Get user hero selection */
		menu_->takeInput(message, "You did not select a targetable Enemy. ", totalTargetableEnemies, 1);

		/* Use Algorithm to determine real user target (can be viewed at bottom) */
		if (menu_->inputIsErrorNumber()) {
			keepLooping = 0;
			return 1;
		}
		else {
			if (menu_->getInput() == 1) {
				if (canTarget[0] == 1) {
					heroTarget_ = 0;
					keepLooping = 0;
				}
				else if (canTarget[1] == 1) {
					heroTarget_ = 1;
					keepLooping = 0;
				}
				else if (canTarget[2] == 1) {
					heroTarget_ = 2;
					keepLooping = 0;
				}
				else if (canTarget[3] == 1) {
					heroTarget_ = 3;
					keepLooping = 0;
				}
				else {
					cout << "You are unable to target this monster due to it being dead or in an unattackable state.\n\n";
					system("pause");
				}
			}
			else if (menu_->getInput() == 2) {
				if (canTarget[1] == 1) {
					heroTarget_ = 1;
					keepLooping = 0;
				}
				else if (canTarget[2] == 1) {
					heroTarget_ = 2;
					keepLooping = 0;
				}
				else if (canTarget[3] == 1) {
					heroTarget_ = 3;
					keepLooping = 0;
				}
				else {
					cout << "You are unable to target this monster due to it being dead or in an unattackable state.\n\n";
					system("pause");
				}
			}
			else if (menu_->getInput() == 3) {
				if (canTarget[2] == 1) {
					heroTarget_ = 2;
					keepLooping = 0;
				}
				else if (canTarget[3] == 1) {
					heroTarget_ = 3;
					keepLooping = 0;
				}
				else {
					cout << "You are unable to target this monster due to it being dead or in an unattackable state.\n\n";
					system("pause");
				}
			}
			else if (menu_->getInput() == 4) {
				if (canTarget[4] == 1) {
					heroTarget_ = 3;
					keepLooping = 0;
				}
				else {
					cout << "You are unable to target this monster due to it being dead or in an unattackable state.\n\n";
					system("pause");
				}
			}
		}
	}

	/* UM, THIS COuLD FUCK SHIT UP */
	return 0;
}

/* Handles enemy_ attacks called by enemy_TakeTurn fuction */
void Battle::enemyAttack()
{	
	/* Variable Declarations */
	bool keepLooping = 1;
	int enemyTarget = 0;
	int totalRandomDamage = 0;
	int realDamage;

	/* Set Damage based on the current fighting enemies minimum and maximum damage */
	realDamage = (rand() % 
		(enemy_[currentFighter_].getTotalLifeRepeatable()->getPhysicalDamageMinimum() + enemy_[currentFighter_].getTotalLifeRepeatable()->getPhysicalDamageMaximum())
				 ) + enemy_[currentFighter_].getTotalLifeRepeatable()->getPhysicalDamageMinimum();

	/* If dealing 0 damage, then display message */
	if (realDamage < 1) {
		realDamage = 1;
		cout << "Something probably went wrong! Monster dealing 0 damage.";
	}

	/* If only one hero left, then it must be the main hero. So set the target to the main hero. */
	if (heroParty_->getTotalHeroes() == 1)
		enemyTarget = 0;
	/* If there are more than one hero, pick one of the living ones. */
	else {
        /* Keep looping while the number isn't in the range of (-1, (totalHeroes-1)) */
		while (keepLooping == 1) {
			
			/* Randomly generate target */
			enemyTarget = (rand() % heroParty_->getTotalHeroes());
			
			/* Check to make sure hero is in proper range. End loop if it is. */
			if ((enemyTarget > -1) && (enemyTarget < (heroParty_->getTotalHeroes()-1))) {

				/* If the Party Hero is alive, end the loop */
				if (heroParty_->getHero(enemyTarget)->getBaseLifeRepeatable()->getStates()->getAlive() == 1)
					keepLooping = 0;
			}
		}
	}
		
	/* Deal Damage */
	heroParty_->getHero(enemyTarget)->decreaseCurrentHitPoints(realDamage);

	/* Display Attack Message */
    cout << enemy_[currentFighter_].getName() << " has attacked " << heroParty_->getHero(enemyTarget)->getName() << " for " << realDamage << " damage";
}

/* Displays Hero Name + Hit Points + Mana Points */
void Battle::showHeroPartyInformation()
{	
	/* Variable Declarations */
	int menuDisplayCount = 1;

	/* Begin displaying */
	cout << "Heroes: \n";

	/* Perform loop to display every heroes information */
	for (int i = 0; i < heroParty_->getTotalHeroes(); i++) {

		/* If the party member is alive, then... */
		if (heroParty_->getHero(i)->getBaseLifeRepeatable()->getStates()->getAlive() == 1) {

			/* Display the party information */
			cout << " " << menuDisplayCount << ".) Hero " << heroParty_->getHero(i)->getName() << " (" << heroParty_->getHero(i)->getCurrentHitPoints() << "," << heroParty_->getHero(i)->getTotalLifeRepeatable()->getMaximumHitPoints() << ") (";
			cout << heroParty_->getHero(i)->getCurrentManaPoints() << "," << heroParty_->getHero(i)->getTotalLifeRepeatable()->getMaximumManaPoints() << ")\n";

			/* Increase the menu Display count */
			menuDisplayCount++;
		}
	}

	/* More formatting */
	cout << endl;
}

/* Displays enemy_ Name + Hit Points + Mana Points */
void Battle::showEnemyPartyInformation()
{
	/* Variable Declarations */
	int livingEnemies = 0;
	int count = 1;

	/* Determine total amount of living enemies */
	for (int i = 0; i < 4; i++) {
		if (enemy_[i].getTotalLifeRepeatable()->getStates()->getAlive())
			livingEnemies++;
	}

	/* Display enemy_ battle statistics */
	cout << "Enemies: \n";
	for (int i = 0; i < totalEnemies_; i++) {
		if (enemy_[i].getCreated() == 1) {
			cout << " " << count <<	".) " << enemy_[i].getName() << " (" << enemy_[i].getCurrentHitPoints() << ",";
			cout << enemy_[i].getTotalLifeRepeatable()->getMaximumHitPoints() << ") (" << enemy_[i].getCurrentManaPoints() << ",";
			cout << enemy_[i].getTotalLifeRepeatable()->getMaximumManaPoints() << ")\n";
			count++;
		}
	} /* end for loop */
}

/* Gathers experience to give to the heroes */
void Battle::collectExperience()
{
    /* Variable declarations */
	int expGainTotal = 0;

	/* Initialize expGainTotal */
	for (int i = 0; i < totalEnemies_; i++)
		expGainTotal = expGainTotal + enemy_[i].getExperience();
	
	/* Pause and clear */
	system("pause");
	system("cls");

	/* Display victory message */
	cout << "You are victorious in battle!\n";

	/* Display who was slain */
	cout << "Slain:\n ";
	for (int j = 0; j < totalEnemies_; j++) {
		cout << enemy_[j].getName() << "\n";
		if (j < (totalEnemies_ - 1))
			cout << " ";
	}
	
	cout << "\n";

	/* Give experience to the hero and/or party members that fought. */
	heroParty_->giveExperience(expGainTotal);
}

/* Increases hero gold */
void Battle::collectGold()
{		
	/* Variable Declarations */
    int totalGold = 0;

	/* Increase total gold by the amount of gold each monster has */
    for (int i = 0; i < totalEnemies_; i++)
        totalGold += enemy_[i].getGold();
    
	/* Give the gold to the hero */
	heroParty_->getMainHero()->increaseGold(totalGold);

	/* Display the amount of gold won */
	cout << "You have won " << totalGold << " gold for your victory!\n\n";
}

void Battle::collectItem()
{
	/* Variable Declarations */
	bool itemDropped = 0;
    bool genSocket1 = 0;
	bool genSocket2 = 0;
	int genSocket = 0;

	int itemDropChance = 0;
	int enemyAverageLevel = 0;
	int itemNumber = 0;
	int genItemType = 0;
	int genRarity = 1;
	int genBag = 0;
	int itemType = 0;

	Weapon *weaponDrop = new Weapon;
	Shield *shieldDrop = new Shield;
	BodyArmor *bodyArmorDrop = new BodyArmor;
	LegArmor *legArmorDrop = new LegArmor;
	Ring *ringDrop = new Ring;
	Necklace *necklaceDrop = new Necklace;

	/* Give every enemy_ a chance to drop an item */
	for (int i = 0; i < totalEnemies_; i++) {

		/* Generate a random value from 1-100 */
		itemDropChance = (rand() % 100) + 1;

		/* If the value is >= 15, then hero gets item */
		if (itemDropChance >= 1) { //15
		
			/* First we store the total enemy total levels */
			for (int i = 0; i < totalEnemies_; i++) {
				enemyAverageLevel += enemy_[i].getLevel();
			}

			/* Then we calculate the average of these levels */
			enemyAverageLevel = enemyAverageLevel / totalEnemies_;

			/* Next, we generate the item type (weapon, equipment, etc.) */
		
			/* Generate whether it's consumable or weapon */
			genBag = 1; //rand() % 1
		
			/* If genbag = 1, then... It's an equipment */
			if (genBag == 1) {

				/* Based on the average level, we determine the strength of item the hero can get as a drop */
				if (enemyAverageLevel <= 5)
					itemNumber = 0;
				else if (enemyAverageLevel <= 10)
					itemNumber = rand() % 1 + 1;
				else if (enemyAverageLevel <= 15)
					itemNumber = rand() % 2 + 1;
				else if (enemyAverageLevel <= 20)
					itemNumber = rand() % 3 + 2;
				else if (enemyAverageLevel <= 30)
					itemNumber = rand() % 4 + 3;
				else if (enemyAverageLevel <= 40)
					itemNumber = rand() % 5 + 4;
				else if (enemyAverageLevel <= 50)
					itemNumber = rand() % 6 + 5;
				else if (enemyAverageLevel <= 60)
					itemNumber = rand() % 7 + 6;
				else if (enemyAverageLevel <= 70)
					itemNumber = rand() % 8 + 7;
				else if (enemyAverageLevel <= 80)
					itemNumber = rand() % 9 + 8;
				else if (enemyAverageLevel <= 90)
					itemNumber = rand() % 10 + 9;
				else if (enemyAverageLevel <= 100)
					itemNumber = rand() % 11 + 10;
				else if (enemyAverageLevel <= 120)
					itemNumber = rand() % 12 + 10;
				else if (enemyAverageLevel <= 140)
					itemNumber = rand() % 13 + 11;
				else if (enemyAverageLevel <= 160)
					itemNumber = rand() % 14 + 12;
				else if (enemyAverageLevel <= 180)
					itemNumber = rand() % 15 + 13;
				else if (enemyAverageLevel <= 200)
					itemNumber = rand() % 16 + 14;
				else if (enemyAverageLevel <= 225)
					itemNumber = rand() % 17 + 14;
				else if (enemyAverageLevel <= 250)
					itemNumber = rand() % 18 + 15;
				else if (enemyAverageLevel <= 300)
					itemNumber = rand() % 19 + 1;

				/* Now we generate whether or not the item will have sockets */
				
				genSocket = rand() % 1;
				if (genSocket == 1)
					genSocket1 = 1;
				else 
					genSocket1 = 0;
				
				genSocket = rand() % 1;
				if (genSocket == 1)
					genSocket2 = 1;
				else
					genSocket2 = 0;

				/* Finally we generate a rarity of the item */
				genRarity = rand() % 10000 + 1;

				if (genRarity > 5000) {
					genRarity = 0;
				}
				else if (genRarity > 2000) {
					genRarity = 1;
				}
				else if (genRarity > 500) {
					genRarity = 2;
				}
				else if (genRarity > 20) {
					genRarity = 3;
				}
				else if (genRarity > 2) {
					genRarity = 4;
				}
				else if (genRarity == 1) {
					cout << "GODLY QUALITY ITEM FOUND!!!\n";
					system("pause");
					genRarity = 5;
				}

				/* Now we generate what type of equipment it will be -- (weapon, shield, bodyarmor, leg armor, ring, necklace)  */
				itemType = 0; //rand() % 5

				//cout << itemType << " \n";
				//system("pause");

				switch (itemType) {
					case 0:

						/* Set the dropped weapon to weapon[itemNumber] from weapons.txt */
						weaponDrop = fileItems_->getEquipmentInventory()->getWeapon(itemNumber);

						/* Set the sockets and rarity of the item */
						weaponDrop->setSocketsAndRarity(genRarity, genSocket1, genSocket2);

						/* We acquire the new generated item type of item number */
						heroParty_->aquireWeapon("Monster dropped a ", weaponDrop);

						/* Save that an item was dropped */
						itemDropped = 1;

						/* Break this case statement */
						break;
					case 1:

						/* Set the dropped weapon to weapon[itemNumber] from weapons.txt */
						shieldDrop = fileItems_->getEquipmentInventory()->getShield(itemNumber);

						/* Set the sockets and rarity of the item */
						shieldDrop->setSocketsAndRarity(genRarity, genSocket1, genSocket2);

						/* We acquire the new generated item type of item number */
						heroParty_->aquireShield("Monster dropped a ", shieldDrop);

						/* Save that an item was dropped */
						itemDropped = 1;

						/* Break this case statement */
						break;
					case 2:

						/* Set the dropped weapon to weapon[itemNumber] from weapons.txt */
						bodyArmorDrop = fileItems_->getEquipmentInventory()->getBodyArmor(itemNumber);

						/* Set the sockets and rarity of the item */
						bodyArmorDrop->setSocketsAndRarity(genRarity, genSocket1, genSocket2);

						/* We acquire the new generated item type of item number */
						heroParty_->aquireBodyArmor("Monster dropped a ", bodyArmorDrop);

						/* Save that an item was dropped */
						itemDropped = 1;

						/* Break this case statement */
						break;
					case 3:

						/* Set the dropped weapon to weapon[itemNumber] from weapons.txt */
						legArmorDrop = fileItems_->getEquipmentInventory()->getLegArmor(itemNumber);

						/* Set the sockets and rarity of the item */
						legArmorDrop->setSocketsAndRarity(genRarity, genSocket1, genSocket2);

						/* We acquire the new generated item type of item number */
						heroParty_->aquireLegArmor("Monster dropped a ", legArmorDrop);

						/* Save that an item was dropped */
						itemDropped = 1;

						/* Break this case statement */
						break;
					case 4:

						/* Set the dropped weapon to weapon[itemNumber] from weapons.txt */
						ringDrop = fileItems_->getEquipmentInventory()->getRing(itemNumber);

						/* Set the sockets and rarity of the item */
						ringDrop->setSocketsAndRarity(genRarity, genSocket1, genSocket2);

						/* We acquire the new generated item type of item number */
						heroParty_->aquireRing("Monster dropped a ", ringDrop);

						/* Save that an item was dropped */
						itemDropped = 1;

						/* Break this case statement */
						break;
					case 5:

						/* Set the dropped weapon to weapon[itemNumber] from weapons.txt */
						necklaceDrop = fileItems_->getEquipmentInventory()->getNecklace(itemNumber);

						/* Set the sockets and rarity of the item */
						necklaceDrop->setSocketsAndRarity(genRarity, genSocket1, genSocket2);

						/* We acquire the new generated item type of item number */
						heroParty_->aquireNecklace("Monster dropped a ", necklaceDrop);

						/* Save that an item was dropped */
						itemDropped = 1;

						/* Break this case statement */
						break;
					default:
						cout << "Invalid ItemType Generated! Random Generation Failure.\n";
						system("pause");
						break;
				}
			}
			/* Else, It's consumable */
			else {
				/* Based on the average level, we determine the strength of item the hero can get as a drop */
				if (enemyAverageLevel <= 5)
					itemNumber = 1;
				else if (enemyAverageLevel <= 10)
					itemNumber = 2;
				else if (enemyAverageLevel > 10)
					itemNumber = 3;
			}
		}
	}

	/* If an item wasn't dropped then display a message that one wasn't */
	if (itemDropped == 0)
		cout << "No item was dropped.\n";
}

/* Updates whether or not a player is dead or alive */
/* Tells the loop to keep going or to stop based on whether A.) The main Hero died, B.) All Party Members are dead and C.) All Enemies are dead */
bool Battle::handleDeath()
{	
	/* Variable Declarations */
	bool enemyAlive = 0;
	bool heroAlive = 0;

	/* Check if the main hero is still alive. If dead, stop battling.
		The Main hero is the only check to see if the battle should end due to a hero death.*/

	/* Check Main Hero to see if he/she died or not. */
	/* then If the main hero has less than or equal to 0 hit points... */
	if (heroParty_->getMainHero()->getCurrentHitPoints() <= 0) {
		
		enemyAlive = 0;
		heroAlive = 0;

		/* Set hasFled_ to true to end the battle */
		hasFled_ = 1;

		/* Set that the main hero died */
		mainHeroDied_ = 1;
	}
	else
		/* Or else set heroAlive to true */
		heroAlive = 1;

	/* Enemies */
	for (int i = 0; i < totalEnemies_; i++) {
		
		/* If the enemy_ is alive then continue */
		if (enemy_[i].getTotalLifeRepeatable()->getStates()->getAlive()) {
			
			/* if the enemy_ has less than 0 or less hp, set dead */
			if (enemy_[i].getCurrentHitPoints() <= 0)  {
				
				cout << "An Enemy has been Slain!\n";
				
				enemy_[i].getTotalLifeRepeatable()->getStates()->setAlive(0);
			
			}
			
			/* If any enemy_ has more than 0 hp, save that */
			else
				enemyAlive = 1;
		}
	} /* end hero checking loop */

	/* If all fighters are alive and the hero didn't flee return 1 to keep battling */
	if (hasFled_ == 0) {
		
		/* If all heroes are alive, then we can check the enemy_ state */
		if (heroAlive == 1) {
			
			/* If enemy_ is alive then return 1 to keep battling */ 
			if (enemyAlive == 1)
				
				return 1;
			
			/* else the enemy_ is dead and we want to handle victory */
			else if (enemyAlive == 0) {

				victory();
				
				return 0;
			}
		}
	}
	/* Else if the hero fled, return 0 to break the loop */
	else if (hasFled_ == 1)
		return 0;

	/* Default to keep battling */
	return 1;
}

void Battle::victory() {
	/* No Variable Declarations */

	/* Collect experience, gold, and possibly items */
	collectExperience();
	collectGold();
	collectItem();
}


//cout << "ItemType: " << itemType << "ItemNumber: " << itemNumber << " " << endl;

/********************************************************************************

Algorithm to determine who the REAL USER target is.

User enters target.

Things we know:
	If 1, target 1st living of last 4 enemies. Can be any enemy_.
	If 2, target 1st living of last 3 enemies. Can't be 1st enemy_.
	If 3, target 1st living of last 2 enemies. Can't be 1st or 2nd enemy_.
	If 4, target 1st living of last 1 enemy_. Can't be 1st, 2nd, or 3rd enemy_.

Set enemy_Target to reference to the enemy_ that is active.
Stop the loop if a valid target was selected.
	Else end the loop.

		
*********************************************************************************/


/***************************************************************************

	I.
	
	Every turn we need to increase the current index of the turn order to make sure
	that the next player takes his/her turn. If the current index is equal to the size
	then we need to simply reset the index so that players can take turns again.

	1a. Check to see if the index is equal to the size of the list, then reset the index. If
		the index is reset, then note that a new round has happened.
	1b. Increase the index of bTurnOrder_ every turn.

	II. 
	
	So every time all players have taken a turn (newround == 1), we need to calculate a base turn order.
	This turn order will only be calculated at the beginning of a round.

	1. Reset the list
	2. Calculate who goes first based on dexterity.
	3. Store the newly created bTurnOrder_.
	
	III. 
	
	Every turn we need to check to see if any new buffs were applied. If they were
	then alter bTurnOrder_ to account for them.

	1. Check to see if any new relevant buffs were cast (haste, slow)
	2. Alter to the current bTurnOrder_ list to account for states like haste and slow.
		a. If you are hasted so that you go next, then the bTurnOrder_ is changed
			so that, YOU go next and all of players are shifted down.
		b. If you have a regular speed buff, then make it so dexterity applies
			doubly.
		c. If slowed, then dexterity applies 1/2 as much.
		d. If GLUED, then you will go last.

	

	IV.



	***************************************************************************/

/********************************************************************************
Debugging Statements to to save effort when debugging

1.) - Make sure that all the order values are set to the correct amount

	for (int i4 = 0; i4 < totalBattlers_; i4++) {
		cout << " dexteritybTurnOrder_ " << i4 << ": " << dexteritybTurnOrder_[i4];
		if (i4 != totalBattlers_)
			cout << " | ";
	}

2.) Display totalBattlers_ and pause

	cout << "totalBattlers_: " << totalBattlers_ << endl; system("pause");

3.) display list player stats

	system("cls");
	for (it = bTurnOrder_.begin(); it != bTurnOrder_.end(); it++) {
		cout << "(" << (*it).getDexterity() << ") ";
		cout << "[" << (*it).getPlayerNumber() << "]\n";
	}
	system("pause");

4.) Display the stats of an item being dropped
	
	cout << weaponDrop->getModifiedName() << endl;
	cout << fileItems_->getEquipmentInventory()->getWeapon(itemNumber).getModifiedName() << endl;
	system("pause");


********************************************************************************/