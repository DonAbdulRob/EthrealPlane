#include "displayPartyInformation.h"
#include "userInputTemplate.h"
#include "battle.h"
#include "utilities.h"

#include <iostream>
#include <string>


/* Let user select hero and then display that heroes stats. */
void showFullPartyStats()
{
	/* Variable Declarations */
	int userChoice = 0;

	/* Get user input on the hero to view */
	userChoice = takeUserInputNumber("Which heroes stats would you like to view?\n" + returnPartyNames(1),
		"You didn't select a hero", totalHeroes, (totalHeroes+2));

	/* Put userChoice on programmer level */
	userChoice--;

	/* Show stats of the chosen hero */
	HeroParty.getHero(userChoice)->printStats();
}

