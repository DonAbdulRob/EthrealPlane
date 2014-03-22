#ifndef _ENCHANTMENT_H_
#define _ENCHANTMENT_H_

class Resistances;
class Attributes;
class RandomEvent;

class Enchantment
{
protected:
	Resistances *resistances_;
	Attributes *attributes_;
	RandomEvent *randomEvent_;

	int bonusDamage_;
	int bonusDamageOccurance_;

public:
	Enchantment();

	/* General */
	
	/* Gets */
	Resistances *getResistances();
	Attributes *getAttributes();
	RandomEvent *getRandomEvent();

	int getBonusDamage() {return bonusDamage_;}
	int getBonusDamageOccurance() {return bonusDamageOccurance_;}

	/* Sets */
	void setResistances(Resistances*);
	void setAttributes(Attributes*);
	void setRandomEvent(RandomEvent*);

	void setBonusDamage(int x) {bonusDamage_ = x;}
	void setBonusDamageOccurance(int x) {bonusDamageOccurance_ = x;}
};

#endif

