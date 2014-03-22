/* This file will help generate the items for the game :D */

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void itemGenerator(int itemCreationType);
void setLevel(int x, int &y);
string getOreName(int currentItem);
string getClothName(int currentItem);

/* Return LevelRequirements */
int returnLevel(int currentItem)
{
	switch (currentItem) {
		case 1: 
			return 1;
		case 2:
			return 5;			
		case 3:
			return 10;			
		case 4:
			return 15;			
		case 5:
			return 20;			
		case 6:
			return 30;			
		case 7:
			return 40;			
		case 8:
			return 50;			
		case 9:
			return 60;			
		case 10:
			return 70;			
		case 11:
			return 80;			
		case 12:
			return 90;			
		case 13:
			return 100;			
		case 14:
			return 120;			
		case 15:
			return 140;			
		case 16:
			return 160;			
		case 17:
			return 180;			
		case 18:
			return 200;			
		case 19:
			return 225;			
		case 20:
			return 250;			
		case 21:
			return 500;			
	}
	return -1;
}

/* Return standard name for ores */
string getOreName(int currentItem)
{
	switch (currentItem) {
        case 1:
             return "Copper";
        case 2:
             return "Bronze";
        case 3:
             return "Iron";             
        case 4:
             return "Steel";             
        case 5:
             return "Varium";             
        case 6:
             return "Mlificum";             
        case 7:
             return "Adamantium";             
        case 8:
             return "Dragon";             
        case 9:
             return "Beryll";             
        case 10:
             return "Azmith";             
        case 11:
             return "Sereptonium";             
        case 12:
             return "Ralifum";             
        case 13:
             return "Magnifite";             
        case 14:
             return "Cyritite";             
        case 15:
             return "Genogma";             
		case 16:
			 return "Hoga";			 
		case 17:
			 return "Telium";			 
		case 18:
			 return "Shervagorite";			 
        case 19:
             return "Divine";             
        case 20:
             return "Infinicia";             
        case 21:
             return "Uber";             
        default:
             return "";
    }
	return "";
}  

string getClothName(int currentItem)
{
	switch (currentItem) {
        case 1:
             return "Rat";
        case 2:
             return "Chicken";
        case 3:
             return "Cow";             
        case 4:
             return "Bear";             
        case 5:
             return "Serpent Scaled";             
        case 6:
             return "Terror Hide";             
        case 7:
             return "Predator";             
        case 8:
             return "Dragon Hide";             
        case 9:
             return "Dragon Scaled";             
        case 10:
             return "Zorgon Claw";             
        case 11:
             return "Scalberth Claw";             
        case 12:
             return "Mystic Toothed";             
        case 13:
             return "Hunter";             
        case 14:
             return "Stalker";             
        case 15:
             return "Overpowered";             
		case 16:
			 return "Ignok";			 
		case 17:
			 return "Shoo";			 
		case 18:
			 return "Xoc'MinMua";			 
        case 19:
             return "Divine";             
        case 20:
             return "Infinicia";             
        case 21:
             return "Uber";             
        default:
             return "";
    }
	return "";
}

