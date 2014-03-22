#include "equipmentSlots.h"
#include "item.h"
#include "world.h"

EquipmentSlot::EquipmentSlot()
{
	esIsFull_ = 0;
}

slot1::slot1()
{
	/* Initialize the pointer. Then make it point to a weapon. */
	s1Weapon_ = new Weapon;
}

slot2::slot2()
{
	s2Weapon_ = new Weapon;
	s2Shield_ = new Shield;
}

slot3::slot3()
{
	s3BodyArmor_ = new BodyArmor;
}

slot4::slot4()
{
	s4LegArmor_ = new LegArmor;
}

slot5::slot5()
{
	s5Ring_ = new Ring;
}

slot6::slot6()
{
	s6Ring_ = new Ring;
}

slot7::slot7()
{
	s7Necklace_ = new Necklace;
}

/* Slot clears */
void slot1::clear()
{
	s1Weapon_ =  new Weapon; 
	esIsFull_ = 0;
}

void slot2::clear()
{
	s2Weapon_ = new Weapon;
	s2Shield_ = new Shield;
	esIsFull_ = 0;
}

void slot3::clear()
{
	s3BodyArmor_ = new BodyArmor; 
	esIsFull_ = 0;
}

void slot4::clear()
{
	s4LegArmor_ = new LegArmor;
	esIsFull_ = 0;
}

void slot5::clear()
{
	s5Ring_ = new Ring;
	esIsFull_ = 0;
}

void slot6::clear()
{
	s6Ring_ = new Ring;
	esIsFull_ = 0;
}

void slot7::clear()
{
	s7Necklace_ = new Necklace; 
	esIsFull_ = 0;
}

/* Prints */

void slot1::printInformation()
{
	if (s1Weapon_->checkCreated()) {
		s1Weapon_->printWeaponInformation();
		s1Weapon_->printEquipmentInformation();
	}
	else {
		cout << "Nothing Equipped\n";
	}
}

void slot2::printInformation()
{
	if (s2Weapon_->checkCreated()) {
		s2Weapon_->printWeaponInformation();
		s2Weapon_->printEquipmentInformation();
	}
	else if (s2Shield_->checkCreated()) {
		s2Shield_->printShieldInformation();
		s2Shield_->printEquipmentInformation();
	}
	else {
		cout << "Nothing Equipped\n";
	}
}

void slot3::printInformation()
{
	if (s3BodyArmor_->checkCreated()) {
		s3BodyArmor_->printBodyArmorInformation();
		s3BodyArmor_->printEquipmentInformation();
	}
	else {
		cout << "Nothing Equipped\n";
	}
}

void slot4::printInformation()
{
	if (s4LegArmor_->checkCreated()) {
		s4LegArmor_->printLegArmorInformation();
		s4LegArmor_->printEquipmentInformation();
	}
	else {
		cout << "Nothing Equipped\n";
	}
}

void slot5::printInformation()
{
	if (s5Ring_->checkCreated()) {
		s5Ring_->printRingInformation();
		s5Ring_->printEquipmentInformation();
	}
	else {
		cout << "Nothing Equipped\n";
	}
}

void slot6::printInformation()
{
	if (s6Ring_->checkCreated()) {
		s6Ring_->printRingInformation();
		s6Ring_->printEquipmentInformation();
	}
	else {
		cout << "Nothing Equipped\n";
	}
}

void slot7::printInformation()
{
	if (s7Necklace_->checkCreated()) {
		s7Necklace_->printNecklaceInformation();
		s7Necklace_->printEquipmentInformation();
	}
	else {
		cout << "Nothing Equipped\n";
	}
}

/* Slot sets */

bool slot1::setWeapon(Weapon *newWeapon)
{
	if (esIsFull_ == 0) {
		s1Weapon_ = newWeapon;
		esIsFull_ = 1;
		return 1;
	}
	else {
		cout << "This slot is full." << endl;
		return 0;
	}
}

bool slot2::setWeapon(Weapon *newWeapon)
{
	if (esIsFull_ == 0) {
		s2Weapon_ = newWeapon;

		/* Clear out the shield */
		delete s2Shield_;
		s2Shield_ = new Shield;
		esIsFull_ = 1;
		return 1;
	}
	else {
		cout << "Weapon Slots are full." << endl;
		return 0;
	}
}

bool slot2::setShield(Shield *newShield)
{
	if (esIsFull_ == 0) {
		/* Clear out the weapon */
		delete s2Weapon_;
		s2Weapon_ = new Weapon;
		s2Shield_ = newShield;
		esIsFull_ = 1;
		return 1;
	}
	else {
		cout << "This Slot is full." << endl;
		return 0;
	}
}

bool slot3::setBodyArmor(BodyArmor *newBodyArmor)
{
	if (esIsFull_ == 0) {
		s3BodyArmor_ = newBodyArmor;
		esIsFull_ = 1;
		return 1;
	}
	else {
		cout << "This Slot is full." << endl;
		return 0;
	}
}

bool slot4::setLegArmor(LegArmor *newLegArmor)
{
	if (esIsFull_ == 0) {
		s4LegArmor_ = newLegArmor;
		esIsFull_ = 1;
		return 1;
	}
	else {
		cout << "This Slot is full." << endl;
		return 0;
	}
}

bool slot5::setRing(Ring *newRing)
{
	if (esIsFull_ == 0) {
		s5Ring_ = newRing;
		esIsFull_ = 1;
		return 1;
	}
	else {
		cout << "This Slot is full." << endl;
		return 0;
	}
}

bool slot6::setRing(Ring *newRing)
{
	if (esIsFull_ == 0) {
		s6Ring_ = newRing;
		esIsFull_ = 1;
		return 1;
	}
	else {
		cout << "This Slot is full." << endl;
		return 0;
	}
}

bool slot7::setNecklace(Necklace *newNecklace)
{
	if (esIsFull_ == 0) {
		s7Necklace_ = newNecklace;
		esIsFull_ = 1;
		return 1;
	}
	else {
		cout << "This Slot is full." << endl;
		return 0;
	}
}

