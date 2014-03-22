#ifndef _LIFEREPEATABLE_H_
#define _LIFEREPEATABLE_H_

class Resistances;
class ElementalDamages;
class Stats;
class States;
class Attributes;

class LifeRepeatable
{
protected:
	int maximumHitPoints_;
	int maximumManaPoints_;

	int physicalDamageMinimum_;
	int physicalDamageMaximum_;
	int criticalHitChance_;
	int doubleStrikeChance_;
	int divineStrikeChance_;

	int dodgeChance_;
	
	Resistances *resistances_;
	ElementalDamages *elementalDamages_;
	States *states_;
	Attributes *attributes_;

public:
	LifeRepeatable();

	/* Gets */
	int getMaximumHitPoints  () {return maximumHitPoints_;}
	int getMaximumManaPoints () {return maximumManaPoints_;}
	int getPhysicalDamageMinimum () {return physicalDamageMinimum_;}
	int getPhysicalDamageMaximum () {return physicalDamageMaximum_;}
	int getCriticalHitChance     () {return criticalHitChance_;}
	int getDoubleStrikeChance    () {return doubleStrikeChance_;}
	int getDivineStrikeChance    () {return divineStrikeChance_;}
	int getDodgeChance       () {return dodgeChance_;}

	Resistances *getResistances();
	ElementalDamages *getElementalDamages();
	States *getStates();
	Attributes *getAttributes();

	/* Sets */
	void setMaximumHitPoints  (int x) {maximumHitPoints_ = x;}
	void setMaximumManaPoints (int x) {maximumManaPoints_ = x;}
	void setPhysicalDamageMinimum (int x) {physicalDamageMinimum_ = x;}
	void setPhysicalDamageMaximum (int x) {physicalDamageMaximum_ = x;}
	void setCriticalHitChance     (int x) {criticalHitChance_ = x;}
	void setDoubleStrikeChance    (int x) {doubleStrikeChance_ = x;}
	void setDivineStrikeChance    (int x) {divineStrikeChance_ = x;}
	void setDodgeChance       (int x) {dodgeChance_ = x;}

	void setResistances(Resistances*);
	void setElementalDamages(ElementalDamages*);
	void setStates(States*);
	void setAttributes(Attributes*);

	/* Increases */
	void increasePhysicalDamageMinimum(int x) {physicalDamageMinimum_ += x;}
	void increasePhysicalDamageMaximum(int x) {physicalDamageMaximum_ += x;}

	/* Decreases */
	void decreasePhysicalDamageMinimum(int x) {physicalDamageMinimum_ -= x;}
	void decreasePhysicalDamageMaximum(int x) {physicalDamageMaximum_ -= x;}
};


#endif

