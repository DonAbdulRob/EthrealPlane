#ifndef _FIGHTER_H_
#define _FIGHTER_H_

class Fighter
{
private:
	int isPlayerNumber_;

public:
	Fighter() {};
	
	int dexterity_;

	/* Ovveride Operator */
	bool operator < (const Fighter& rhs)
	{
		return dexterity_ < rhs.dexterity_;
	}

	/* Sets */
	void setDexterity(int x) {dexterity_ = x;}
	void setPlayerNumber(int x) {isPlayerNumber_ = x;}

	/* Gets */
	int getDexterity() {return dexterity_;}
	int getPlayerNumber() {return isPlayerNumber_;}
};

#endif
