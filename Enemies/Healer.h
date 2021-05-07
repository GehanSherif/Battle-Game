#pragma once
#include "Enemy.h"
class Healer :
    public Enemy
{
private:

public:
    Healer(int id, int arrTime, int enemyHealth, int enemyPower, int enemySpeed, int relPeriod, int d = MaxDistance);
};

