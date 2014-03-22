#include "map.h"
#include "world.h"
#include "location.h"
#include "life.h"

#include <iostream>

Map::Map(void)
{
	mXLength_ = 0;
	mYLength_ = 0;
	mTotalTowns_ = 10;
	oldPosition_[0] = 0;
	oldPosition_[1] = 0;
	newPosition_[0] = 0;
	newPosition_[1] = 0;

	mTown_ = new Location*[10];

	for (int i = 0; i < 10; i++) {
		mTown_[i] = new Location;
	}

	mHiddenObject_ = ".";
	calculateGridAverageLength();
	fillMap(1);
	clearObjects();

	mObject_[mGridAverageLength_][mGridAverageLength_] = "o";
}

Map::Map(int xLength, int yLength, int startPosition[])
{
	mXLength_ = xLength;
	mYLength_ = yLength;
	mTotalTowns_ = 10;
	oldPosition_[0] = startPosition[0];
	oldPosition_[1] = startPosition[1];
	newPosition_[0] = 0;
	newPosition_[1] = 0;

	mTown_ = new Location*[10];

	for (int i = 0; i < 10; i++) {
		mTown_[i] = new Location;
	}

	mHiddenObject_ = ".";
	calculateGridAverageLength();
	fillMap(1);
	clearObjects();
	mObject_[mGridAverageLength_][mGridAverageLength_] = "o";
}
 
Map::~Map(void)
{
}

/* Private Methods */

void Map::calculateGridAverageLength()
{
	mGridAverageLength_ = (mXLength_ + mYLength_) / 4;
}

void Map::clearObjects()
{
	for (int i = 0; i < mXLength_; i++) {
		for (int i2 = 0; i2 < mYLength_; i2++) {
			mObject_[i][i2] = ".";
		}
	}
}

void Map::setTownCoordinates(int &x, int &y, int i)
{
	/* Sets town location to a region that matches it's distance from center.
	The goal is to make sure towns have a good spread in distance from each other and constantly get farther from the middle.
	
	Examples: Town 1: 10 range of map middle - 90-100, 100-110 Town 2: 10-20 range of map middle - 80-90, 110-120 */
	
	bool keepLooping = 1;
	int a = 100 - (i * 10);  // 90, 80
	int b = 100 - (i * 10) + 10; // 100, 90
	int c = 100 - 10 + (i * 10); // 100, 110
	int d = 100 + (i * 10); // 110, 120
	
	while (keepLooping == 1) {

		/* Reset keepLooping to be evaluated */
		keepLooping = 0;

		/* Generate a number between a and d */
		x = (rand() % (d - a)) + a;
		y = (rand() % (d - a)) + a;

		/* if the number is out of bounds, KEEPLOOPING! */
		if ((x > b) && (x < c))  {
			keepLooping = 1;
		}

		/* if the number is out of bounds, KEEPLOOPING! */
		if ((y > b) && (y < c)) {
			keepLooping = 1;
		}

		/* if the number is out of bounds, KEEPLOOPING! */
		if (keepLooping == 0) {	
			for (int i = 0; i < 3; i++) {
				for (int i2 = 0; i2 < 3; i2++) {
					if (mTile_[(x-1)+i][(y-1)+i2] == "m") {
						keepLooping = 1;
					}
				}
			}
		}

		/* Perform final check to make sure that the town isn't place on any objects */
		if (keepLooping == 0) {
			if (mObject_[x][y] != ".") {
				keepLooping = 1;
			}
		}
	} /* End of while */
} /* End of function */

void Map::getInformation(string &name, string &welcome, int i)
{
	switch (i) {
		case 0:
			name = "Araman";
			welcome = "the home of adventurers and magic!";
			break;
		case 1:
			name = "Anorixia";
			welcome = "the town of water. ";
			break;
		case 2:
			name = "Levue";
			welcome = "the town of hard work. SWEAT, SWEAT, SWEAT!";
			break;
		case 3:
			name = "Iqnok";
			welcome = "where flames rise and fall!";
			break;
		case 4:
			name = "Berillisk";
			welcome = "where rock smashes and crushes all!";
			break;
		case 5:
			name = "Trinity";
			welcome = "the merging point of the elements.";
			break;
		case 6:
			name = "The Horde";
			welcome = "the last retreat for all fallen soldiers.";
			break;
		case 7:
			name = "Requiem";
			welcome = "lengend has it that Requiem is a meeting place of gods.";
			break;
		case 8:
			name = "Halo City";
			welcome = "the meeting place of angels.";
			break;
		case 9:
			name = "Undead Town";
			welcome = "undead rule the markets";
			break;
		case 10:
			name = "Black Huggles";
			welcome = "populated by a race of black nomads that give tons of hugs!.";
			break;
		default:
			name = "LOL NOPE";
			welcome = "HAHA YOU WISH!!!";
			break;
	}
}

