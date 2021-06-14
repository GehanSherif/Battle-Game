#include "Freezer.h"

Freezer::Freezer(int id, int arrTime, int enemyHealth, int enemyPower, int enemySpeed, int relPeriod)
	:Enemy(id, arrTime, enemyHealth, enemyPower, enemySpeed, relPeriod)
{
	setType(FREEZER);
}

void Freezer::Move()
{
    if (Distance <= MinDistance)
        return;
    else
    {
        if (currentHealth < 0.5 * originalHealth)
        {
            Distance -= 0.5 * speed;
        }
        else
        {
            Distance -= speed;
        }
        if (Distance < MinDistance)
            Distance = MinDistance;
    }
}
