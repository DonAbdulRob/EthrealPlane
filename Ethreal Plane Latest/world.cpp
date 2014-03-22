#include "world.h"

#include "location.h"
#include "heroManager.h"
#include "map.h"
#include "battle.h"
#include "utilities.h"
#include "inventory.h"
#include "item.h"
#include "userinput.h"
#include "battle.h"
#include "allInventories.h"
#include "life.h"
#include "lifeRepeatable.h"
#include "states.h"
#include "attributes.h"

//#include "spell.h"

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

World::World(void)
{
	/* Initialize Variables */
	heroParty_ = new HeroManager;
	map_ = new Map(201, 201, heroParty_->getMainHero()->getCoordinates());
	fileItems_ = new FileItems;
	wMenu_ = new MenuInput;

	fileItems_->readAll();

	/* Populate the world map */
	map_->createMountains(20);
	map_->createTowns();
	
	/* Display introduction message */
	//displayIntroduction();
	//createMainHero();
	//createSpells();

	skipHeroCreation();
}

/* Called by main to display introduction message */
void World::displayIntroduction()
{
	/* No Variable Declarations */

	/* Display introduction message text */
	cout<<"In the Ethreal Plane, you are able to explore the world fighting other\n";
	cout<<"adventurers. Partake in arenas, master skills, and become the best that you can in this game!";
	cout<<" If you need help, simply z to bring up the help display.\n\n";
	
	/* Formatting */
	cout << "\n\n";
    system("pause");

	system("cls");
	cout << "To get you started off, a gift from the heaven's above! GO FORTH AND SLAY!\n";
	
	/* Aquire a new weapon. */
	heroParty_->aquireWeapon("Bestowed a ", fileItems_->getEquipmentInventory()->getWeapon(1));
}

