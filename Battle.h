#pragma once

#include "Enemies\Enemy.h"
#include "Enemies\Freezer.h"
#include "Enemies\Healer.h"
#include "Enemies\Fighter.h"
#include "ArrayStack.h";
#include "Castle\Castle.h"
#include "Generic_DS\Queue.h"
#include "GUI\GUI.h"
#include "PriorityQueue.h"

// it is the controller of the project
class Battle
{
private:
	GUI* pGUI;
	Castle BCastle;
	int EnemyCount;	//the actual number of enemies in the game
	int FighterCount, FreezerCount, HealerCount;
	int ActiveCount, FrostedCount, KilledCount;	//no. of enemies (Active, Frosted, killed so far)
	int ActiveFighter, ActiveFreezer, ActiveHealer;
	int FrostedFighter, FrostedHealer, FrostedFreezer;
	int KilledFighter, KilledFreezer, KilledHealer;
	static int CurrentTimeStep;
	//Enemy * BEnemiesForDraw[MaxEnemyCount]; // This Array of Pointers is used for drawing elements in the GUI
								  			// No matter what list type you are using to hold enemies, 
											// you must pass the enemies to the GUI function as an array of enemy pointers. 
											// At every time step, you should update those pointers 
											// to point to the current active enemies 
											// then pass the pointers list to the GUI function

	Queue<Enemy*> Q_Inactive;					//Queue of inactive enemies
	Queue<Freezer*> Q_ActiveFreezer;			//Queue of Active Freezers
	PriorityQueue<Fighter*> Q_ActiveFighter;		//Priority queue of active Fighters
	ArrayStack<Healer*> S_ActiveHealer;			//Stack of Active Healers
	PriorityQueue<Enemy*> Q_Frosted;			//Queue of Frosted Enemies
	Queue<Enemy*> Q_Killed;						//Queue of killed Enemies
	

	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	//Queue for all enemies in the battle
	int DemoListCount;
	Enemy* DemoList[MaxEnemyCount];	//Important: This is just for demo

public:
	
	Battle();
	void AddAllListsToDrawingList(); //Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
	Castle * GetCastle();
	void RunSimulation();
	void ActivateEnemies();		//check the inactive list and activate all enemies that has arrived
	void ActivateEnemiesSimulator();


	void AddtoDemoList(Enemy* Ptr); //Add Enemy to the demo queue of enemies (for demo purposes only)
	//void Simulator();
	void Demo_UpdateEnemies();	//Randomly update enemies distance/status (for demo purposes)

	void ImportInputFile();

	static int getCurrentTimeStep();

	void RunSimulation_Once();
	bool runTimeStep();
};