void itemGenerator(int itemCreationType)
{
	/* static int currentItem = 0;
    static int count = 0;
    static int level = 1; */

	/* Item Specific */
	int itemsPerGeneration = 0;
	int trueCurrent = 0;
	int totalTtemTypes = 0;
	
	string itemTypeName = "";
	string itemOreType = "";
	string itemClothType = "";
	string itemFullName = "";
	string description = "";

	int itemLevelRequirement = 0;
	int attributeBase[4] = {0};
    int value = 0;
	
	double scalingMultiplier = 1;
	double growthRate = 0;

	/* Weapon */
    int minDamage;
    int maxDamage;

	/* Shield */
	int dodgeChance;
	
	/* Shield, Body Armor, Leg Armor */
	int physicalArmor;

	/* Ring, has nothing. */
	int elementalResistances[10];

	/*
		fire
		wind
		water
		rock
		poisen
		static
		psychic
		dark
		light
		berserk
	*/

	/* Put itemcreationtype on the programmer level */
	itemCreationType--;

    /* Create/Open the file */
    ofstream myfile;
	
	if (itemCreationType == 0)
		myfile.open("Weapons.txt");
	else if (itemCreationType == 1)
		myfile.open("Shields.txt");
	else if (itemCreationType == 2)
		myfile.open("BodyArmors.txt");
	else if (itemCreationType == 3)
		myfile.open("LegArmors.txt");
	else if (itemCreationType == 4)
		myfile.open("Rings.txt");
	else if (itemCreationType == 5)
		myfile.open("Necklaces.txt");
    
	/* Set the total amount of items round of item creation */
	itemsPerGeneration = 21;
	
	//createWeapon();

	/* Set how many different item types we want to create */
	if (itemCreationType == 0)
		totalTtemTypes = 3;
	else if (itemCreationType == 1)
		totalTtemTypes = 1;
	else if (itemCreationType == 2)
		totalTtemTypes = 3;
	else if (itemCreationType == 3)
		totalTtemTypes = 2;
	else if (itemCreationType == 4)
		totalTtemTypes = 1;
	else if (itemCreationType == 5)
		totalTtemTypes = 1;

	
	/* We need to create totalWeapons amount of weapons */
	for (int i = 0; i < totalTtemTypes; i++) {
		
		/* Based on item Creation type */
		if (itemCreationType == 0) {
			/* Set the Item type name to correspond with the currently generated item type */
			if (i == 0)
				itemTypeName = "Sword";
			else if (i == 1)
				itemTypeName = "Staff";
			else
				itemTypeName = "Dagger";
		}
		else if (itemCreationType == 1) {
			if (i == 0)
				itemTypeName = "Shield";
		}
		else if (itemCreationType == 2) {
			if (i == 0)
				itemTypeName = "Platemail";
			else if (i == 1)
				itemTypeName = "Vestment";
			else if (i == 2)
				itemTypeName = "Robe";
		}
		else if (itemCreationType == 3) {
			if (i == 0)
				itemTypeName = "Leggings";
			else
				itemTypeName = "Trousers";
		}
		else if (itemCreationType == 4) {
			if (i == 0)
				itemTypeName = "Ring";
		}
		else if (itemCreationType == 5) {
			if (i == 0)
				itemTypeName = "Necklace";
		}

		/* Set the trueCurrentItem to the next current Item. */
		trueCurrent = (i * itemsPerGeneration) + 1;

		/* Create one set of items */
        for (int currentItem = 1; currentItem < (itemsPerGeneration+1); currentItem++) {

			/* Create the full item name */
			if ((itemCreationType == 0) || (itemCreationType == 1) || (itemCreationType == 4) || (itemCreationType == 5)) {

				/* create the full item name as an ore */
				itemOreType = getOreName(currentItem);
				itemFullName = itemOreType + " " + itemTypeName;
			}
			else if (itemCreationType == 2) {
				if (i == 0) {
					itemOreType = getOreName(currentItem);
					itemFullName = itemOreType + " " + itemTypeName;
				}
				else if (i == 1,2) {
					/* create the full item name as an cloth */
					itemClothType = getClothName(currentItem);
					itemFullName = itemClothType + " " + itemTypeName;
				}
			}
			else if (itemCreationType == 3) {
				if (i == 0) {
					itemOreType = getOreName(currentItem);
					itemFullName = itemOreType + " " + itemTypeName;
				}
				else if (i == 1,2) {
					itemClothType = getClothName(currentItem);
					itemFullName = itemClothType + " " + itemTypeName;
				}
			}
			else if (itemCreationType == 4) {
				itemOreType = getOreName(currentItem);
				itemFullName = itemOreType + " " + itemTypeName;				
			}
			else if (itemCreationType == 5) {
				itemOreType = getOreName(currentItem);
				itemFullName = itemOreType + " " + itemTypeName;
			}
			
			/* If a weapon, then the base attributes will be */
			if (itemCreationType == 0) {

				/* If a sword then mostly vitality, and lower other stats */
				if (i == 0) {
					attributeBase[0] = 4;
        			attributeBase[1] = 1;
        			attributeBase[2] = 2;
        			attributeBase[3] = 1;
				}

				/* If a staff, then mostly magic and lower other stats */
				else if (i == 1) {
					attributeBase[0] = 1;
        			attributeBase[1] = 4;
        			attributeBase[2] = 1;
        			attributeBase[3] = 2;
				}

				/* If a dagger, then mostly agility and lower other stats */
				else {
					attributeBase[0] = 2;
					attributeBase[1] = 1;
					attributeBase[2] = 4;
					attributeBase[3] = 1;
				}
			}
			/* Shield */
			else if (itemCreationType == 1) {
				attributeBase[0] = 3;
        		attributeBase[1] = 1;
        		attributeBase[2] = 3;
        		attributeBase[3] = 1;
			}
			/* Body Armor */
			else if (itemCreationType == 2) {
				attributeBase[0] = 5;
        		attributeBase[1] = 1;
        		attributeBase[2] = 1;
        		attributeBase[3] = 1;
			}
			/* Leg Armor */
			else if (itemCreationType == 3) {
				attributeBase[0] = 5;
        		attributeBase[1] = 1;
        		attributeBase[2] = 1;
        		attributeBase[3] = 1;
			}
			/* Ring */
			else if (itemCreationType == 4) {
				attributeBase[0] = 1;
        		attributeBase[1] = 2;
        		attributeBase[2] = 1;
        		attributeBase[3] = 3;
			}
			/* Necklace */
			else if (itemCreationType == 5) {
				attributeBase[0] = 1;
        		attributeBase[1] = 2;
        		attributeBase[2] = 1;
        		attributeBase[3] = 3;
			}

			/* We calculate all the attributes of the weapon now. 4 passes to hit all variables */
			for (int i = 0; i < 4; i++) {

				/* We now calculate the stats actual value.
						Definition of how we want stat growth: We want to increase the stats exponentially.
							 Set A = {y = x^2 + b | for all Z+}
							b becomes insignificant so just do y = x^z */

				attributeBase[i] = int((attributeBase[i] * (currentItem + scalingMultiplier) * (attributeBase[i] * (currentItem + scalingMultiplier))) / 95);

				if (attributeBase[i] < 1)
					attributeBase[i] = 1;
			}
			
			/* Get the items level requirement */
			itemLevelRequirement = returnLevel(currentItem); /* Set Item Level Requirement */

           /* EVEN MOAR quick maths to calculate value */
            value = int(currentItem * scalingMultiplier) * 125;

			/* Equal level physical armor to a weapon gives different fractions of protective power:maximum damage of that weapon.	
			-Ore based equipment get higher armor bonuses.
						
				-Body Armor = Huge Protection against weapons damage
					-physicalArmor = maximumDamage / 2;
					-no attribute bonuses.
				-Leggings = Medium protection against weapon damage.
					-physicalArmor = maximumDamage / 4
					-no attribute bonuses.
				-Shields = Chance to Block attacks + armor.
					-chanceToDodge = forumla with diminishing returns. Lowerlimit = 1%, upperLimit = 20%
						rarity will give a 50% bonus to the upperlimit rather than 500% stat bonus.
						so if the current bonus is 5%, then the chance to dodge will be 7.5% chance to dodge. Maximum dodge being 30% ofc.
					-physicalArmor = maximumDamage / 8;
			-Cloth based equipment get higher attribute bonuses.
				-Body Armor = Huge Protection against weapons damage
					-physicalArmor = maximumDamage / 4;
					-+50% higher stats
				-Leggings = Medium protection against weapon damage.
					-physicalArmor = maximumDamage / 8
					- +50% higher stats
				-No cloth shields
				*/



			/* Set special properties for items based on the being generated type and send information to file */

			/* Weapons */
			if (itemCreationType == 0) {

				/* Weapon Damage should be on a 25:75 ratio to stats to make the whole damage.
					Attributes are 75% so the weapon is 25%. So 1:3 ratio of weapon damage to generated attribute
					Then we split that 25% weapon damage into  ratio into 1:3 and 3:3 to represent the minimum and maximum damage.
					Tighten up the minimum damage value by multiplying it by 2 */
				minDamage = int(attributeBase[i] / 4.5);
				maxDamage = int(attributeBase[i] / 3);

				/* Send weapon information to the file */
				myfile << itemFullName << endl;
				myfile << "This " << itemTypeName << " was forged from " << itemOreType << endl;
				myfile << value << endl;
				myfile << itemLevelRequirement << endl;
				myfile << attributeBase[0] << endl;
				myfile << attributeBase[1] << endl;
				myfile << attributeBase[2] << endl;
				myfile << attributeBase[3] << endl;
				myfile << minDamage << endl;
				myfile << maxDamage << endl;
			}
			/* Shields */
			else if (itemCreationType == 1) {
				
				/* Add this shield functionality to the game */
				dodgeChance = currentItem - (currentItem / itemsPerGeneration);
				physicalArmor = int(attributeBase[i] / 5);

				/* Send shield information to the file */
				myfile << itemFullName << endl;
				myfile << "This " << itemTypeName << " was forged from " << itemOreType << endl;
				myfile << value << endl;
				myfile << itemLevelRequirement << endl;
				myfile << attributeBase[0] << endl;
				myfile << attributeBase[1] << endl;
				myfile << attributeBase[2] << endl;
				myfile << attributeBase[3] << endl;
				myfile << dodgeChance << endl;
				myfile << physicalArmor << endl;
			}
			/* Body Armors */
			else if (itemCreationType == 2) {

				/* If the body armor isn't cloth based, then...  */
				if (itemClothType == "") {
					
					/* Steal weapon calculation formula and modify */
					physicalArmor = int(attributeBase[i] / 4.5) / 2;

				}
				/* It is cloth based */
				else {
					physicalArmor = int(attributeBase[i] / 4.5) / 4;

					for (int i = 0; i < 4; i++)
						attributeBase[i] = int(attributeBase[i] * 1.5);
				}

				/* Send shield information to the file */
				myfile << itemFullName << endl;
				myfile << "This " << itemTypeName;
				
				if (itemOreType != "")
					myfile << " was forged from " << itemOreType << endl;
				else
					myfile << " was crafted from " << itemClothType << endl;

				myfile << value << endl;
				myfile << itemLevelRequirement << endl;
				myfile << attributeBase[0] << endl;
				myfile << attributeBase[1] << endl;
				myfile << attributeBase[2] << endl;
				myfile << attributeBase[3] << endl;
				myfile << physicalArmor << endl;
			}
			/* Leg Armor */
			else if (itemCreationType == 3) {
				
				/* If the Leg armor isn't cloth based, then...  */
				if (itemClothType == "") {
					
					/* Steal weapon calculation formula and modify */
					physicalArmor = int(attributeBase[i] / 4.5) / 2;

				}
				/* It is cloth based */
				else {
					physicalArmor = int(attributeBase[i] / 4.5) / 4;
				}

				/* Send leg armor information to the file */
				myfile << itemFullName << endl;
				myfile << "This " << itemTypeName;
				
				if (itemOreType != "")
					myfile << " was forged from " << itemOreType << endl;
				else
					myfile << " was crafted from " << itemClothType << endl;

				myfile << value << endl;
				myfile << itemLevelRequirement << endl;
				myfile << attributeBase[0] << endl;
				myfile << attributeBase[1] << endl;
				myfile << attributeBase[2] << endl;
				myfile << attributeBase[3] << endl;
				myfile << physicalArmor << endl;
			}
			/* Ring */
			else if (itemCreationType == 4) {
				
				/* Send ring information to the file */
				myfile << itemFullName << endl;
				myfile << "This " << itemTypeName << " was forged from " << itemOreType << endl;
				myfile << value << endl;
				myfile << itemLevelRequirement << endl;
				myfile << attributeBase[0] << endl;
				myfile << attributeBase[1] << endl;
				myfile << attributeBase[2] << endl;
				myfile << attributeBase[3] << endl;
			}
			/* Necklace */
			else if (itemCreationType == 5) {
				
				/* Send ring information to the file */
				myfile << itemFullName << endl;
				myfile << "This " << itemTypeName << " was forged from " << itemOreType << endl;
				myfile << value << endl;
				myfile << itemLevelRequirement << endl;
				myfile << attributeBase[0] << endl;
				myfile << attributeBase[1] << endl;
				myfile << attributeBase[2] << endl;
				myfile << attributeBase[3] << endl;
			}
			
			 /* Increase the trueCurrent by 1 */
			trueCurrent++;

			/* Increase the scaling multiplier for future passes */
			scalingMultiplier = scalingMultiplier + 5;

			/* Clear values to be re-evaluated */
			for (int i = 0; i < 4; i++)
				attributeBase[i] = 0;
        }

		/* Reset item type names */
		itemOreType = "";
		itemTypeName = "";

		/* Reset the scaling multiplier */
		scalingMultiplier = 1;
    }
    
    /* Close the file */
    myfile.close();

	/* Display completion message */
	cout << "Process Successfully completed!!!\n\n";

}

int main()
{
    /***************************************************************************** 
	
	 Create Equipment -- Template = 
	 
	 setItemProperty - Name, descroption, value
	 setEquipmentProperty - level requirement, attributes, magic find
	 Set ??? Property - ??? ??? Customized
	
	*****************************************************************************/
	
	/* Variable Declarations */
	int itemCreationType = 0;
	
	/* Display Message */
    cout << "welcome to the random item generator!\n This will generate items. Enjoy\n\n";
    cout << "SetItemProperty - Name, description, value\n";
    cout << "SetEquipmentProperty - level requirement, attributes, magic find\n";
	cout << "Set ??? Property - ??? ??? Customized\n\n";
    
	/* Take user input on type of items to generate */
	cout << "Item to Generate:\n 1.) Weapons\n 2.) Shields\n 3.) Body Armor\n 4.) Leg Armor\n 5.) Ring\n 6.) Necklace: ";
	cin >> itemCreationType;

	/* Start generating items */
    itemGenerator(itemCreationType);

    system("pause");
}
