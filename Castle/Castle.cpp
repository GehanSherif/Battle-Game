#include "Castle.h"
#include "../Enemies/Healer.h"




void Castle::SetHealth(double h)
{
	if(h > 0)
		Health = h;
	else
		Health = 0; // killed
}

void Castle::SetOriginalHealth(double h)
{
	if (h > 0)
		originalHealth = h;
	else
		originalHealth = 0; // killed
}

double Castle::GetHealth() const
{
	return Health;
}

void Castle::receiveDamage(double damage)
{
	totalDamage += damage;
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
	return enemy->recieveFrost(frost); //true if frosted
}

void Castle::sendSS(int destiny)
{
	if (totalSentSS == 3) //max is three
		return;
	totalSentSS++;
	superSoliders.enqueue(new SuperSolider(destiny, 0.2*Health));
}

void Castle::useHealerTools(Enemy* healer)
{
	Healer* H = dynamic_cast<Healer*>(healer);
	if (H == nullptr)
		return;
	if (!(H->isDead()) && H->GetDistance() > 5) //must be dead and within 5 meters
		return;

	Health += H->getPower();
}

bool Castle::checkThreshold()
{
	if (Health < 0.3 * originalHealth)
		return true;
	else
		return false;
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

}
bool Castle::IsFrosted() const
{
	return frosted;
}

double Castle::getFreezingThreshold() const
{
	return freezingThreshold;
}

double Castle::getTotalDamage() const
{
	return totalDamage;
}

Queue<SuperSolider*>* Castle::getPtrSS()
{
	return &superSoliders;
}
