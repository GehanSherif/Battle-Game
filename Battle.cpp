#include "Battle.h"
#include <time.h>
#include <fstream>
#include <sstream>
#include "Enemies\Fighter.h"
#include "Enemies\Freezer.h"
#include "Enemies/Healer.h"
#include <string>
using namespace std;

Battle::Battle()
{	
	EnemyCount = 0;
	KilledCount = 0;
	ActiveCount = 0;
	FrostedCount = 0;
	DemoListCount =	0;
	CurrentTimeStep = 0;
	FighterCount = 0;
	FreezerCount = 0;
	HealerCount = 0;
	pGUI = NULL;
}

void Battle::AddtoDemoList(Enemy* Ptr)
{
	DemoList[DemoListCount++] = Ptr;

	// Note that this function doesn't allocate any enemy objects
	// It just enqueue a pointer that is already allocated into the queue
}


Castle * Battle::GetCastle()
{
	return &BCastle;
}


void Battle::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		break;
	case MODE_STEP:
		break;
	case MODE_SLNT:
		break;
	case MODE_DEMO:
		Just_A_Demo();
	case MODE_SIMULATOR:
		Simulator();
	}
	delete pGUI;
	
}


//This is just a demo function for project introductory phase
//It should be removed in phases 1&2
void Battle::Just_A_Demo()
{	
	
	pGUI->PrintMessage("Just a Demo. Enter Enemies Count(next phases should read I/P filename):");
	EnemyCount = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer

	pGUI->PrintMessage("Generating Enemies randomly... In next phases, Enemies should be loaded from a file...CLICK to continue");
	pGUI->waitForClick();

	CurrentTimeStep = 0;
	//
	// THIS IS JUST A DEMO Function
	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2
	//
	 
	srand(time(NULL));
	int Enemy_id = 0;
	int ArrivalTime=1;
	Enemy* pE= NULL;
	//Create Random enemies and add them all to inactive queue
	for(int i=0; i<EnemyCount; i++)
	{			
		ArrivalTime += (rand()%3);	//Randomize arrival time
		pE = new Enemy(++Enemy_id,ArrivalTime);
		pE->SetStatus( INAC); //initiall all enemies are inactive
		Q_Inactive.enqueue(pE);		//Add created enemy to inactive Queue
	}	

	AddAllListsToDrawingList();
	pGUI->UpdateInterface(CurrentTimeStep);	//upadte interface to show the initial case where all enemies are still inactive

	pGUI->waitForClick();
	
	while( KilledCount < EnemyCount )	//as long as some enemies are alive (should be updated in next phases)
	{
		CurrentTimeStep++;
		ActivateEnemies();

		Demo_UpdateEnemies();	//Randomly update enemies distance/status (for demo purposes only)

		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
		pGUI->UpdateInterface(CurrentTimeStep);
		Sleep(250);
	}		
}

void Battle::Simulator()
{
	ImportInputFile(); //Calling input file
	AddAllListsToDrawingList();
	pGUI->UpdateInterface(CurrentTimeStep);	//upadte interface to show the initial case where all enemies are still inactive

	pGUI->waitForClick();

	while (KilledCount < EnemyCount)	//as long as some enemies are alive (should be updated in next phases)
	{
		CurrentTimeStep++;
		ActivateEnemiesSimulator();

		RunSimulation_Once();	//Update Simulation

		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
		pGUI->UpdateInterface(CurrentTimeStep);
		Sleep(250);
	}

}

//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
void Battle::AddAllListsToDrawingList()
{	
	//Add inactive queue to drawing list
	int InactiveCount;
	int ActiveFreezerCount;
	int ActiveHealerCount;

	//Inactive
	Enemy* const * EnemyList = Q_Inactive.toArray(InactiveCount);
	for(int i=0; i<InactiveCount; i++)
		pGUI->AddToDrawingList(EnemyList[i]);

	//Freezers
	Freezer* const* FreezerList = Q_ActiveF.toArray(ActiveFreezerCount);
	for (int i = 0; i < ActiveFreezerCount; i++)
		pGUI->AddToDrawingList(FreezerList[i]);
	
	//Healers
	ActiveHealerCount = S_ActiveH.getCount();
	Healer** HealerList = new Healer*[ActiveHealerCount];
	HealerList = S_ActiveH.toArray();
	for (int i = 0; i < ActiveHealerCount; i++)
		pGUI->AddToDrawingList(HealerList[i]);

	//Frosted
	Enemy* const* FrostedList = Q_Frosted.toArray(FrostedCount);
	for (int i = 0; i < FrostedCount; i++)
		pGUI->AddToDrawingList(FrostedList[i]);

	//Killed
	Enemy* const* KilledList = Q_Killed.toArray(KilledCount);
	for (int i = 0; i < KilledCount; i++)
		pGUI->AddToDrawingList(KilledList[i]);




	//Add other lists to drawing list
	//TO DO
	//In next phases, you should add enemies from different lists to the drawing list
	//For the sake of demo, we will use DemoList
	for(int i=0; i<DemoListCount; i++)
		pGUI->AddToDrawingList(DemoList[i]);
}

