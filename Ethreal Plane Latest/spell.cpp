/*
#include "spell.h"

Spell::Spell()
{
	sName_ = "undefined";

	sElementalDamages_ = new ElementalDamages;
}

void Spell::calculateManaCost()
{
	/* A calculation of TOTAL effects the the spell has. This is calculated via the total postive and negative
	effects this spell has on targets.
	
	Damage Spells does 5 damage. 5 spellPower. Friendly Target = Negative it.
											   Enemy Target = Normal.
	
	Each additional friendly target = 1.5* the spellPower more.
	Each additional enemy target = 1.5* the spellPower less.

	Spell is global (hits everybody) = 1/2 spell Power. 
	
	
	

}
*/