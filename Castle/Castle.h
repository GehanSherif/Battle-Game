#pragma once
#include "..\Defs.h"
class Castle
{
	double Health;
	int matAttack; //Max number of enemies a castle can attack at any time step
	double castlePower;
	bool frosted = false;

public:
	void SetHealth(double h);
	double GetHealth() const;
	bool getDamage(double damage); //returns true in case the castle is killed

	void SetmatAttack(int n);
	int GetmatAttack() const;

	void SetcasltePower(double POW);
	double GetcastlePower() const;

	void SetFrosted(bool f);
	bool IsFrosted() const;
};

