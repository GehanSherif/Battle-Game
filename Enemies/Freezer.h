#pragma once
#include "Enemy.h"
#include "../Castle/Castle.h"
class Freezer :
    public Enemy
{
private:


public:
    Freezer(int id, int arrTime, int enemyHealth, int enemyPower, int enemySpeed, int relPeriod);

    void Move() override;
    void frostCastle(Castle*);

};

