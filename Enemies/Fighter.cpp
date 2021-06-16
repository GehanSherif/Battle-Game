#include "Fighter.h"
#include "../Battle.h"
#include "../SuperSolider.h"


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

void Fighter::attackCastle(Castle* castle)
{
    if (getReloading() != 0) //must equal zero
        return;

    if (firstShotTime == 0)
        firstShotTime = Battle::getCurrentTimeStep();

    double k;
    if (currentHealth < 0.5 * originalHealth)
        k = 0.5;
    else
        k = 1.0;


    if (castle->getPtrSS()->isEmpty())
    {
        //No SS so attack the caslte itself


        double damage = (k * power) / Distance;
        castle->receiveDamage(damage);
    }
    else //There are SSs so attack them
    {
        SuperSolider* ss = nullptr;
        castle->getPtrSS()->dequeue(ss);
        double damage = (k * power) / 2;
        ss->receiveDamage(damage);
        if (ss->isDead())
            delete ss;
        else
            castle->getPtrSS()->enqueue(ss);
    }


}

//This function returns the priority of a fighter to be attacked by the castle and 
//is based on distance, power, health, status(active or frosted), remaining time steps for an enemy to end reload period.
double Fighter::getPriority() const
{
    int k;
    if (isFrosted())
        k = 0.5;
    else
        k = 1;
    
    return (power * currentHealth * k) / (Distance * (getReloading()+1));
}
