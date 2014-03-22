#ifndef _HEROESCONTAINER_H
#define _HEROESCONTAINER_H

/* File includes and specify namespace */
#include <iostream>
#include <string>
using namespace std;

/* Forward Class Declarations */
class PartyMember;
class MainHero;
class Consumable;
class MenuInput;

/* Class HeroManager aka HeroParty aka WHATEVERTHEFUCK YOU WANT */
class HeroManager
{
private:
	void setHeroBeingManaged(string);
	void messagePlus(string);

protected:

	/* Variables */
	MainHero *hmHero_;
	PartyMember *hmPartyHero_[3];
	MenuInput *hmMenu_;

	int hmCurrentFreeSlot_;
	int hmTotalHeroes_;
	int hmHeroBeingManaged_;

	/* Methods */
	void swapHeroes(int, int);
	void replaceHero(int a, int b) {hmPartyHero_[a] = hmPartyHero_[b];}
	void setName(int[], string[]);

	void manageConsumables();

public:
	HeroManager();

	/* General */
	bool generateNewRandomPartyMember();
	void removePartyMember();

	string returnPartyNames(bool);
	void showFullPartyNames();
	void showFullPartyStats();
	
	void fullHealWholeParty();
	void healthRestoreWholeParty();
	void manaRestoreWholeParty();

	void giveExperience(int);

	void manageInventories();
	void manageEquipment(int);

	bool aquireWeapon(string, Weapon*);
	bool aquireShield(string, Shield*);
	bool aquireBodyArmor(string, BodyArmor*);
	bool aquireLegArmor(string, LegArmor*);
	bool aquireRing(string, Ring*);
	bool aquireNecklace(string, Necklace*);

	void aquireTargetWeapon    (int);
	void aquireTargetShield    (int);
	void aquireTargetBodyArmor (int);
	void aquireTargetLegArmor  (int);
	void aquireTargetRing      (int);
	void aquireTargetNecklace  (int);

	/* Gets */
	MainHero* getMainHero() {return hmHero_;}
	PartyMember* getPartyMember(int x) { return hmPartyHero_[x-1]; }
	PartyMember* getHero(int x);

	int getTotalHeroes     () {return hmTotalHeroes_;}
	int getCurrentFreeSlot () {return hmCurrentFreeSlot_;}
};

#endif

