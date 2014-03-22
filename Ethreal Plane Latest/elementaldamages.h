#ifndef _ELEMENTALDAMAGES_H_
#define _ELEMENTALDAMAGES_H_

class ElementalDamages
{
protected:
	int fireDamage_;
	int windDamage_;
	int waterDamage_;
	int rockDamage_;
	int poisenDamage_;
	int staticDamage_;
	int psychicDamage_;
	int lightDamage_;
	int darkDamage_;
	int berserkDamage_;

public:
	ElementalDamages() {
		fireDamage_ = 0;
		windDamage_= 0;
		waterDamage_= 0;
		rockDamage_= 0;
		poisenDamage_= 0;
		staticDamage_= 0;
		psychicDamage_= 0;
		lightDamage_= 0;
		darkDamage_= 0;
		berserkDamage_= 0;
	};

	/* Gets */
	int getFireDamage    () {return fireDamage_;}
	int getWindDamage    () {return windDamage_;}
	int getWaterDamage   () {return waterDamage_;}
	int getRockDamage    () {return rockDamage_;}
	int getPoisenDamage  () {return poisenDamage_;}
	int getStaticDamage  () {return staticDamage_;}
	int getPsychicDamage () {return psychicDamage_;}
	int getLightDamage   () {return lightDamage_;}
	int getDarkDamage    () {return darkDamage_;}
	int getBerserkDamage () {return berserkDamage_;}

	/* Sets */
	void setFireDamage    (int x) {fireDamage_ = x;}
	void setWindDamage    (int x) {windDamage_ = x;}
	void setWaterDamage   (int x) {waterDamage_ = x;}
	void setRockDamage    (int x) {rockDamage_ = x;}
	void setPoisenDamage  (int x) {poisenDamage_ = x;}
	void setStaticDamage  (int x) {staticDamage_ = x;}
	void setPsychicDamage (int x) {psychicDamage_ = x;}
	void setLightDamage   (int x) {lightDamage_ = x;}
	void setDarkDamage    (int x) {darkDamage_ = x;}
	void setBerserkDamage (int x) {berserkDamage_ = x;}
};

#endif