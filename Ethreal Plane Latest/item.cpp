#include "item.h"
#include "enchantment.h"
#include "heroManager.h"
#include "resistances.h"
#include "attributes.h"
#include "utilities.h"

/*************
Constructors
*************/

/* Rarity Formula, save it :D */
//rarity = int((rarity * .5) + .5);

/* Item Constructor */
Item::Item()
{
	name_ = "Undefined";
	description_ = "Undefined";
	value_ = 0;
}

/* Consumable Constructor */
Consumable::Consumable()
{
	/* Set targets */
	targetEnemy_ = 0;
	targetHero_ = 0;

	heal_ = 0;
	damage_ = 0;

	attributes_ = new Attributes;
}

/* Equiment Constructor */
Equipment::Equipment()
{	
	rarityName_ = "Undefined";
	levelRequirement_ = 0;
	rarity_ = 0;
	plusValue_ = 0;
	socket_[0] = 0;
	socket_[1] = 0;

	baseAttributes_ = new Attributes;
	modifiedAttributes_ = new Attributes;
}

/* Weapon Constructor */
Weapon::Weapon()
{
	minimumDamage_ = 0;
	maximumDamage_ = 0;
}

/* 2nd Hand Constructor */
Shield::Shield()
{
	physicalArmor_ = 0;
}

/* Body Armor Constructor */
BodyArmor::BodyArmor()
{
	physicalArmor_ = 0;
}

/* Leg Armor Constructor */
LegArmor::LegArmor()
{
	physicalArmor_ = 0;
}

/* Necklace Constructor */
Necklace::Necklace()
{
	enchantment_ = new Enchantment[0];
	enchantment2_ = new Enchantment[0];

	resistances_ = new Resistances;
}

/*****************
Public Functions
*****************/

bool Equipment::checkCreated()
{
	if (name_ == "Undefined") {
		return 0;
	}
	else {
		return 1;
	}
}

void Equipment::setFullName()
{
	fullName_ = "";

	fullName_ += rarityName_ + " ";
	fullName_ += name_ + " +";
	fullName_ += returnString(plusValue_);
}

void Equipment::printEquipmentInformation()
{
	cout << "Vitility Bonus: " << modifiedAttributes_->getAttribute(0) << " ";
	cout << "Magic Bonus: " << modifiedAttributes_->getAttribute(1) << "\n";
	cout << "Dexterity Bonus: " << modifiedAttributes_->getAttribute(2) << " ";
	cout << "Luck Bonus: " << modifiedAttributes_->getAttribute(3) << "\n";
}

void Equipment::updateRarityModified()
{
	switch (rarity_) {
		case 0:
			rarityName_ = "Normal";
			break;
		case 1:
			rarityName_ = "Strong";
			for (int i = 0; i < 4; i++) {
				modifiedAttributes_->setAttribute(i, int(baseAttributes_->getAttribute(i) * 1.25)); // 25% bonus
			}
			break;
		case 2:
			rarityName_ = "Unique";
			for (int i = 0; i < 4; i++) {
				modifiedAttributes_->setAttribute(i, int(baseAttributes_->getAttribute(i) * 1.5)); //50% bonus
			}
			break;
		case 3:
			rarityName_ = "Elite";
			for (int i = 0; i < 4; i++) {
				modifiedAttributes_->setAttribute(i, int(baseAttributes_->getAttribute(i) * 2)); //100% bonus
			}
			break;
		case 4:
			rarityName_ = "Super";
			for (int i = 0; i < 4; i++) {
				modifiedAttributes_->setAttribute(i, int(baseAttributes_->getAttribute(i) * 2.5)); //150% bonus
			}
			break;
		case 5:
			rarityName_ = "Godly";
			for (int i = 0; i < 4; i++) {
				modifiedAttributes_->setAttribute(i, int(baseAttributes_->getAttribute(i) * 3)); //200% bonus
			}
			break;
		default:
			rarityName_ = "Weak";
			break;
	}

	setFullName();
}

void Equipment::setBaseAttributes(Attributes* newAttributes)
{
	baseAttributes_ = newAttributes;
}

void Equipment::setModifiedAttributes(Attributes* newAttributes)
{
	modifiedAttributes_ = newAttributes;
}

Attributes *Equipment::getBaseAttributes()
{
	return baseAttributes_;
}

Attributes *Equipment::getModifiedAttributes()
{
	return modifiedAttributes_;
}

void Weapon::printWeaponInformation()
{
	cout << "Weapon: " << fullName_ << " with ";
	cout << minimumDamage_ << " base damage and ";
	cout << maximumDamage_ << " maximum damage.\n";
}

void Shield::printShieldInformation()
{
	cout << "Shield: " << fullName_ << " with ";
	cout << physicalArmor_ << " physical armor and ";
	cout << dodgeChance_ << " dodge chance.\n";
}

void BodyArmor::printBodyArmorInformation() 
{
	cout << "Body Armor: " << fullName_ << " with ";
	cout << physicalArmor_ << " physical armor.\n";
}

