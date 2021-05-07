#pragma once
#include "..\Defs.h"
class Castle
{
	double Health;
	int matAttack; //Max number of enemies a castle can attack at any time step
	double castlePower;

	//
	// TODO: Add More Data Members As Needed
	//

public:

	void SetHealth(double h);
	double GetHealth() const;

	//
	// TODO: Add More Member Functions As Needed
	//

};

