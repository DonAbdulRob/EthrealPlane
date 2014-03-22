#ifndef _TURNORDERMANAGEMENT_H_
#define _TURNORDERMANAGEMENT_H_

#include "life.h"
#include "fighter.h"
#include <list>

void turnOrderManager          (int currentRound, bool &hasFled, bool &keepBattling);
void computeDexterityTurnOrder (list<Fighter> &turnOrder, Fighter BattleFighter[]);

#endif

