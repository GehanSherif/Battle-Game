#include "Healer.h"

Healer::Healer(int id, int arrTime, int enemyHealth, int enemyPower, int enemySpeed, int relPeriod)
	:Enemy(id, arrTime, enemyHealth, enemyPower, enemySpeed, relPeriod)
{
	setType(HEALER);
	movingDirection = 0;
}

void Healer::Move()
{
	if (movingDirection == 0) //moving towards castle
	{
		if (Distance - MinDistance < speed)
		{
			Distance = speed - Distance + MinDistance;
			movingDirection = 1;
		}
		else
		{
			Distance -= speed;
		}
	}
	else
	{
		if (MaxDistance - Distance < speed)
		{
			Distance = MaxDistance - (speed - Distance);
		}
		else
		{
			Distance += speed;
		}
	}
}

void Healer::healEnemy(Enemy* enemy)
{
	int k;
	int diff = abs(enemy->GetDistance() - Distance);
	if (diff == 0)
	{
		k = 1;
	}
	else if (diff == 1)
	{
		k = 0.5;
	}
	else if (diff == 2)
	{
		k = 0.25;
	}
	else
	{
		return;
	}
	double heal = 1.0 * k * power;
	enemy->getHeal(heal);
}