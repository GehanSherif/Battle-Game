#include "Castle.h"
#include "../Enemies/Healer.h"




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

bool Castle::attackEnemy(Enemy* enemy)
{
	Healer* healer = dynamic_cast<Healer*>(enemy);
	int k;
	if (healer != nullptr)
		k = 2;
	else
		k = 1;
	double damage = 1.0 * castlePower / (k * enemy->GetDistance());
	return enemy->recieveDamage(damage); //true if dead
}

bool Castle::frostEnemy(Enemy* enemy)
{
	Healer* healer = dynamic_cast<Healer*>(enemy);
	int k;
	if (healer != nullptr)
		k = 2;
	else
		k = 1;
	double frost = 1.0 * castlePower / (k * enemy->GetDistance());
	return enemy->recieveFrost(frost); //true if dead
}

void Castle::sendSS()
{

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
Castle::Castle()
{
	superSoliders.enqueue(new SuperSolider(1));
	superSoliders.enqueue(new SuperSolider(2));
	superSoliders.enqueue(new SuperSolider(3));
}
bool Castle::IsFrosted() const
{
	return frosted;
}

double Castle::getFreezingThreshold() const
{
	return freezingThreshold;
}
