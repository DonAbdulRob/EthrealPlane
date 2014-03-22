#include "fullEquipment.h"
#include "equipmentSlots.h"

/* Constructor */

FullEquipment::FullEquipment()
{
	/* Create the new slots */
	feSlot1_ = new slot1;
	feSlot2_ = new slot2;
	feSlot3_ = new slot3;
	feSlot4_ = new slot4;
	feSlot5_ = new slot5;
	feSlot6_ = new slot6;
	feSlot7_ = new slot7;

	/* Store the location of the pointers in feAllSlots */
	feAllSlots_[0] = feSlot1_;
	feAllSlots_[1] = feSlot2_;
	feAllSlots_[2] = feSlot2_;
	feAllSlots_[3] = feSlot2_;
	feAllSlots_[4] = feSlot2_;
	feAllSlots_[5] = feSlot2_;
	feAllSlots_[6] = feSlot2_;
}

/* Public methods */

EquipmentSlot* FullEquipment::getSlot(int x)
{
	return feAllSlots_[x];
}

void FullEquipment::setSlot(int x, EquipmentSlot* name)
{
	feAllSlots_[x-1] = name;
}

