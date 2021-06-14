#include "Enemy.h"



Enemy::Enemy(int id, int arrTime, int enemyHealth, int enemyPower, int enemySpeed, int relPeriod)
	: ID(id), ArrvTime(arrTime), originalHealth(enemyHealth), power(enemyPower), speed(enemySpeed), reloadPeriod(relPeriod)
{
	SetStatus(INAC);
	
	Distance = MaxDistance;
	Freezed = false;
}

int Enemy::GetID() const
{
	return ID;
}

void Enemy::setID(int ID)
{
	this->ID = ID;
}

void Enemy::setArrvTime(int ATime)
{
	ArrvTime = ATime;
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
		return true;
	}
	else
		return false;
}

bool Enemy::isDead() const
{
	if (currentHealth <= 0)
		return true;
	else
		return false;
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

int Enemy::getType() const
{
	return type;
}

int Enemy::getHealth() const
{
	return currentHealth;
}



int Enemy::GetArrvTime() const
{
	return ArrvTime;
}
