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
	ActiveFighter = 0;
	ActiveHealer = 0;
	ActiveFreezer = 0;
	FrostedFighter = 0;
	FrostedHealer = 0;
	FrostedFreezer = 0;
	KilledFighter = 0;
	KilledFreezer = 0;
	KilledHealer = 0;
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
	PROG_MODE mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		break;
	case MODE_STEP:
		break;
	case MODE_SLNT:
		break;
	case MODE_DEMO:

	case MODE_SIMULATOR:
		Simulator();
	}
	delete pGUI;
	
	
}


//This is just a demo function for project introductory phase
//It should be removed in phases 1&2
//void Battle::Just_A_Demo()
//{	
//	
//	pGUI->PrintMessage("Just a Demo. Enter Enemies Count(next phases should read I/P filename):");
//	EnemyCount = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer
//
//	pGUI->PrintMessage("Generating Enemies randomly... In next phases, Enemies should be loaded from a file...CLICK to continue");
//	pGUI->waitForClick();
//
//	CurrentTimeStep = 0;
//	//
//	// THIS IS JUST A DEMO Function
//	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2
//	//
//	 
//	srand(time(NULL));
//	int Enemy_id = 0;
//	int ArrivalTime=1;
//	Enemy* pE= NULL;
//	//Create Random enemies and add them all to inactive queue
//	for(int i=0; i<EnemyCount; i++)
//	{			
//		ArrivalTime += (rand()%3);	//Randomize arrival time
//		pE = new Enemy(++Enemy_id,ArrivalTime);
//		pE->SetStatus( INAC); //initiall all enemies are inactive
//		Q_Inactive.enqueue(pE);		//Add created enemy to inactive Queue
//	}	
//
//	AddAllListsToDrawingList();
//	//pGUI->UpdateInterface(CurrentTimeStep);	//upadte interface to show the initial case where all enemies are still inactive
//
//	pGUI->waitForClick();
//	
//	while( KilledCount < EnemyCount )	//as long as some enemies are alive (should be updated in next phases)
//	{
//		CurrentTimeStep++;
//		ActivateEnemies();
//
//		Demo_UpdateEnemies();	//Randomly update enemies distance/status (for demo purposes only)
//
//		pGUI->ResetDrawingList();
//		AddAllListsToDrawingList();
//		//pGUI->UpdateInterface(CurrentTimeStep);
//		Sleep(250);
//	}		
//}

void Battle::Simulator()
{
	ImportInputFile(); //Calling input file
	AddAllListsToDrawingList();
	pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetHealth(), BCastle.IsFrosted(), KilledCount,
		ActiveCount, FrostedCount, ActiveFighter, ActiveFreezer, ActiveHealer,
	FrostedFighter, FrostedHealer, FrostedFreezer,
	 KilledFighter, KilledFreezer, KilledHealer);	//upadte interface to show the initial case where all enemies are still inactive

	pGUI->waitForClick();

	while (KilledCount < EnemyCount)	//as long as some enemies are alive (should be updated in next phases)
	{
		CurrentTimeStep++;
		ActivateEnemiesSimulator();
		if (CurrentTimeStep != 1)
		{
			RunSimulation_Once();	//Update Simulation
		}
		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
		pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetHealth(), BCastle.IsFrosted(), KilledCount,
			ActiveCount, FrostedCount, ActiveFighter, ActiveFreezer, ActiveHealer,
			FrostedFighter, FrostedHealer, FrostedFreezer,
			KilledFighter, KilledFreezer, KilledHealer);
		pGUI->waitForClick();
		
	}

}

