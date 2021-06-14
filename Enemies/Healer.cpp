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
			Distance = MaxDistance - (speed + Distance - MaxDistance);
		}
		else
		{
			Distance += speed;
		}
	}
}

