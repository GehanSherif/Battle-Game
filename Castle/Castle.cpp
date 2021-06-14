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

bool Castle::getDamage(double damage)
{
	Health -= damage;
	if (Health <= 0)
	{
		Health = 0;
		return true;
	}
	else
		return false;
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

void Castle::SetFrosted(bool f)
{
	frosted = f;
}
bool Castle::IsFrosted() const
{
	return frosted;
}