#ifndef _FULLEQUIPMENT_H_
#define _FULLEQUIPMENT_H_

/* File includes and specify namespace */
#include <iostream>
#include <string>
using namespace std;

/* Forward Class Declarations */
class EquipmentSlot;
class slot1;
class slot2;
class slot3;
class slot4;
class slot5;
class slot6;
class slot7;

/* Class FullEquipment */
class FullEquipment
{
protected:
	EquipmentSlot *feAllSlots_[7];

	slot1* feSlot1_;
	slot2* feSlot2_;
	slot3* feSlot3_;
	slot4* feSlot4_;
	slot5* feSlot5_;
	slot6* feSlot6_;
	slot7* feSlot7_;

public:
	FullEquipment();

	/* Gets */
	EquipmentSlot* getSlot(int x);
	slot1* getSlot1() {return feSlot1_;}
	slot2* getSlot2() {return feSlot2_;}
	slot3* getSlot3() {return feSlot3_;}
	slot4* getSlot4() {return feSlot4_;}
	slot5* getSlot5() {return feSlot5_;}
	slot6* getSlot6() {return feSlot6_;}
	slot7* getSlot7() {return feSlot7_;}

	/* Sets */
	void setSlot(int x, EquipmentSlot* name);
};

#endif
