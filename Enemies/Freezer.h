#pragma once
#include "Enemy.h"
class Freezer :
    public Enemy
{
public:


private:
    Freezer(int id, int arrTime, int enemyHealth, int enemyPower, int enemySpeed, int relPeriod, int d = MaxDistance);

};

