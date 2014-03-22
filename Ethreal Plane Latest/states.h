#ifndef _STATES_H_
#define _STATES_H_

class States
{
protected:
	
	bool alive_;
	bool magicTargetable_;
	bool physicalTargetable_;
	bool hurtOverTime_;
	bool healOverTime_;
	bool invulnerable_;
	bool silenced_;
	bool hasted_;
	bool slowed_;
	bool poisened_;

	int duration_; /* How long the heal/damage over times last */

public:
	States() {
		alive_ = 1;
		magicTargetable_ = 1;
		physicalTargetable_ = 1;
		hurtOverTime_ = 0;
		healOverTime_ = 0;
		invulnerable_ = 0;
		silenced_ = 0;
		hasted_ = 0;
		slowed_ = 0;
		poisened_ = 0;
		duration_ = 0;
	};

	bool getAlive              () {return alive_;}
	bool getMagicTargetable    () {return magicTargetable_;}
	bool getPhysicalTargetable () {return physicalTargetable_;}
	bool getHurtOverTime       () {return hurtOverTime_;}
	bool getHealOverTime       () {return healOverTime_;}
	bool getinvulnerable       () {return invulnerable_;}
	bool getSilenced           () {return silenced_;}

	void setAlive              (bool x) {alive_ = x;}
	void setMagicTargetable    (bool x) {magicTargetable_ = x;}
	void setPhysicalTargetable (bool x) {physicalTargetable_= x;}
	void setHurtOverTime       (bool x) {hurtOverTime_= x;}
	void setHealOverTime       (bool x) {healOverTime_= x;}
	void setInvulnerable       (bool x) {invulnerable_= x;}
	void setSilenced           (bool x) {silenced_= x;}
};

#endif
