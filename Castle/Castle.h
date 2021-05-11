#pragma once
#include "..\Defs.h"
class Castle
{
	double Health;
	int matAttack; //Max number of enemies a castle can attack at any time step
	double castlePower;
	bool frosted=0;
	//
	// TODO: Add More Data Members As Needed
	//

public:

	void SetHealth(double h);
	double GetHealth() const;

	void SetmatAttack(int n);
	int GetmatAttack() const;

	void SetcasltePower(double POW);
	double GetcastlePower() const;

	void SetFrosted(bool f);
	bool IsFrosted() const;

	//
	// TODO: Add More Member Functions As Needed
	//

};