/* Public Methods */

void Map::fillMap(int fillType)
{
	for (int i = 0; i < mXLength_; i++) {
		for (int i2 = 0; i2 < mYLength_; i2++) {
			if (fillType == 1) {
				mTile_[i][i2] = "_";
			}
			else {
				mTile_[i][i2] = "m";
			}
		}
	}
}

void Map::createMountains(int noSpawnRadius)
{
	// Variables
	int x[501]; // Access variable for object array.
	int y[501]; // Access variable for object array.
	int tempMap[500][500]; // Represents the map in number form.
	int chanceToSpawn = 0; // Holds a random number for whether or not a mountain spawns
	double spawnCheck = 0; // Holds a value that represents the limit that chanceToSpawn has to meet for a mountain to spawn.

	mTotalBaseMountains_ = 300; //(rand() % mGridAverageLength_ / 20) + (mGridAverageLength_ / 10);
	mMountainDistance_ = 20; //mGridAverageLength_ * .75;
	mCutoffPoint_ = 7; //mGridAverageLength_ / 10;

	//related to diamond generation
	int diamondRadius = 0;
	int startPoint = 0;
	int endPoint = 0;
	int spawnWidth = 0;
	int mountainCount = 0;

	/* Initialize temp map elements to 0 */
	for (int i = 0; i < mXLength_; i++) {
		for (int i2 = 0; i2 < mYLength_; i2++) {
			tempMap[i][i2] = 0;
		}
	}

	for (int i = 0; i < 501; i++) {
		for (int i2 = 0; i2 < 501; i2++) {
			x[i] = 0;
			y[i] = 0;
		}
	}

	/* Generate a location for a base mountain. Make sure no base mountains are too close. */
	for (int i = 0; i < mTotalBaseMountains_; i++) {
	
		// Generate random values
		x[i] = rand() % mXLength_;
		y[i] = rand() % mYLength_;

		// Check is performed to make sure mountains aren't too close.
		if (i > 0) {
			for (int i2 = 0; i2 < i; i2++) {
				while ((x[i2] - mMountainDistance_) < 1) {
					x[i2] = rand() % mXLength_;
					y[i2] = rand() % mYLength_;
				}
			}
		}
	}

	/* Place base mountains onto integer map */
	for (int i = 0; i < mTotalBaseMountains_; i++) {
		tempMap[x[i]][y[i]] = 1;
	}

	/* Go through every integer map element. If that map element is a number > 0, then spawn 4 numbers around it */
	for (int i = 1; i < mCutoffPoint_; i++) {
		for (int j = 0; j < mXLength_; j++) {
			for (int k = 0; k < mYLength_; k++) {
				if (tempMap[j][k] == i) {

					/* Set the spawn check to the percent that i is of mCutoffPoint */
					spawnCheck = i * 100 / mCutoffPoint_;

					/* If the percent is within a range, then change the spawn check to be the limit for random number checking */
					if (spawnCheck < 25)
						spawnCheck = 100;
					else if (spawnCheck > 25)
						spawnCheck = 60;
					else if (spawnCheck > 12.5)
						spawnCheck = 50;
					else if (spawnCheck > 25)
						spawnCheck = 25;
					else if (spawnCheck > 50)
						spawnCheck = 10;
					else
						spawnCheck = 5;
						
					/* Generate a random chance to spawn */
					chanceToSpawn = (rand() % 100) + 1;
					
					/* Spawn top mountain */
					if (chanceToSpawn <= spawnCheck) 
						tempMap[j][(k+1)] = (i+1);

					/* Spawn bottom mountain */
					chanceToSpawn = (rand() % 100) + 1;
					if (chanceToSpawn <= spawnCheck) 
						tempMap[j][(k-1)] = (i+1);

					/* Spawn right mountain */
					chanceToSpawn = (rand() % 100) + 1;
					if (chanceToSpawn <= spawnCheck) 
						tempMap[(j+1)][k] = (i+1);

					/* Spawn left mountain */
					chanceToSpawn = (rand() % 100) + 1;
					if (chanceToSpawn <= spawnCheck)
						tempMap[(j-1)][k] = (i+1);
				}
			}
		}
	}

	/* Convert stray grass in mountains into mountains. */
	
	/* Do 3 passes */
	for (int l = 0; l < 2; l++) {
		/* X and Y coordinates */
		for (int i = 2; i < mXLength_ - 2; i++) {
			for (int i2 = 2; i2 < mYLength_ - 2; i2++) {
				if (tempMap[i][i2] == 0) {
					/* Scan 5 blocks (2 left, middle, 2 right) 0,1,2,3,4 */
					for (int j = 4; j > 0; j--) {
						if (tempMap[i + 2-j][i2] > 0)
							mountainCount++;
						if (tempMap[i][i2+2-j] > 0)
							mountainCount++;
					}
				}

				/* If there are 10 mountains around the grass, then turn the grass to a mountain */
				if (mountainCount > 15) {
					tempMap[i][i2] = 1;
				}
				
			
				/* Reset mountain count */
				mountainCount = 0;
			}
		}
	}

	
	/* Convert integer mountain map to string mountain map */
	for (int i = 0; i < mXLength_; i++) {
		for (int i2 = 0; i2 < mYLength_; i2++) {	
			if (tempMap[i][i2] > 0) {
				mTile_[i][i2] = "m";
			}
		}
	}

	diamondRadius = 4;
	startPoint = mGridAverageLength_ - diamondRadius;
	endPoint = (mGridAverageLength_ - startPoint + 1) + mGridAverageLength_;
	spawnWidth = mGridAverageLength_ - startPoint + 1;

	/* Clear mountains in a diamond around WHAT I WANT!!! HAHAHAHA
		THE DIAMOND ALGORITHM WAS DEVELOPED HERE! ~Donald Abdullah-Robinson */
	for (int a = startPoint; a < endPoint; a++) {
		for (int i = 0; i < spawnWidth; i++) {
			
			/* Lay out base diamond shapes */
			mTile_[a+i][a-i] = "_";
			mTile_[a-i][a+i] = "_";

			/* Fill in the gaps of the diamond shape while trimming using the if statements. */
			if (a < endPoint - 1) {
				mTile_[a+1-i][a+i] = "_";
			}
			
			if (i < spawnWidth - 1) {
				if (a < endPoint - 1) {
					mTile_[a+1+i][a-i] = "_";
				}
			}
		}
	}
}

