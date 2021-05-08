#pragma once
#include "Enemy.h"
class Fighter :
    public Enemy
{
private:
                    
public:
    Fighter(int id, int arrTime, int enemyHealth, int enemyPower, int enemySpeed, int relPeriod, int d = MaxDistance);
    double getPriority();

};

