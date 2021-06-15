#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

class GUI;
// Enemy is the base class of each type of enemy
// Enemy should be an abstract class in next phases
class Enemy
{

protected:
	const int ID;         //Each enemy has a unique ID (sequence number)
	const int ArrvTime;	//arrival time (time it starts to join battle)

	ENMY_STATUS status;	    //status of the enemy (inactive, inactive, frosted, killed)

	int Distance;	//Horizontal distance between enemy & the tower of its region;Always positive (ranges from 2 to 60)

	const double originalHealth;	//Enemy health
	const double frostThreshold;

	double currentHealth;
	double currentFrost;
	double speed;	//Enemy speed
	double power;	//Enemy Power


	int reloadPeriod;	//Time an Enemy takes to reload
	int firstShotTime;	//Time at which an Enemy was first shot by the castle
	int killedTime;		//Time at which an Enemy was killed

	int timeToEndReload;
	ENMY_TYPE type;

public:
	Enemy(int id, int arrTime, int enemyHealth, int enemyPower, int enemySpeed, int ReloadPeriod);


	//getters
	int GetID() const;
	int GetArrvTime() const;
	ENMY_STATUS GetStatus() const;
	int GetDistance() const;
	int getType() const;
	int getHealth() const;
	int getReloading() const;
	int getSpeed() const;
	bool isFrosted() const;
	bool isDead() const;

	//setters
	void SetStatus(ENMY_STATUS);
	void SetDistance(int);
	void setType(ENMY_TYPE);
	void setReloading();
	void setKilledTime(int time);

	//operations
	bool recieveDamage(double damage); //returns true if enemey is dead after taking the damage
	bool recieveFrost(double frost); //returns true in case enemy is frosted
	void getHeal(double heal);
	void decrementReload();
	void meltIce();

	//virtual operations
	virtual void Move() = 0;	//All enemies can move

	//destructor
	virtual ~Enemy();

};

