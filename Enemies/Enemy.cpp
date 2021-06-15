#include "Enemy.h"
#include "../Battle.h"



Enemy::Enemy(int id, int arrTime, int enemyHealth, int enemyPower, int enemySpeed, int relPeriod)
	: ID(id), ArrvTime(arrTime), originalHealth(enemyHealth), power(enemyPower), speed(enemySpeed), reloadPeriod(relPeriod)
	, frostThreshold(0.33 * enemyHealth), totalFrostedTime(relPeriod)
{
	SetStatus(INAC);
	
	Distance = MaxDistance;
	timeToEndReload = 0;
	currentFrost = 0;
	timeTogetUnfrosted = 0;
}

int Enemy::GetID() const
{
	return ID;
}


void Enemy::SetStatus(ENMY_STATUS s)
{
	status = s;
}


ENMY_STATUS Enemy::GetStatus() const
{
	return status;
}


bool Enemy::recieveDamage(double damage)
{
	currentHealth -= damage;
	if (currentHealth <= 0)
	{
		currentHealth = 0;
		SetStatus(KILD);
		killedTime = Battle::getCurrentTimeStep();
		return true; //dead
	}
	else
		return false; //not dead
}

void Enemy::reduceFrostedTime()
{
	if (timeTogetUnfrosted == 0)
		if (!isDead())
			SetStatus(ACTV);
	else
		timeTogetUnfrosted--;

}

bool Enemy::recieveFrost(double frost)
{

	if (currentFrost + frost >= frostThreshold)
	{
		currentFrost = 0;
		SetStatus(FRST);
		return true; //means enemy got frosted
	}
	else
	{
		currentFrost += frost;
		return false;
	}
}

bool Enemy::isDead() const
{
	if (GetStatus() == KILD)
		return true;
	else
		return false;
}


void Enemy::getHeal(double heal)
{
	currentHealth += heal;
}


void Enemy::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else
		Distance = MaxDistance;
}

int Enemy::GetDistance() const
{
	return Distance;
}

void Enemy::setType(ENMY_TYPE E)
{
	type = E;
}

void Enemy::setReloading()
{
	timeToEndReload = reloadPeriod;
}

void Enemy::setKilledTime(int time)
{
	killedTime = time;
}

int Enemy::getType() const
{
	return type;
}

int Enemy::getHealth() const
{
	return currentHealth;
}

int Enemy::getReloading() const
{
	return timeToEndReload;
}

int Enemy::getSpeed() const
{
	if (currentFrost >= frostThreshold)
		return 0.7 * speed;
	else
		return speed;
}

bool Enemy::isFrosted() const
{
	if (GetStatus() == FRST)
		return true;
	else
		return false;
}

int Enemy::getfirstShotTime() const
{
	return firstShotTime;
}



int Enemy::GetArrvTime() const
{
	return ArrvTime;
}

void Enemy::decrementReload()
{
	if (timeToEndReload == 0)
		return;
	timeToEndReload--;
}

void Enemy::meltIce()
{
	currentFrost -= 0.1 * (currentHealth + power);
}

Enemy::~Enemy()
{
}
