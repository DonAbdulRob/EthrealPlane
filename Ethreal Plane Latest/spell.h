/*
#ifndef SPELL_H
#define SPELL_H

class Spell
{
protected:
	string name_;

	bool targetSelf_; //allowable targets
	bool targetAllies;
	bool targetEnemies;
	bool hitSelf; //units it has to hit
	int hitsAllies;
	int hitsEnemies;

	int duration_;
	int manaCost_;

	ElementalDamages *sElementalDamages_;
	Resistances *resistances_;
	Attribute *attributes_;
	States *states_;
	Stats *stats_;

	

public:
	Spell();

	bool getTargetSelf() {return sTargetSelf_;}
	string getName() {return sName_;}
	void calculateManaCost();

};

#endif

*/