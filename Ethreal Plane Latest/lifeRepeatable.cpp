#include "lifeRepeatable.h"
#include "resistances.h"
#include "elementalDamages.h"
#include "states.h"
#include "attributes.h"

LifeRepeatable::LifeRepeatable()
{
	maximumHitPoints_ = 0;
	maximumManaPoints_ = 0;
	physicalDamageMinimum_ = 0;
	physicalDamageMaximum_ = 0;
	criticalHitChance_ = 0;
	doubleStrikeChance_ = 0;
	divineStrikeChance_ = 0;
	dodgeChance_ = 0;

	resistances_ = new Resistances;
	elementalDamages_ = new ElementalDamages;
	states_ = new States;
	attributes_ = new Attributes;
}

void LifeRepeatable::setResistances(Resistances* newReistances)
{
	resistances_ = newReistances;
}

void LifeRepeatable::setElementalDamages(ElementalDamages* newElementalDamages)
{
	elementalDamages_ = newElementalDamages;
}

void LifeRepeatable::setStates(States* newStates)
{
	states_ = newStates;
}

void LifeRepeatable::setAttributes(Attributes* newAttributes)
{
	attributes_ = newAttributes;
}

Resistances *LifeRepeatable::getResistances()
{
	return resistances_;
}

ElementalDamages *LifeRepeatable::getElementalDamages()
{
	return elementalDamages_;
}

States *LifeRepeatable::getStates()
{
	return states_;
}

Attributes *LifeRepeatable::getAttributes()
{
	return attributes_;
}