/* Will take a user action to continue execution of the game. Takes actions infinitely. */
void World::takeAction()
{
	/* Variable Declarations */
	Battle *encounter;

	string action;
	bool isEncounter = 0;
	bool badInput = 0;
	bool success = 0;
	int inTown = 0;
	int newPosition[2];

	string key_Up =    "w";
	string key_Down =  "s";
	string key_Left =  "a";
	string key_Right = "d";
	
	string key_Help = "h";
	string key_Save = "n";
	string key_Load = "m";

	string key_PrintStats =    "p";
	string key_ConfigureZoom = "o";

	string key_ManageInventories = "i";

	string key_Teleport = "^";

	/* Heal the hero */
    heroParty_->getMainHero()->fullHeal();

	/* Uncomment later
	cout << "For maximum gaming quality, make window size maximum!\n";
	system("pause"); */

	/* Infinite Loop so that the game runs forever */
	while (true) {
		/* Reset variables to be reevaluated */
        action = "";
		inTown = 0;
		
		/* Formatting */
		system("cls");
		
		if (badInput == 1) {
			cout << "You entered in a key that does nothing!\n";
			badInput = 0;
		}

		/* Display location in coordinate form */
		cout << "Party Location: (" << heroParty_->getMainHero()->getXCoordinate() << "),(" << heroParty_->getMainHero()->getYCoordinate() << ")" << endl;
		
		/* Display location in graphical form */
		map_->viewMap(heroParty_->getMainHero()->getXCoordinate(), heroParty_->getMainHero()->getYCoordinate(), heroParty_->getMainHero()->getMapZoom());
		
        /* Take user input on what to do */
		cout << "Enter Action: ";
		cin >> action;
		
		/* User validation to ensure the user doesn't put in more than 1 character.
		   This is to prevent: If the user puts in more than one action, each character will cause the loop to run
		   an extra time causing the hero to move two spaces at once and other oddities. */
		if (action.size() > 1) {
			system("cls");
			cout << "You have entered too many characters.\n\n";
        }
        /* If the user put in a 1 character input, then continue */
		else {
            /* If a move command, move the hero */
			if ((action=="w") || (action=="s") || (action=="a") || (action=="d")) {

				/* Call map function to move player. */
				if (action == "w") {

					/* Establish the new position for the player */
					newPosition[0] = heroParty_->getMainHero()->getXCoordinate();
					newPosition[1] = heroParty_->getMainHero()->getYCoordinate() + 1;

					/* Move the hero and store whether the process happened successfully or not in success variable */
					success = map_->moveHero(newPosition);
				}
				else if (action == "s") {

					newPosition[0] = heroParty_->getMainHero()->getXCoordinate();
					newPosition[1] = heroParty_->getMainHero()->getYCoordinate() - 1;

					success = map_->moveHero(newPosition);
				}
				else if (action == "d") {

					newPosition[0] = heroParty_->getMainHero()->getXCoordinate() + 1;
					newPosition[1] = heroParty_->getMainHero()->getYCoordinate();

					success = map_->moveHero(newPosition);
				}
				else if (action == "a") {

					newPosition[0] = heroParty_->getMainHero()->getXCoordinate() - 1;
					newPosition[1] = heroParty_->getMainHero()->getYCoordinate();

					success = map_->moveHero(newPosition);
				}
				
				/* If you failed to move, then */
				if (success == 0) {

					/* Display error message and prevent further processing */
					cout << "You can't move this way due to an obstruction.\n";

					/* Give the user a chance to read the message */
					system("pause");
				}
				else {

					/* Update hero coordinates */
					heroParty_->getMainHero()->moveHero(newPosition);

					/* Check to see if the hero is in a town. */
					for (int i = 0; i < map_->getTotalTowns(); i++) {
		
						/* If the heroes current coordinates match any towns coordinates, then... */
						if ((heroParty_->getMainHero()->getXCoordinate() == map_->getTown(i)->getTXLoc()) && (heroParty_->getMainHero()->getYCoordinate() == map_->getTown(i)->getTYLoc())) {
						
							/* Store town number */
							inTown = i;

							/* End loop */
							i = map_->getTotalTowns();
						}
					}

					/* If in a town, then enterTown */
					if (inTown > 0)
						enterTown();

					/* If you aren't in a town, then.. */
					if (inTown == 0) {

						/* Check to see if you enter a battle */
						if (computeEncounter()) {

							/* Create a new encounter */
							encounter = new Battle(heroParty_, fileItems_);

							/* Have the battle */
							encounter->fight();

							/* If the hero died, then reset his position on the map. */
							if (encounter->heroWon() == 0) {
								
								newPosition[0] = heroParty_->getMainHero()->getXRespawnCoordinate();
								newPosition[0] = heroParty_->getMainHero()->getYRespawnCoordinate();

								map_->moveHero(newPosition);
								heroParty_->getMainHero()->hasDied();
							}

							/* Clear the past encounter */
							delete encounter;
						}
					} 
				}
			}
			/* If a help command, display help */
			else if (action == key_Help)  {
				system("cls");
                displayHelp();
			}
            /* If a print stats command, display stats */
			else if (action == key_PrintStats) {
				system("cls");
                heroParty_->showFullPartyStats();
			}
			/* If a change world map view size command, let the user change this */
			else if (action == key_ConfigureZoom) {
				system("cls");
				setWorldView();
			}
			/* If a save command, then save the game */
			else if (action == key_Save) {
				system("cls");
				saveGame();
			}
			/* If a load command, then load the game */
			else if (action == key_Load) {
				system("cls");
				loadGame();
			}
			else if (action == key_ManageInventories) {
				system("cls");
				heroParty_->manageInventories();
			}
			else if (action == key_Teleport) {
				system("cls");
				cout << "Currently Disabled.\n";
			}
			/* If none of the above, dispaly that the user entered an invalid entry */
			else {
				system("cls");
                badInput = 1;
			}
		}
	}
}

void World::setWorldView()
{
	int view;

	cout << "Current Map Zoom: " << heroParty_->getMainHero()->getMapZoom() << endl;
	cout << "Enter a new zoom (Note: 0 will reset to 10): ";
	cin >> view;

	if ((view < 40) && (view > 4) && (view < map_->getXLength()) && (view < map_->getYLength())) {
		heroParty_->getMainHero()->setMapZoom(view);
		cout << "The map view has been set to " << view << endl;
		system("pause");
	}
	else if (view == 0) {
		heroParty_->getMainHero()->setMapZoom(10);
		cout << "The map view has been reset to 10." << endl;
		system("pause");
	}
	else {
		cout << "You entered an invalid view. The view is unchanged. " << endl;
	}
}

/* Called by takeAction to calculate whether or not hero has an encounter while exploring */
bool World::computeEncounter()
{
	/* Generate Random number and store in battle chance */
    int battleChance = rand() % 100 + 1;
	
	/* If that number is less than 1, return 1 so that the hero is put in battle. 0 = no battle */
	if (battleChance <= 30) //30
		return 1;
	else
        return 0;
}

