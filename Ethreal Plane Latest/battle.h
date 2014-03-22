#ifndef _BATTLE_H_
#define _BATTLE_H_

#include <string>
using namespace std;

class Opponent;
class Fighter;
class HeroManager;
class List;
class FileItems;
class MenuInput;

class Battle 
{
protected:
	Opponent *enemy_; // Enemy = new Opponent[4];
	HeroManager *heroParty_;
	Fighter *fighter_; /* Create 8 battlefighters that hold their dexterity. */
	FileItems *fileItems_;
	MenuInput *menu_;

	int totalEnemies_;
	int totalBattlers_;
	int currentRound_;
	int currentFighter_;
	int heroTarget_;
	bool hasFled_;
	bool mainHeroDied_;

	/* Initialize opponents */
	void createEnemies();

	/* Starts Battle */
	void increaseRound();
	void displayEncounterMessage();
	void manageTurns();
	void computeDexterityTurnOrder();
	bool handleDeath();
	
	void computerTakeTurn();
	void enemyAttack();
	
	void heroTakeTurn();
	bool heroAttack();
	bool getUserTarget();

	void showHeroPartyInformation();
	void showEnemyPartyInformation();

	void collectExperience();
	void collectGold();
	void collectItem();
	void victory();

public:
	Battle() {};
	Battle(HeroManager*&, FileItems*);

	void fight();

	bool heroWon() {if (mainHeroDied_ == 1) return 0; else return 1;}
};

#endif