void LegArmor::printLegArmorInformation() 
{
	cout << "Leg Armor: " << fullName_ << " with ";
	cout << physicalArmor_ << " physical armor.\n";
}

void Ring::printRingInformation() 
{
	cout << "Ring: " << fullName_ << ".\n";
}

void Necklace::printNecklaceInformation() 
{
	cout << "Necklace: " << fullName_ << ".\n";	
}

/* Set Functions */

void Item::setItemProperties(string name, string description, int value)
{
	name_ = name;
	description_ = description;
	value_ = value;
}

void Consumable::setConsumableProperties(bool targetEnemy, bool targetHero, int heal, int damage, int a0, int a1, int a2, int a3)
{
	/* Set targets */
	targetEnemy_ = targetEnemy;
	targetHero_ = targetHero;

	/* Set the type of changes the item can give */
	heal_ = heal;
	damage_ = damage;
	
	attributes_ = new Attributes;

}

void Consumable::setAll(string name, string description, int value, bool targetEnemy, bool targetHero, int heal, int damage, int a0, int a1, int a2, int a3)
{
	/* Set the item properties */
	setItemProperties(name, description, value);

	/* Set the consumable properties */
	setConsumableProperties(targetEnemy, targetHero, heal, damage, a0, a1, a2, a3);
}

/* Consumable information display function */
void Consumable::displayInformation()
{
	cout << "This consumable heals " << heal_ << "hit points.\n";
}

void Equipment::setEquipmentProperties(int levelRequirement, int attribute[])
{
	levelRequirement_ = levelRequirement;

	for (int i = 0; i < 4; i++) {
		baseAttributes_->setAttribute(i, attribute[i]);
	}

	updateRarityModified();
}

void Equipment::setSocketsAndRarity(int rarity, int socket1, int socket2)
{
	rarity_ = rarity;

	updateRarityModified();

	socket_[0] = socket1;
	socket_[1] = socket2;
}

void Weapon::setWeaponProperties(int minimumDamage, int maximumDamage)
{
	minimumDamage_ = minimumDamage;
	maximumDamage_ = maximumDamage;	
}

void Shield::setShieldProperties(int dodgeChance, int physicalArmor)
{
	dodgeChance_ = dodgeChance;
	physicalArmor_ = physicalArmor;
}

void BodyArmor::setBodyArmorProperties(int physicalArmor)
{
	physicalArmor_ = physicalArmor;
}

void LegArmor::setLegArmorProperties(int physicalArmor)
{
	physicalArmor_ = physicalArmor;
}

void Ring::setRingEnchantment(int enchantmentNumber)
{
	enchantment_ = new Enchantment[enchantmentNumber];
}

void Ring::setRingEnchantment2(int enchantmentNumber)
{
	enchantment2_ = new Enchantment[enchantmentNumber];
}

void Necklace::setNecklaceEnchantment(int enchantmentNumber)
{
	enchantment_ = new Enchantment[enchantmentNumber];
}

void Necklace::setNecklaceEnchantment2(int enchantmentNumber)
{
	enchantment2_ = new Enchantment[enchantmentNumber];
}

void Weapon::setAll(string name, string description, int value, int levelRequirement, int attribute[], int damage[])
{
	/* Item properties */
	setItemProperties(name, description, value);

	/* Equipment Properties */
	setEquipmentProperties(levelRequirement, attribute);

	/* Weapon Properties */
	minimumDamage_ = damage[0];
	maximumDamage_ = damage[1];
}

void Shield::setAll(string name, string description, int value, int levelRequirement, int attribute[], int dodge, int armor)
{
	/* Item properties */
	setItemProperties(name, description, value);

	/* Equipment Properties */
	setEquipmentProperties(levelRequirement, attribute);

	dodgeChance_ = dodge;
	physicalArmor_ = armor;
}

void BodyArmor::setAll(string name, string description, int value, int levelRequirement, int attribute[], int armor)
{
	/* Item properties */
	setItemProperties(name, description, value);

	/* Equipment Properties */
	setEquipmentProperties(levelRequirement, attribute);

	physicalArmor_ = armor;
}

void LegArmor::setAll(string name, string description, int value, int levelRequirement, int attribute[], int armor)
{
	/* Item properties */
	setItemProperties(name, description, value);

	/* Equipment Properties */
	setEquipmentProperties(levelRequirement, attribute);

	physicalArmor_ = armor;
}

void Ring::setAll(string name, string description, int value, int levelRequirement, int attribute[])
{
	/* Item properties */
	setItemProperties(name, description, value);

	/* Equipment Properties */
	setEquipmentProperties(levelRequirement, attribute);
}

void Necklace::setAll(string name, string description, int value, int levelRequirement, int attribute[])
{
	/* Item properties */
	setItemProperties(name, description, value);

	/* Equipment Properties */
	setEquipmentProperties(levelRequirement, attribute);
}