void World::displayHelp()
{
    int menuSelection;
	
	cout << "Welcome to the help menu for Ethreal Plane.\n 1. Basics\n 2. Battle\n 3. Commands\n 4. Exit: ";
	cin >> menuSelection;
	
	switch (menuSelection) {
		case 1: /*```````````````````````````````````````````````````````````````````````````````````-*/
			cout << "\n     In the Ethreal Plane you take the role of a hero questing to gain fame and\n";
			cout << "become e more powerful. Your goal in the ethreal plane is to slay monsters,\n";
			cout << "collect epic lewts, and become the most strong hero in all the land. However,\n";
			cout << "your hero starts off lowly and weak. You must work hard and face the perils of\n";
			cout << "the land to become the best. Your hero starts at (100,100). The world is a\n";
			cout << "coordinate system where x is the first value and y is the second value. To\n";
			cout << "move";
			cout << ", you will have to enter a single key to move in a direction. The default\n";
			cout << "direction keys are wasd.\n\n";
			cout << "     When asked \"what would you like to do now\" you are able to enter a\n";
			cout << "direction key to move your hero through the world. W will move your hero North.\n";
			cout << "Thus, if you enter the character 'w', then your hero will move to (100,101).\n";
			cout << "S will move your hero South. A will move your hero East. D will move your\n";
			cout << "hero West.\n\n";
			cout << "     To interact with the world and to enter commands and actions, you\n";
			cout << "will most likely have to enter a single letter or a number. When moving through";
			cout << "the world random events can occur. You are likely to run into wild monsters or\n";
			cout << "even find random gold!\n\n";
			cout << "     There are towns scattered throughout the world also that";
			cout << "can be found so be on the lookout! In towns you can recruit heroes into your\n";
			cout << "party to have more than one hero in battles! Also you can heal in towns. They\n";
			cout << "are very useful locations!\n\n";
			break;
		case 2:
			cout << "\n     Battles can be started many different ways. They can be random encounters\n";
			cout << "or initiated from a quest. Battles pit you against one to three enemies. They\n";
			cout << "can be the same or different based on the encounter type. The player (hero OR\n";
			cout << "enemy) with the higher dexterity will take their turn first. \n\n";
			cout << "     In battle you can choose to attack the enemy, cast a spell, or flee. If you";
			cout << "attack the enemy then you will do damage based on your minimum and maximum\n";
			cout << "damage. If you cast a spell, then it's effects will take place. If you choose to";
			cout << "flee then there is a 20% chance that you will escape the battle succesfully.\n\n";
			cout << "     Battles will continue until the main hero dies or all enemies are dead. If\n";
			cout << "you win the battle then you gain experience and gold and possibly an item!\n";
			cout << "However if you die then you will lose 1/2 of your current experience and 1/2 of\n";
			cout << "your current gold and be moved back to (100, 100).\n\n";
			break;
		case 3:
			cout << "Commands:\n 'h' = Help Menu\n 'p' = Show Party Stats\n 'o' = Change Map Zoom\n 'i' = Manage Equipment Inventories for heroes\n 'n' = Save the Game\n 'm' = Load the Game\n";
			cout << "Special Commands: You can enter '1595' to drop all items from an inventory when managing an item at the Inventory Viewer.\n";
			cout << "Cheats: I would advise to only use if you ABSOLUTELY NEED TO! (IE A BUG):\n Teleport = '^'";
		case 1681337:
			cout << "CHEATS!\n";
			heroParty_->getMainHero()->activateCheats();
			heroParty_->getMainHero()->calculateStats();
			heroParty_->getMainHero()->fullHeal();
			break;
	}
}

void World::saveGame()
{
	ofstream f("C:\\Users\\donny\\Desktop\\SaveFile.txt");

	for (int i = 0; i < heroParty_->getTotalHeroes(); i++) {
		
		if (heroParty_->getPartyMember(i)->getName() != "No Name") {
			f << "Hero" + returnString(i) + "\n";
			f << heroParty_->getPartyMember(i)->getSaveInformation();
			if (i == 0) {
				f << heroParty_->getMainHero()->getSaveInformation2();
			}
			f << "End";
		}
	}
	f.close();
}

