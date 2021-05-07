#include "Castle.h"




void Castle::SetHealth(double h)
{
	if(h > 0)
		Health = h;
	else
		Health = 0; // killed
}

double Castle::GetHealth() const
{
	return Health;
}

void Castle::SetmatAttack(int n)
{
	matAttack = n;
}

int Castle::GetmatAttack() const
{
	return matAttack;
}

void Castle::SetcasltePower(double POW)
{
	castlePower = POW;
}

double Castle::GetcastlePower() const
{
	return castlePower;
}