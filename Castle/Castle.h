#pragma once
#include "..\Defs.h"
class Castle
{
	//inputted from file
	double Health;
	int maxAttack; //Max number of enemies a castle can attack at any time step
	double castlePower;
	double freezingThreshold;

	//must be initialized
	bool frosted = false;
	double frostLevel = 0;

public:
	//getters
	bool IsFrosted() const;
	int GetmaxAttack() const;
	double GetHealth() const;
	double GetcastlePower() const;
	double getFreezingThreshold() const;


	//setters
	void SetHealth(double h);
	void SetmaxAttack(int n);
	void SetcasltePower(double POW);
	void SetFrosted(bool f);
	void setFreezingThreshold(double th);


	//operations
	void receiveDamage(double damage); //returns true in case the castle is killed
	void receiveFrost(double frost); 



};