void World::loadGame()
{
	ifstream f("C:\\Users\\donny\\Desktop\\SaveFile.txt");
	
	string contents = "";
	string header = "";
	int currentHero = 0;
	int len = 0;

	while (!f.eof()) {
		
		/* Get the information from the line */
		getline(f, contents);
		len = contents.length();
		
		/*
		system("cls");
		cout << "contents: " << contents << "\nlength: " << len << endl;
		system("pause");
		*/

		/* Check Headers */
		header = contents.substr(0,4);
		if (header == "Hero") {
			currentHero = returnNumber(contents.substr(4,len));
		}
		else if (header == "Main") {
			currentHero = 0;
		}

		/* Read another line from the file */
		getline(f, contents);
		len = contents.length();

		/* While not at another header, keep reading from the file. */
		while (contents.substr(0,3) != "End") {

			/* Check contents under header
			system("cls");
			cout << contents << endl;
			system("pause"); */

			/* Party Information */
			if (contents.substr(0,4) == "Name") {
				heroParty_->getPartyMember(currentHero)->setName(contents.substr(4,(len-4)));
			}
			else if (contents.substr(0,9) == "Attribute") {
				heroParty_->getPartyMember(currentHero)->getBaseLifeRepeatable()->getAttributes()->setAttribute(returnNumber(contents.substr(9,1)),returnNumber(contents.substr(10,1)));
			}
			else if (contents.substr(0,5) == "Class") {
				heroParty_->getPartyMember(currentHero)->setClass(0, contents.substr(5,(len-5)));
			}
			else if (contents.substr(0,5) == "Level") {
				heroParty_->getPartyMember(currentHero)->setLevel(returnNumber(contents.substr(5,(len-5))));
			}
			else if (contents.substr(0,10) == "Experience") {
				heroParty_->getPartyMember(currentHero)->setExperience(returnNumber(contents.substr(10,(len-5))));
			}
			else if (contents.substr(0,10) == "StatPoints") {
				heroParty_->getPartyMember(currentHero)->setStatPoints(returnNumber(contents.substr(10,(len-10))));
			}

			/* Main Hero Information */
			if (currentHero == 0) {
				if (contents.substr(0,4) == "Gold") {
					heroParty_->getMainHero()->setGold(returnNumber(contents.substr(4, (len-4))));
				}
				else if (contents.substr(0,12) == "XCoordinate") {
					heroParty_->getMainHero()->setXCoordinate(returnNumber(contents.substr(12, (len-12))));
				}
				else if (contents.substr(0,12) == "YCoordinate") {
					heroParty_->getMainHero()->setXCoordinate(returnNumber(contents.substr(12, (len-12))));
				}
				else if (contents.substr(0,7) == "MapZoom") {
					heroParty_->getMainHero()->setXCoordinate(returnNumber(contents.substr(7, (len-7))));
				}
			}

			/* Get a new line */
			getline(f,contents);
			len = contents.length();

			/* Debugging information 
			cout << contents.substr(0,4) << " looping forever.\n";
			system("pause"); */
		}
	}

	f.close();

	/* if (contents.substr(0,3) == "Zoom") {
	heroParty_->getMainHero()->setMapZoom(returnNumber(contents.substr(4,len)));
} */
}

void World::skipHeroCreation()
{
	/* Create hero */
	heroParty_->getMainHero()->setPowerPlayerProperties("Destro", 1, 1, 1, 1);
	
	/* give hero mega imba damage */
	heroParty_->getMainHero()->getBaseLifeRepeatable()->setPhysicalDamageMinimum(500);
	heroParty_->getMainHero()->getBaseLifeRepeatable()->setPhysicalDamageMaximum(1000);

	heroParty_->getMainHero()->calculateStats();
	heroParty_->getMainHero()->fullHeal();
}