//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
void Battle::AddAllListsToDrawingList()
{	
	//Add inactive queue to drawing list
	int InactiveCount;
	int ActiveFreezerCount;
	int ActiveHealerCount;
	int ActiveFighterCount;

	//Inactive
	Enemy* const * EnemyList = Q_Inactive.toArray(InactiveCount);
	for(int i=0; i<InactiveCount; i++)
		pGUI->AddToDrawingList(EnemyList[i]);

	//Fighters
	Fighter* const* FighterList = Q_ActiveFighter.toArray(ActiveFighterCount);
	for (int i = 0; i < ActiveFighterCount; i++)
		pGUI->AddToDrawingList(FighterList[i]);

	//Freezers
	Freezer* const* FreezerList = Q_ActiveFreezer.toArray(ActiveFreezerCount);
	for (int i = 0; i < ActiveFreezerCount; i++)
		pGUI->AddToDrawingList(FreezerList[i]);

	//Healers
	Healer* const* HealerList = S_ActiveHealer.toArray(ActiveHealerCount);
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
		//AddtoDemoList(pE);		//move it to demo list (for demo purposes)
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
		ActiveCount++;
		pE->SetStatus(ACTV);	//make status active
		if(pE->getType() == 0)
		{ 
			ActiveFighter++;
			Fighter* pFighter = dynamic_cast<Fighter*>(pE);
			Q_ActiveFighter.insert(pFighter, pFighter->getPriority());
		}
		else if (pE->getType() == 1)
		{
			ActiveHealer++;
			Healer* pH = dynamic_cast<Healer*>(pE);
			S_ActiveHealer.push(pH);
		}
		else if (pE->getType() == 2)
		{
			ActiveFreezer++;
			Freezer* pF = dynamic_cast<Freezer*>(pE);
			Q_ActiveFreezer.enqueue(pF);
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
	BCastle.setFreezingThreshold(BCastle.GetHealth()*0.33);


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
			FighterCount++;
		}
		else if (TYP == "1")
		{
			enemy = new Healer(stoi(ID), stoi(AT), stoi(H), stoi(POW), stoi(SPD), stoi(RLD));
			HealerCount++;
		}
		else
		{
			enemy = new Freezer(stoi(ID), stoi(AT), stoi(H), stoi(POW), stoi(SPD), stoi(RLD));
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
	Freezer* pFreezer;
	Fighter* pFighter;
	int freezedFightersNo = 0, freezedHealersNo = 0, freezedFreezersNo = 0, killedActiveEnemiesNo = 0, defrostedEnemies = 0, killedFrostedEnemies = 0;
	int cH = S_ActiveHealer.getCount();
	int cFreezer = Q_ActiveFreezer.getC();
	int cFighter = Q_ActiveFighter.size();

	//ii. Move all active enemies of all types according to their speeds and movement
	//pattern.


	//1- Moving Fighter
	PriorityQueue<Fighter*> TempActiveFighterPQ(ActiveFighter);
	for (int i = 0; i < ActiveFighter; i++)
	{
		Q_ActiveFighter.dequeueMax(pFighter);
		if(pFighter->GetStatus() == ACTV)
		pFighter->DecrementDist();
		TempActiveFighterPQ.insert(pFighter, pFighter->getPriority());
	}
	for (int i = 0; i < ActiveFighter; i++)
	{
		TempActiveFighterPQ.dequeueMax(pFighter);
		Q_ActiveFighter.insert(pFighter, pFighter->getPriority());
	}

	//2- Moving Freezer
	Queue<Freezer*> TempActiveFreezerQueue;
	for (int i = 0; i < ActiveFreezer; i++)
	{
		Q_ActiveFreezer.dequeue(pFreezer);
		if(pFreezer->GetStatus() == ACTV)
		pFreezer->DecrementDist();
		TempActiveFreezerQueue.enqueue(pFreezer);
	}
	for (int i = 0; i < ActiveFreezer; i++)
	{
		TempActiveFreezerQueue.dequeue(pFreezer);
		Q_ActiveFreezer.enqueue(pFreezer);
	}


	//3- Moving Healer
	ArrayStack<Healer*> TempActiveHealerStack;
	for (int i = 0; i < ActiveHealer; i++)
	{
		S_ActiveHealer.pop(pH);
		if (pH->GetStatus() == ACTV)
		pH->DecrementDist();
		TempActiveHealerStack.push(pH);
	}
	for (int i = 0; i < ActiveHealer; i++)
	{
		TempActiveHealerStack.pop(pH);
		S_ActiveHealer.push(pH);
	}

	//iii. For each enemy type, pick two active enemies that are on top of list and
	//freeze them.

	for (int i = 0; i < 2 ; i++)
	{
		if (!(Q_ActiveFighter.isEmpty()))
		{
			Q_ActiveFighter.dequeueMax(pFighter);
			FreezeEnemy(pFighter);
			Q_Frosted.enqueue(pFighter);
			freezedFightersNo++;
		}
		if (!(Q_ActiveFreezer.isEmpty()))
		{
			Q_ActiveFreezer.dequeue(pFreezer);
			FreezeEnemy(pFreezer);
			Q_Frosted.enqueue(pFreezer);
			freezedFreezersNo++;
		}
		if (!(S_ActiveHealer.isEmpty()))
		{
			S_ActiveHealer.pop(pH);
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
				S_ActiveHealer.push(pH);
			}
			//Freezer
			else if (dynamic_cast<Freezer*>(pE) != nullptr)
			{
				pFreezer = dynamic_cast<Freezer*>(pE);
				DefrostEnemy(pFreezer);
				Q_ActiveFreezer.enqueue(pFreezer);
			}
			else if (dynamic_cast<Fighter*>(pE) != nullptr)
			{
				pFighter = dynamic_cast<Fighter*>(pE);
				DefrostEnemy(pFighter);
				Q_ActiveFighter.insert(pFighter, pFighter->getPriority());
			}
		}
	}

	//v. Kill one active enemy and one frosted enemy.
	//1- Active Enemy
	int x = rand() % 3;
	if (x == 0) //kill Active Fighter
	{
		if (!(Q_ActiveFighter.isEmpty()))
		{
			Q_ActiveFighter.dequeueMax(pFighter);
			KillEnemy(pFighter);
			Q_Killed.enqueue(pFighter);
		}
	}
	else if (x == 1) //kill active freezer
	{
		if (!(Q_ActiveFreezer.isEmpty()))
		{
			Q_ActiveFreezer.dequeue(pFreezer);
			KillEnemy(pFreezer);
			Q_Killed.enqueue(pFreezer);
		}
	}
	else if (x == 2) //kill active Healer
	{
		if (!(S_ActiveHealer.isEmpty()))
		{
			S_ActiveHealer.pop(pH);
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
	if (dynamic_cast<Freezer*>(pE))
	{
		ActiveFreezer--;
		FrostedFreezer++;
	}
	else if (dynamic_cast<Healer*>(pE))
	{
		ActiveHealer--;
		FrostedHealer++;
	}
	else if (dynamic_cast<Fighter*>(pE))
	{
		ActiveFighter--;
		FrostedFighter++;
	}
}

void Battle::DefrostEnemy(Enemy* pE)
{
	pE->SetStatus(ACTV);
	ActiveCount++;
	FrostedCount--;
	if (dynamic_cast<Freezer*>(pE))
	{
		ActiveFreezer++;
		FrostedFreezer--;
	}
	else if (dynamic_cast<Healer*>(pE))
	{
		ActiveHealer++;
		FrostedHealer--;
	}
	else if (dynamic_cast<Fighter*>(pE))
	{
		ActiveFighter++;
		FrostedFighter--;
	}
}

void Battle::KillEnemy(Enemy* pE)
{
	if (pE->GetStatus() == FRST)
	{
		FrostedCount--;
		KilledCount++;
	}
	else if (pE->GetStatus() == ACTV)
	{
		ActiveCount--;
		KilledCount++;
	}

	if (dynamic_cast<Freezer*>(pE))
	{
		if (pE->GetStatus() == FRST)
		{
			FrostedFreezer--;
			KilledFreezer++;
		}
		else
		{
			ActiveFreezer--;
			KilledFreezer++;
		}
	}
	else if (dynamic_cast<Healer*>(pE))
	{
		if (pE->GetStatus() == FRST)
		{
			FrostedHealer--;
			KilledHealer++;
		}
		else
		{
			ActiveHealer--;
			KilledHealer++;
		}
	}
	else if (dynamic_cast<Fighter*>(pE))
	{
		if (pE->GetStatus() == FRST)
		{
			FrostedFighter--;
			KilledFighter++;
		}
		else
		{
			ActiveFighter--;
			KilledFighter++;
		}
	}
	pE->SetStatus(KILD);
}

bool Battle::runTimeStep()
{
	//enemies walking, enemies acting, enemies reloading, enemy picking criteria



	//castle attacking

	return false;
}
