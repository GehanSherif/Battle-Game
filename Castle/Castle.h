#pragma once
#include "..\Defs.h"
#include "../Enemies/Enemy.h"
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
	void receiveDamage(double damage);
	void receiveFrost(double frost); 
	bool attackEnemey(Enemy*); //returns true if the enemy is dead due to the attack
	void frostEnemey(Enemy*);



};

