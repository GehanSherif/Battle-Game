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

	double health;	//Enemy health
	double speed;	//Enemy speed
	double power;	//Enemy Power

	int reloadPeriod;	//Time an Enemy takes to reload
	int firstShotTime;	//Time at which an Enemy was first shot by the castle
	int killedTime;		//Time at which an Enemy was killed

	bool Freezed;	//1 if an enemy is freezed and 0 otherwise
	int type;

public:
	Enemy(int id, int arrTime, int d = MaxDistance);
	Enemy(int id, int arrTime, int enemyHealth, int enemyPower, int enemySpeed, int ReloadPeriod, int d = MaxDistance);

	int GetID() const;

	int GetArrvTime() const;

	ENMY_STATUS GetStatus() const;
	void SetStatus(ENMY_STATUS);
	
	void SetDistance(int );
	int GetDistance() const;
	void setType(int);
	int getType();
	void DecrementDist();
	void DecrementDist(int);
	bool isDead() const;



	virtual ~Enemy();

	// Virtual Functions: ----------------

	//virtual void Move() = 0;	//All enemies can move
	//virtual void Act() = 0;	//Acting means fighting or healing

	//
	// TODO: Add More Member Functions As Needed
	//

};

