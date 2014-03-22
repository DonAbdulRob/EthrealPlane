#include "randomEvent.h"

RandomEvent::RandomEvent()
{
	event_ = 0;
	strength_ = 0;
	chance_ = 0;
	duration_ = 0;
}

RandomEvent::RandomEvent(int newEvent, int strength, int chance, int duration)
{
	setAll(newEvent, strength, chance, duration);
}

void RandomEvent::setAll(int newEvent, int strength, int chance, int duration)
{
	event_ = newEvent;
	strength_ = strength;
	chance_ = chance;
	duration_ = duration;
}
