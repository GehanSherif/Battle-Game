#include "Freezer.h"
#include <math.h>

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
            Distance -= 0.5 * getSpeed();
        }
        else
        {
            Distance -= getSpeed();
        }
        if (Distance < MinDistance)
            Distance = MinDistance;
    }
}

void Freezer::frostCastle(Castle* castle)
{
    if (getReloading() != 0) //must equal zero
        return;

    double k;
    if (currentHealth < 0.5 * originalHealth)
        k = 0.5;
    else
        k = 1.0;
    double frost = (k * pow(power, 2)) / Distance;
    castle->receiveFrost(frost);
}
