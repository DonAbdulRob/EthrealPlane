#ifndef _WORLD_H
#define _WORLD_H

class Inventory;
class ConsumableInventory;
class EquipmentInventory;
class QuestInventory;
class JunkInventory;
class Consumables;
class Weapon;
class Shield;
class BodyArmor;
class LegArmor;
class Ring;
class Necklace;
class RandomJunk;
class FileItems;
class HeroManager;
class Map;
class Location;
class MenuInput;

class World
{
private:
	HeroManager *heroParty_;
	Map *map_;
	FileItems *fileItems_;
	MenuInput *wMenu_;

	bool computeEncounter();

	void displayIntroduction();
	void setWorldView();
	void displayHelp();
	void saveGame();
	void loadGame();
	void skipHeroCreation();
	void createMainHero();

	void enterTown();
	void enterInn(Location*);
	void enterGuild(Location*);

public:
	World(void);

	HeroManager *getHeroParty();

	void takeAction();
};

#endif