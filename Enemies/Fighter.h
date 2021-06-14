#pragma once
#include "Enemy.h"
#include "../Castle/Castle.h"

class Fighter :
    public Enemy
{
private:
                    
public:
    Fighter(int id, int arrTime, int enemyHealth, int enemyPower, int enemySpeed, int relPeriod);

    void Move() override;
    void attackCastle(Castle*);
    double getPriority() const;
};

