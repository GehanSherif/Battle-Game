#include "Fighter.h"

Fighter::Fighter(int id, int arrTime, int enemyHealth, int enemyPower, int enemySpeed, int relPeriod, int d)
    :Enemy(id, arrTime, enemyHealth, enemyPower, enemySpeed, relPeriod, d)
{
}


//This function returns the priority of a fighter to be attacked by the castle and 
//is based on distance, power, health, status(active or frosted), remaining time steps for an enemy to end reload period.
double Fighter::getPriority()
{
    return 0.0;
}
