#include <time.h>
#include <string>
#include "world.h"

/* Initializes key globals to the for the game and serves as a stepping stone into the game*/
int main()
{
	/* Initialize Pseudo-Random Number Generation */
	srand(int(time(NULL)));
    
	/* Create a new game world */
	World *Game = new World;

	/* Start the game! */
	Game->takeAction();
}
