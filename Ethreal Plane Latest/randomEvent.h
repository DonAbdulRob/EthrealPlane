#ifndef _RANDOMEVENT_H_
#define _RANDOMEVENT_H_

class RandomEvent
{
protected:
	int event_;
	int strength_;
	int chance_;
	int duration_;

public:
	RandomEvent();
	RandomEvent(int, int, int, int);

	/* Gets */
	int getEvent() {return event_;}
	int getStrength() {return strength_;}
	int getChance() {return chance_;}
	int getDuration() {return duration_;}
	
	/* Sets */
	void setAll(int, int, int, int);
};

#endif