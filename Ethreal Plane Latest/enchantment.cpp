#include "enchantment.h"
#include "attributes.h"
#include "randomEvent.h"
#include "resistances.h"

#include <iostream>
#include <string>

/* Constructors */
Enchantment::Enchantment()
{
	resistances_ = new Resistances;
	attributes_ = new Attributes;
	randomEvent_ = new RandomEvent;

	bonusDamage_ = 0;
	bonusDamageOccurance_ = 0;
}

/* Gets */
Resistances *Enchantment::getResistances()
{
	return resistances_;
}

Attributes *Enchantment::getAttributes()
{
	return attributes_;
}

RandomEvent *Enchantment::getRandomEvent()
{
	return randomEvent_;
}