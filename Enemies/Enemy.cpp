#include "Enemy.h"


Enemy::Enemy(int id, int arrTime, int d):ID(id),ArrvTime(arrTime)
{
	SetDistance(d);
}

Enemy::Enemy(int id, int arrTime, int enemyHealth, int enemyPower, int enemySpeed, int relPeriod, int d)
	: ID(id), ArrvTime(arrTime), health(enemyHealth), power(enemyPower), speed(enemySpeed), reloadPeriod(relPeriod)
{
	SetDistance(d);
	SetStatus(INAC);

}

Enemy::~Enemy()
{
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


void Enemy::DecrementDist()
{
	if (Distance > MinDistance)
		Distance = Distance - speed;
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

void Enemy::setType(int E)
{
	type = E;
}

int Enemy::getType()
{
	return type;
}



int Enemy::GetArrvTime() const
{
	return ArrvTime;
}