//check the inactive list and activate all enemies that has arrived
void Battle::ActivateEnemies()
{
	Enemy *pE;
	while( Q_Inactive.peekFront(pE) )	//as long as there are more inactive enemies
	{
		if(pE->GetArrvTime() > CurrentTimeStep )	//no more arrivals at current time
			return;
				
		Q_Inactive.dequeue(pE);	//remove enemy from the queue
		pE->SetStatus(ACTV);	//make status active
		AddtoDemoList(pE);		//move it to demo list (for demo purposes)
	}
}

void Battle::ActivateEnemiesSimulator()
{
	Enemy* pE;
	while (Q_Inactive.peekFront(pE))	//as long as there are more inactive enemies
	{
		if (pE->GetArrvTime() > CurrentTimeStep)	//no more arrivals at current time
			return;

		Q_Inactive.dequeue(pE);	//remove enemy from the queue
		pE->SetStatus(ACTV);	//make status active
		if(pE->getType() == 0)
		{ }
		else if (pE->getType() == 1)
		{
			Healer* pH = dynamic_cast<Healer*>(pE);
			S_ActiveH.push(pH);
		}
		else if (pE->getType() == 2)
		{
			Freezer* pF = dynamic_cast<Freezer*>(pE);
			Q_ActiveF.enqueue(pF);
		}
	}
}


//Randomly update enemies distance/status (for demo purposes)
void Battle::Demo_UpdateEnemies()
{
	Enemy* pE;
	int Prop;
	//Freeze, activate, and kill propablities (for sake of demo)
	int FreezProp = 5, ActvProp = 10, KillProp = 1;	
	srand(time(0));
	for(int i=0; i<DemoListCount; i++)
	{
		pE = DemoList[i];
		switch(pE->GetStatus())
		{
		case ACTV:
			pE->DecrementDist();	//move the enemy towards the castle
			Prop = rand()%100;
			if(Prop < FreezProp)		//with Freeze propablity, change some active enemies to be frosted
			{
				pE->SetStatus(FRST); 
				ActiveCount--;
				FrostedCount++;
			}
			else	if (Prop < (FreezProp+KillProp) )	//with kill propablity, kill some active enemies
					{
						pE->SetStatus(KILD);	
						ActiveCount--;
						KilledCount++;
					}
			
			break;
		case FRST:
			Prop = rand()%100;
			if(Prop < ActvProp)			//with activation propablity, change restore some frosted enemies to be active again
			{
				pE->SetStatus(ACTV);
				ActiveCount++;
				FrostedCount--;
			}

			else	if (Prop < (ActvProp+KillProp) )			//with kill propablity, kill some frosted enemies
					{
						pE->SetStatus(KILD);	
						FrostedCount--;
						KilledCount++;
					}

			break;
		}
	}
}

