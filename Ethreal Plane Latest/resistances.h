#ifndef _RESISTANCES_H_
#define _RESISTANCES_H_

class Resistances
{
protected:
	/* Resistances */
	int physicalArmor_;
	int fireResistance_;
	int windResistance_;
	int waterResistance_;
	int rockResistance_;
	int poisenResistance_;
	int staticResistance_;
	int psychicResistance_;
	int lightResistance_;
	int darkResistance_;
	int berserkResistance_;

	/* Elemental Protections */
	bool physicalProtected_;
	bool fireProtected_;
	bool windProtected_;
	bool waterProtected_;
	bool rockProtected_;
	bool poisenProtected_;
	bool staticProtected_;
	bool psychicProtected_;
	bool lightProtected_;
	bool darkProtected_;
	bool berserkProtected_;

public:
	Resistances() {
		physicalArmor_ = 0;
		fireResistance_ = 0;
		windResistance_ = 0;
		waterResistance_ = 0;
		rockResistance_ = 0;
		poisenResistance_ = 0;
		staticResistance_ = 0;
		psychicResistance_ = 0;
		lightResistance_ = 0;
		darkResistance_ = 0;
		berserkResistance_ = 0;

		physicalProtected_ = 0;
		fireProtected_ = 0;
		windProtected_ = 0;
		waterProtected_ = 0;
		rockProtected_ = 0;
		poisenProtected_ = 0;
		staticProtected_ = 0;
		psychicProtected_ = 0;
		lightProtected_ = 0;
		darkProtected_ = 0;
		berserkProtected_ = 0;
	};

	/* Gets */
	int getPhysicalarmor     () {return physicalArmor_;}
	int getFireResistance    () {return fireResistance_;}
	int getWindResistance    () {return windResistance_;}
	int getWaterResistance   () {return waterResistance_;}
	int getRockResistance    () {return rockResistance_;}
	int getPoisenResistance  () {return poisenResistance_;}
	int getPsychicResistance () {return psychicResistance_;}
	int getLightResistance   () {return lightResistance_;}
	int getDarkResistance    () {return darkResistance_;}
	int getBerserkResistance () {return berserkResistance_;}

	bool getPhysicalProtected () {return physicalProtected_;}
	bool getFireProtected     () {return fireProtected_;}
	bool getWindProtected     () {return windProtected_;}
	bool getWaterProtected    () {return waterProtected_;}
	bool getRockProtected     () {return rockProtected_;}
	bool getPoisenProtected   () {return poisenProtected_;}
	bool getStaticProtected   () {return staticProtected_;}
	bool getLightProtected    () {return lightProtected_;}
	bool getDarkProtected     () {return darkProtected_;}
	bool getBerserkProtected  () {return berserkProtected_;}

	/* Sets */
	void setPhysicalArmor     (int x) {physicalArmor_ = x;}
	void setFireResistance    (int x) {fireResistance_ = x;}
	void setWindResistance    (int x) {windResistance_ = x;}
	void setWaterResistance   (int x) {waterResistance_ = x;}
	void setRockResistance    (int x) {rockResistance_ = x;}
	void setPoisenResistance  (int x) {poisenResistance_ = x;}
	void setPsychicResistance (int x) {psychicResistance_ = x;}
	void setLightResistance   (int x) {lightResistance_ = x;}
	void setDarkResistance    (int x) {darkResistance_ = x;}
	void setBerserkResistance (int x) {berserkResistance_ = x;}

	void setPhysicalProtected  (bool x) {physicalProtected_ = x;}
	void setFireProtected      (bool x) {fireProtected_ = x;}
	void setWindProtected      (bool x) {windProtected_ = x;}
	void setWaterProtected     (bool x) {waterProtected_ = x;}
	void setRockProtected      (bool x) {rockProtected_ = x;}
	void setPoisenProtected    (bool x) {poisenProtected_ = x;}
	void setStaticProtected    (bool x) {staticProtected_ = x;}
	void setPsychicProtected   (bool x) {psychicProtected_ = x;}
	void setLightProtected     (bool x) {lightProtected_ = x;}
	void setDarkProtected      (bool x) {darkProtected_ = x;}
	void setBerserkProtected   (bool x) {berserkProtected_ = x;}
};

#endif