void Map::createTowns()
{
	/* Variable Declarations */
	int count = 0;
	int townX;
	int townY;
	string tName = "";
	string tWelcome = "";

	/*************************************
	create the towns and their locations
	*************************************/
	for (int i = 1; i < mTotalTowns_; i++) {
		setTownCoordinates(townX, townY, i);
		getInformation(tName, tWelcome, i);
		mTown_[i]->createTown(townX, townY, (i+3*i+3),tName , tWelcome);
		mObject_[townX][townY] = "*";
	}
}

void Map::viewMap(int xLocation, int yLocation, int zoom)
{
	/* Will display an area around the map. The start point is xLocation, yLocation and the amount showed is zoom. */
	for (int i2 = (yLocation + zoom); i2 > (yLocation - zoom); i2--) {
		for (int i = (xLocation - zoom); i < (xLocation + zoom); i++) {

			/* Display the tiles */
			if ((i > 0) && (i < 201) && (i2 > 0) && (i2 < 201)) {
				
				/* Display object first. */
				if (mObject_[i][i2] != ".") {
					cout << mObject_[i][i2];
				}
				/* If there was no object, display the tile */
				else {
					cout << mTile_[i][i2];
				}
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
}

void Map::adjustHeroPosition()
{
	/* Restore object that the hero is on. (town probably) */
	mObject_[oldPosition_[0]][oldPosition_[1]] = mHiddenObject_;
			
	/* Store next object */
	mHiddenObject_ = mObject_[newPosition_[0]][newPosition_[1]];

	/* Update new hero object. */
	mObject_[newPosition_[0]][newPosition_[1]] = "o";

	/* Store current Position into oldPosition_ for future reference. */
	oldPosition_[0] = newPosition_[0];
	oldPosition_[1] = newPosition_[1];
}

bool Map::terrainCheck()
{
	/* If the tile that the hero is moving to is grass (in the future: and is walking (no boat, etc.), then */
	if (mTile_[newPosition_[0]][newPosition_[1]] == "_") { 
		/* Return 1 to indicate that the hero can travel safely on it */
		return 1;
	}
	/* Else if the terrain is water and the hero has a boat, then */
		/* Offer the hero an opportunity to ride the boat */

	return 0;
}

bool Map::moveHero(int newPosition[])
{
	/* No Variable Declarations */

	/* Store new position */
	newPosition_[0] = newPosition[0];
	newPosition_[1] = newPosition[1];

	/* If the new position isn't a map edge or something of that sort, then continue */
	if ((newPosition_[0] != 200) && (newPosition_[0] != 0) && (newPosition_[1] != 200) && (newPosition_[1] != 0)) {

		/* Perform a terrain check to make sure the hero can traverse the terrain */
		if (terrainCheck()) {

			/* Move the hero to the new position */
			adjustHeroPosition();

			/* Return 1 to indicate the hero moved */
			return 1;
		}
	}
	
	/* Return a 0 to indicate a failure to move if a check failed */
	return 0;
}


Location *Map::getTown(int x)
{
	return mTown_[x];
}

Location *Map::getTownAtHero(int x[])
{
	//cout << "x1: " << x[0] << "x2: " << x[1] << endl;

	/* Check every town */
	for (int i = 0; i < mTotalTowns_; i++) {

		/* If the hero is on the same position as the town, then... */
		if ((mTown_[i]->getTXLoc() == x[0]) && (mTown_[i]->getTYLoc() == x[1])) {

			return mTown_[i];
		}
	}

	return mTown_[0];
}

/* Debugging Statement
cout << "Hero: (" << HeroParty.getMainHero()->getXCoordinate() << "," << HeroParty.getMainHero()->getYCoordinate() << ")" << endl;
cout << "World: (" << WorldMap.getTown(i).getTXLoc() << "," << WorldMap.getTown(i).getTYLoc() << ")" << endl;
system("pause"); */


/*
Mountain Generation Algorithm

The mountain generation algorithm is basically how the mountains get placed onto the map.

	1. Create an integer grid.
		This grid is a copy of the map, only with numbers for mountains instead of "m". All values start at 0 base.
	2. Generate Mountain locations.
		Base mountain locations are generated at random and stored into variables.
		Check is performed to make sure that mountains aren't spawned in the safe zone.
	3. Place the mountains at the locations.
	4. Generate new mountains around base mountains.
		a. Scan map. If you find a mountain, place 4 new mountains around that mountain directly onto the integer grid.
			Note: There is a chance to not be placed to the north (or south, east, west) of a scanned mountain. The chance
				for a mountain to be spawned starts off high at first and then lower as the number of scans reaches the cut off point.
				The purpose of this is to create mountain shape diversity rather than all diamond mountains.
			Note: To prevent the scan from picking up newly generated mountains, a tiering system is used. This is the main reason
				that an integer grid was created. The scan picks up mountains of number "1" and then places mountains of number "2"
				around it. Then the scan starts again at "2" instead of "1". The scan will place mountains of number "3" around the
				mountains of "2".
		b. Continue to scan the map until the cutoffpoint is reached.
	5. Sometimes a spot between mountains will not be mountain so convert that grassy spot to a mountain.
		Note: This is important so that towns aren't spawned between mountains.
	6. Convert the mountains on the integer map into 
*/


/*
Diamond Generation Algorithm

int spawnRadius = 3; This holds the radius  divided by 2. TOO BAD, the algorithm demands an even radius.
int startPoint = mGridAverageLength - spawnRadius;
int endPoint = (mGridAverageLength_ - startPoint + 1) + mGridAverageLength_;
int spawnWidth = mGridAverageLength_ - startPoint + 1;

Clear mountains in a diamond around WHAT I WANT!!! HAHAHAHA
	THE DIAMOND ALGORITHM WAS DEVELOPED HERE! ~Donald Abdullah-Robinson
for (int a = startPoint; a < endPoint; a++) {
	for (int i = 0; i < spawnWidth; i++) {
			
		Lay out base diamond shapes
		mTile_[a+i][a-i] = "b";
		mTile_[a-i][a+i] = "b";

		Fill in the gaps of the diamond shape while trimming using the if statements.
		if (a < endPoint - 1) {
			mTile_[a+1-i][a+i] = "b";
		}
			
		if (i < spawnWidth - 1) {
			if (a < endPoint - 1) {
				mTile_[a+1+i][a-i] = "b";
			}
		}
	}
}
*/

/*
save with multiple heroes needs a quick test
*/