void Battle::ImportInputFile()
{
	ifstream fin;
	stringstream stream;
	fin.open("InputFile.txt");
	string alldata, CH, N, CP, M, ID, TYP, AT, H, POW, RLD, SPD;
	

	//Getting first line (Castle)
	getline(fin, alldata);
	stream.str(alldata);
	getline(stream, CH, ' ');
	getline(stream, N,  ' ');
	getline(stream, CP, ' ');
	BCastle.SetHealth(stoi(CH));
	BCastle.SetcasltePower(stoi(CP));
	BCastle.SetmatAttack(stoi(N));


	//Getting second line (Num of Enemies)
	getline(fin, alldata);
	stream.str(alldata);
	getline(stream, M, ' ');
	EnemyCount = stoi(M);

	//Getting the rest of lines (Enemies)
	while (getline(fin, alldata))
	{
		Enemy* enemy;

		stream.str(alldata);
		getline(stream, ID,  ' ');
		getline(stream, TYP, ' ');
		getline(stream, AT,  ' ');
		getline(stream, H,   ' ');
		getline(stream, POW, ' ');
		getline(stream, RLD, ' ');
		getline(stream, SPD, ' ');

		if (TYP == "0")
		{
			enemy = new Fighter(stoi(ID), stoi(AT), stoi(H), stoi(POW), stoi(SPD), stoi(RLD));
			enemy->setType(0);
			FighterCount++;
		}
		else if (TYP == "1")
		{
			enemy = new Enemy(stoi(ID), stoi(AT), stoi(H), stoi(POW), stoi(SPD), stoi(RLD));
			enemy->setType(1);
			HealerCount++;
		}
		else
		{
			enemy = new Enemy(stoi(ID), stoi(AT), stoi(H), stoi(POW), stoi(SPD), stoi(RLD));
			enemy->setType(2);
			FreezerCount++;
		}
		EnemyCount++;
		Q_Inactive.enqueue(enemy);
	}
}

void Battle::RunSimulation_Once()
{
	Enemy* pE;
	Healer* pH;
	Freezer* pF;
	int freezedFightersNo = 0, freezedHealersNo = 0, freezedFreezersNo = 0, killedActiveEnemiesNo = 0, defrostedEnemies = 0, killedFrostedEnemies = 0;
	int cH = S_ActiveH.getCount();
	int cF = Q_ActiveF.getC();

	//For each enemy type, pick two active enemies that are on top of list and
	//freeze them.

	for (int i = 0; i < 2 ; i++)
	{
		if (!(Q_ActiveF.isEmpty()))
		{
			Q_ActiveF.dequeue(pF);
			FreezeEnemy(pF);
			Q_Frosted.enqueue(pF);
			freezedFreezersNo++;
		}
		if (!(S_ActiveH.isEmpty()))
		{
			S_ActiveH.pop(pH);
			FreezeEnemy(pH);
			Q_Frosted.enqueue(pH);
			freezedHealersNo++;
		}
	}

	//iv. Pick two previously frosted enemies and return them back to their normal
	//status.

	for (int i = 0; i < 2; i++)
	{
		if (!(Q_Frosted.isEmpty()))
		{
			Q_Frosted.dequeue(pE);
			//Healer
			if (dynamic_cast<Healer*>(pE) != nullptr)
			{
				pH = dynamic_cast<Healer*>(pE);
				DefrostEnemy(pH);
				S_ActiveH.push(pH);
			}
			//Freezer
			else if (dynamic_cast<Freezer*>(pE) != nullptr)
			{
				pF = dynamic_cast<Freezer*>(pE);
				DefrostEnemy(pF);
				Q_ActiveF.enqueue(pF);
			}
		}
	}

	//v. Kill one active enemy and one frosted enemy.
	//1- Active Enemy
	int x = rand() % 3;
	if (x == 0) //kill Active Fighter
	{

	}
	else if (x == 1) //kill active freezer
	{
		if (!(Q_ActiveF.isEmpty()))
		{
			Q_ActiveF.dequeue(pF);
			KillEnemy(pF);
			Q_Killed.enqueue(pF);
		}
	}
	else if (x == 2) //kill active Healer
	{
		if (!(S_ActiveH.isEmpty()))
		{
			S_ActiveH.pop(pH);
			KillEnemy(pH);
			Q_Killed.enqueue(pH);
		}
	}
	//2- Frosted Enemy
	if (!(Q_Frosted.isEmpty()))
	{
		Q_Frosted.dequeue(pE);
		KillEnemy(pE);
		Q_Killed.enqueue(pE);
	}
	


}

void Battle::FreezeEnemy(Enemy* pE)
{
	pE->SetStatus(FRST);
	ActiveCount--;
	FrostedCount++;
}

void Battle::DefrostEnemy(Enemy* pE)
{
	pE->SetStatus(ACTV);
	ActiveCount++;
	FrostedCount--;
}

void Battle::KillEnemy(Enemy* pE)
{
	if (pE->GetStatus() == FRST)
	{
		pE->SetStatus(KILD);
		FrostedCount--;
		KilledCount++;
	}
	else if (pE->GetStatus() == ACTV)
	{
		pE->SetStatus(KILD);
		ActiveCount--;
		KilledCount++;
	}
}