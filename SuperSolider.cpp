#include "SuperSolider.h"
#include <math.h>

SuperSolider::SuperSolider(int distance, int destiny): Distance(distance), Destiny(destiny)
{
}

int SuperSolider::getDistance()
{
	return Distance;
}

int SuperSolider::getDestiny()
{
	return Destiny;
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
