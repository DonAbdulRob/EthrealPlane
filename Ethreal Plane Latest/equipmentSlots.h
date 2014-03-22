#ifndef _EQUIPMENTSLOTS_H
#define _EQUIPMENTSLOTS_H

/* File includes and specify namespace */
#include <iostream>
#include <string>
using namespace std;

/* Forward class declaration */
class Weapon;
class Shield;
class BodyArmor;
class LegArmor;
class Ring;
class Necklace;

/* Class Equipment Slots */
class EquipmentSlot {
protected:
	bool esIsFull_;

public:
	EquipmentSlot();

	/* Sets */
	void setSlotFull() {esIsFull_ = 1;}
	void setSlotEmpty() {esIsFull_ = 0;}

	/* Gets */
	bool isFull() {return esIsFull_;}

	virtual void clear()=0;
};

class slot1: public EquipmentSlot
{
protected:
	Weapon *s1Weapon_;

public:
	slot1();

	/* General */
	void clear();

	/* Sets */
	bool setWeapon(Weapon*);
	void printInformation();

	/* Gets */
	Weapon* getWeapon() {return s1Weapon_;}
};

class slot2: public EquipmentSlot
{
protected:
	Weapon *s2Weapon_;
	Shield *s2Shield_;
	
public:
	slot2();

	/* General */
	void clear();

	/* Sets */
	bool setWeapon(Weapon*);
	bool setShield(Shield*);
	void printInformation();

	/* Gets */
	Weapon* getWeapon() {return s2Weapon_;}
	Shield* getShield() {return s2Shield_;}

};

class slot3: public EquipmentSlot
{
protected:
	BodyArmor *s3BodyArmor_;

public:
	slot3();

	/* General */
	void clear();
	void printInformation();

	/* Sets */
	bool setBodyArmor(BodyArmor*);

	/* Gets */
	BodyArmor* getBodyArmor() {return s3BodyArmor_;}

};

class slot4: public EquipmentSlot
{
protected:
	LegArmor *s4LegArmor_;
	
public:
	slot4();

	/* General */
	void clear();
	void printInformation();

	/* Sets */
	bool setLegArmor(LegArmor*);

	/* Gets */
	LegArmor* getLegArmor() {return s4LegArmor_;}

};

class slot5: public EquipmentSlot
{
protected:
	Ring* s5Ring_;
	
public:
	slot5();

	/* General */
	void clear();
	void printInformation();

	/* Sets */
	bool setRing(Ring*);

	/* Gets */
	Ring* getRing() {return s5Ring_; esIsFull_ = 0;}

};

class slot6: public EquipmentSlot
{
protected:
	Ring* s6Ring_;
	
public:
	slot6();

	/* General */
	void clear();
	void printInformation();

	/* Sets */
	bool setRing(Ring*);

	/* Gets */
	Ring* getRing() {return s6Ring_;}

};

class slot7: public EquipmentSlot
{
protected:
	Necklace* s7Necklace_;
	
public:
	slot7();

	/* General */
	void clear();
	void printInformation();

	/* Sets */
	bool setNecklace(Necklace*);

	/* Gets */
	Necklace* getNecklace() {return s7Necklace_;}

};


#endif