/* Called by main to allow the user to create their Main heroParty_->getMainHero()-> */
void World::createMainHero()
{
	/* Variable Declations + Initializations for Main Hero */
    string pName;
	int pClass;
	int pRace;
	int pElement;

    /* Get Player Name */
	cout << "Welcome to the Ethreal Plane. What is your name?: ";
    cin >> pName;
    
    /* Get the class the user wants. */
	wMenu_->takeInput("1.) Please pick a class (1=Warrior, 2=Mage, 3=Rouge): ", "Please enter a valid class from 1-3.", 3, 0);
	pClass = wMenu_->getInput();
	system("cls");
	
	 /* Get the race the user wants. */
	wMenu_->takeInput("2.) Please pick a race (1=Human,2=Elf,3=Orc): ", "Please enter a valid race from 1-3.", 3, 0);
	pRace = wMenu_->getInput();
	system("cls");
	
	 /* Get the element the user wants. */
	wMenu_->takeInput("3.) Please choose your heroes Element!: \n 1. Fire, 2. Wind, 3. Water, 4. Rock, 5. Poisen,\n 6. Static, 7. Psychic, 8. Light, 9. Dark, 10. Berserk: ",
		"Please enter a valid element from 1-10.", 10, 0);
	pElement = wMenu_->getInput();
	system("cls");

    /* Set Hero stats */
    heroParty_->getMainHero()->setPowerPlayerProperties(pName, 1, pClass, pRace, pElement);
	heroParty_->getMainHero()->calculateStats();
    heroParty_->getMainHero()->restoreHitPoints();
	heroParty_->getMainHero()->restoreManaPoints();
    
    /* Print Hero Stats */
	heroParty_->getMainHero()->printStats();
}

/* Called by town to handle the creation of party members */
void World::enterGuild(Location *town)
{
	/* Variable Declaration + Init */

	/* Formatting */
	system("cls");

	/* Take user input on what they would like to do in the guild */
	wMenu_->takeInput("Welcome to the local Guild. There are lots of people here looking for parties to venture with. What would you like to do?\n 1.) Add Party Member\n 2.) Remove Party Member",
		"You did not pick a valid guild option.", 2, 1);

	/* Based on user input, go to the respective function to add a member or remove a member */
	if (wMenu_->getInput() == 1)
		heroParty_->generateNewRandomPartyMember();
	else if (wMenu_->getInput() == 2)
		heroParty_->removePartyMember();
}

/* Handles */
void World::enterInn(Location *town)
{
    /* Variable Declarations */
    char userChoice;   
	
    system("cls");
    
    /* Ask the user if he/she would like to heal. Also display gold cost */
    cout << "Would you like to heal? It will cost " << town->getInnFee() << " gold.\n ";
    cout << "Current Gold: " << heroParty_->getMainHero()->getGold() << "\n (y/n): ";
	cin >> userChoice;

	/* If the user chooses to heal, then decrease their gold and heal them. */
    if (userChoice == 'y') {
		/* Take Gold */
		heroParty_->getMainHero()->decreaseGold(town->getInnFee());
		/* Heal Entire Party */
		heroParty_->fullHealWholeParty();
    }
    /* If the user didn't choose to heal, then tell the hero they left the inn. */
	else
        cout << "You choose not to heal and promptly left the inn.\n";
}

/* Handles actions for the hero in a town. */
void World::enterTown()
{
    /* Variable Declarations */
    bool stayInTown = 1;

	Location *currentTown = new Location;

	currentTown = map_->getTownAtHero(heroParty_->getMainHero()->getCoordinates());

	if (currentTown->getTownName() != "Undefined") {
		/* Formatting */
		//system("cls");
		
		/* Display Welcome message */
		cout << "Welcome to: " << currentTown->getTownName() << " " << currentTown->getTownWelcome() << endl;
		
		/* Do town stuff until the user chooses to leave the town. */
		do {
		
			/* Get user input on what to do next */
			wMenu_->takeInput("Where would you like to go?\n 1.) Inn\n 2.) Tavern -- Not Working\n 3.) Guild\n 4.) Exit Town:  ", "You entered an invalid location to visit", 4, 0);

			/* Evauluate the choices */
			switch (wMenu_->getInput()) {
				case 1:
					enterInn(currentTown);
					break;
				case 2:
					cout << "Not working\n";
					break;
				case 3:
					enterGuild(currentTown);
					break;
				case 4:
					stayInTown = 0;
				default:
					break;
			}
		} while (stayInTown == 1);
		
		/* Tell the hero he left the town */
		cout << "You have left " << currentTown->getTownName() << "\n";
	}
}

HeroManager *World::getHeroParty() {
	return heroParty_;
}

//cout << "Hero, (" << heroParty_->getMainHero()->getXCoordinate() << "," << heroParty_->getMainHero()->getYCoordinate() << ") World (" << Worldmap_->getTown(i).getTXLoc() << "," << Worldmap_->getTown(i).getTYLoc() << ")" << endl;
