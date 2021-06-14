#include "Fighter.h"


Fighter::Fighter(int id, int arrTime, int enemyHealth, int enemyPower, int enemySpeed, int relPeriod)
    :Enemy(id, arrTime, enemyHealth, enemyPower, enemySpeed, relPeriod)
{
    setType(FIGHTER);
}



void Fighter::Move()
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

//This function returns the priority of a fighter to be attacked by the castle and 
//is based on distance, power, health, status(active or frosted), remaining time steps for an enemy to end reload period.
double Fighter::getPriority()
{
    return 0.0;
}
