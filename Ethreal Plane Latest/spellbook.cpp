/*
#include "spellbook.h"
#include "spell.h"

#include <string>
#include <iostream>
using namespace std;

SpellBook::SpellBook
{
	sbMaximumSpells = 20;
	sbTotalSpells_ = 0;
	sbSpells_ = new Spell*[sbMaximumSpells_];

	for (int i = 0; i < sbMaximumSpells_; i++) {
		sbSpells_[i] = new Spell;
	}
}


SpellBook::SpellBook(int maximumSpells)
{
	sbMaximumSpells = totalSpells;
	sbTotalSpells_ = 0;
	sbSpells_ = new Spell*[sbMaximumSpells_];

	for (int i = 0; i < sbMaximumSpells_; i++) {
		sbSpells_[i] = new Spell;
}

void SpellBook::addSpell(Spell *newSpell)
{
	if (sbTotalSpells_ <= sbMaximumSpells_) {
		for (int i = 0; i < sbTotalSpells_; i++) {
		if (sbSpells_[i]->getName() == "Undefined") {
			sbSpells_[i] = newSpell;
		}
	
		sbTotalSpells_++;
	}
	else
		cout << "This spellbook is full.";
}

void SpellBook::removeSpell(int x)
{
	sbSpells_[x] = new Spell;
}

void SpellBook::getSpell(int x)
{
	return sbSpells_[x];
}
*/

