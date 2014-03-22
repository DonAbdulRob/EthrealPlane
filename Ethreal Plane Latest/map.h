#ifndef _MAP_H_
#define _MAP_H_

/* Specify includes and namespace */
#include <string>
using namespace std;

/* Forward declaration for needed classes */
class Location;
class MainHero;

class Map
{
private:
	/* Variables */
	int mXLength_;
	int mYLength_;
	int mGridAverageLength_;
	int oldPosition_[2];
	int newPosition_[2];

	string mTile_[201][201]; // String Array of tiles to get placed on the map.
	string mObject_[201][201]; // String array of objects to get placed on the map.
	string mHiddenObject_;	// Holds the object type the hero is standing on.

	int mTotalBaseMountains_;
	int mCutoffPoint_;
	int mMountainDistance_;
	int mViewRegion_;
	int mTotalTowns_;

	Location **mTown_;

	/* Methods */
	void setMapSize(int x, int y) { mXLength_ = x; mYLength_ = y; }
	void clearObjects();
	void setTownCoordinates(int &, int &, int);
	void getInformation(string &, string &, int);
	void calculateGridAverageLength();
	
	void adjustHeroPosition();
	bool terrainCheck();

	/* Functions to consider for the future
		void addGoldchests(); //void addItemChests(); //void placemonsters(); //void placeDungeons(); */

public:
	Map(void);
	Map(int, int, int[]);
	~Map(void);

	bool moveHero(int []);

	void viewMap(int, int, int);
	void shiftHero(int, int);
	void fillMap(int);
	void createMountains(int);
	void createTowns();
	void mainHeroDied(int, int);

	/* Gets */
	int getViewRegion() {return mViewRegion_;}
	int getXLength() {return mXLength_;}
	int getYLength() {return mYLength_;}
	int getTotalTowns() {return mTotalTowns_;}
	Location *getTown(int x);
	Location *getTownAtHero(int[]);

	/* Sets */
	void setViewRegion(int x) { mViewRegion_ = x; }
};

#endif

/*

Objects:

Grass - Mountain - Gold - Towns - Hero
-       m          b      *       o


*/