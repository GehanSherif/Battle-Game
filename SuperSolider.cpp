#include "SuperSolider.h"
#include <math.h>


SuperSolider::SuperSolider(int id)
{
	ssID = id;
	Distance = 1;
	Destiny = 1;	//acts as a guard in case of accidental calls to move()
}

int SuperSolider::getDistance()
{
	return Distance;
}

int SuperSolider::getDestiny()
{
	return Destiny;
}

void SuperSolider::setDestiny(int d)
{
	Destiny = d;
}

void SuperSolider::move()
{
	if (abs(Distance - Destiny) > 3)
	{
		Distance += speed;
	}
	else
		Distance = Destiny;
}
