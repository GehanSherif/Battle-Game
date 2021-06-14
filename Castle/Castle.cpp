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

void Castle::receiveDamage(double damage)
{
	Health -= damage;
	if (Health <= 0)
	{
		Health = 0;
	}
}

void Castle::receiveFrost(double frost)
{
	frostLevel += frost;
	if (frostLevel >= freezingThreshold)
	{
		frostLevel = 0;
		frosted = true;
	}
}

void Castle::SetmaxAttack(int n)
{
	maxAttack = n;
}

int Castle::GetmaxAttack() const
{
	return maxAttack;
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
void Castle::setFreezingThreshold(double th)
{
	freezingThreshold = th;
}
bool Castle::IsFrosted() const
{
	return frosted;
}

double Castle::getFreezingThreshold() const
{
	return freezingThreshold;
}
