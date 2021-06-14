#pragma once
#include "Enemy.h"
#include "../Castle/Castle.h"
class Healer :
    public Enemy
{
private:
    bool movingDirection; //0 for towards the castle and 1 away from
public:
    Healer(int id, int arrTime, int enemyHealth, int enemyPower, int enemySpeed, int relPeriod);

    void Move() override;
    void healEnemy(Enemy*);
};

