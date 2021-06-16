#include "Battle.h"
#include <time.h>
#include <fstream>
#include <sstream>
#include "Enemies\Fighter.h"
#include "Enemies\Freezer.h"
#include "Enemies/Healer.h"
#include <string>
#include <stdlib.h>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;
int Battle::CurrentTimeStep = 0;
Battle::Battle()
{	
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
	GAME_STATUS status;
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		status = InteractiveMode();
		break;
	case MODE_STEP:
		status = StepByStepMode();
		break;
	case MODE_SLNT:
		status = SilentMode();
		break;
	}
	ExportOutputFile(status);
	delete pGUI;
}


//This is just a demo function for project introductory phase
//It should be removed in phases 1&2
GAME_STATUS Battle::InteractiveMode()
{	
	int ActiveCount, ActiveFighters, ActiveHealers, ActiveFreezers, FrostedCount;
	pGUI->PrintMessage("Click to start");
	pGUI->waitForClick();
	CurrentTimeStep = 0;
	ImportInputFile();
	AddAllListsToDrawingList();
	pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetHealth(), BCastle.IsFrosted());	//upadte interface to show the initial case where all enemies are still inactive
	GAME_STATUS gameStatus= IN_PROGRESS;
	while (gameStatus == IN_PROGRESS)
	{
		pGUI->waitForClick();
		CurrentTimeStep++;
		gameStatus=runTimeStep();
		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
		ActiveFighters = Q_ActiveFighter.size() - FrostedFighter;
		ActiveHealers = S_ActiveHealer.getCount() - FrostedHealer;
		ActiveFreezers = Q_ActiveFreezer.getC() - FrostedFreezer;
		ActiveCount = ActiveFighters + ActiveHealers + ActiveFreezers;
		FrostedCount = FrostedFighter + FrostedFreezer + FrostedHealer;
		pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetHealth(), BCastle.IsFrosted(), Q_Killed.getC(),
			ActiveCount, FrostedCount, ActiveFighters, ActiveFreezers, ActiveHealers,
			FrostedFighter, FrostedHealer, FrostedFreezer, KilledFighter, KilledFreezers, KilledHealer);
	}
	pGUI->waitForClick();
	return gameStatus;
}

GAME_STATUS Battle::StepByStepMode()
{

	int ActiveCount, ActiveFighters, ActiveHealers, ActiveFreezers, FrostedCount;
	CurrentTimeStep = 0;
	ImportInputFile();
	AddAllListsToDrawingList();
	pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetHealth(), BCastle.IsFrosted());	//upadte interface to show the initial case where all enemies are still inactive
	GAME_STATUS gameStatus = IN_PROGRESS;
	while (gameStatus == IN_PROGRESS)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		CurrentTimeStep++;
		gameStatus = runTimeStep();
		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
		ActiveFighters = Q_ActiveFighter.size() - FrostedFighter;
		ActiveHealers = S_ActiveHealer.getCount() - FrostedHealer;
		ActiveFreezers = Q_ActiveFreezer.getC() - FrostedFreezer;
		ActiveCount = ActiveFighters + ActiveHealers + ActiveFreezers;
		FrostedCount = FrostedFighter + FrostedFreezer + FrostedHealer;
		pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetHealth(), BCastle.IsFrosted(), Q_Killed.getC(),
			ActiveCount, FrostedCount, ActiveFighters, ActiveFreezers, ActiveHealers,
			FrostedFighter, FrostedHealer, FrostedFreezer, KilledFighter, KilledFreezers, KilledHealer);
	}
		
	pGUI->waitForClick();
	return gameStatus;
}

GAME_STATUS Battle::SilentMode()
{
	CurrentTimeStep = 0;
	
	ImportInputFile();
	GAME_STATUS gameStatus = IN_PROGRESS;
	while (gameStatus == IN_PROGRESS)
	{
		CurrentTimeStep++;
		gameStatus = runTimeStep();
	}

	pGUI->waitForClick();
	return gameStatus;
}

//void Battle::Simulator()
//{
//	ImportInputFile(); //Calling input file
//	AddAllListsToDrawingList();
//	pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetHealth(), BCastle.IsFrosted(), KilledCount,
//		ActiveCount, FrostedCount, ActiveFighter, ActiveFreezer, ActiveHealer,
//	FrostedFighter, FrostedHealer, FrostedFreezer,
//	 KilledFighter, KilledFreezer, KilledHealer);	//upadte interface to show the initial case where all enemies are still inactive
//
//	pGUI->waitForClick();
//
//	while (KilledCount < EnemyCount)	//as long as some enemies are alive (should be updated in next phases)
//	{
//		CurrentTimeStep++;
//		ActivateEnemiesSimulator();
//		if (CurrentTimeStep != 1)
//		{
//			RunSimulation_Once();	//Update Simulation
//		}
//		pGUI->ResetDrawingList();
//		AddAllListsToDrawingList();
//		pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetHealth(), BCastle.IsFrosted(), KilledCount,
//			ActiveCount, FrostedCount, ActiveFighter, ActiveFreezer, ActiveHealer,
//			FrostedFighter, FrostedHealer, FrostedFreezer,
//			KilledFighter, KilledFreezer, KilledHealer);
//		pGUI->waitForClick();
//		
//	}
//
//}

//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
void Battle::AddAllListsToDrawingList()
{	
	//Add inactive queue to drawing list
	int InactiveCount;
	int ActiveFreezerCount;
	int ActiveHealerCount;
	int ActiveFighterCount;
	int KilledCount;
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

	//Killed
	Enemy* const* KilledList = Q_Killed.toArray(KilledCount);
	for (int i = 0; i < KilledCount; i++)
		pGUI->AddToDrawingList(KilledList[i]);

}

void Battle::ActivateEnemies()
{
	Enemy* pE;
	while (Q_Inactive.peekFront(pE))	//as long as there are more inactive enemies
	{
		if (pE->GetArrvTime() > CurrentTimeStep)	//no more arrivals at current time
			return;

		Q_Inactive.dequeue(pE);	//remove enemy from the queue
		pE->SetStatus(ACTV);	//make status active
		if(pE->getType() == 0)
		{ 
			Fighter* pFighter = dynamic_cast<Fighter*>(pE);
			Q_ActiveFighter.insert(pFighter, pFighter->getPriority());
		}
		else if (pE->getType() == 1)
		{
			Healer* pH = dynamic_cast<Healer*>(pE);
			S_ActiveHealer.push(pH);
		}
		else if (pE->getType() == 2)
		{
			Freezer* pF = dynamic_cast<Freezer*>(pE);
			Q_ActiveFreezer.enqueue(pF);
		}
	}
}


//Randomly update enemies distance/status (for demo purposes)
void Battle::Demo_UpdateEnemies()
{
	/*
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
			//pE->DecrementDist();	//move the enemy towards the castle
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
	*/
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
	BCastle.SetOriginalHealth(stoi(CH));
	BCastle.SetcasltePower(stoi(CP));
	BCastle.SetmaxAttack(stoi(N));
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
		Q_Inactive.enqueue(enemy);
	}
}

void Battle::ExportOutputFile(GAME_STATUS gameStatus)
{
	ofstream fout("outputFile.txt");
	Enemy* ptrEnemey;
	int TotalKilled = Q_Killed.getC();
	int sumFirstShotDelay = 0;
	int sumKillDelay = 0;

	fout << "Game is ";
	if (gameStatus == WIN)
	{
		fout << "WIN\n";
	}
	else if (gameStatus == LOSS)
	{
		fout << "LOSS\n";
	}
	else if (gameStatus == DRAWN)
	{
		fout << "DRAWN\n";
	}
	
	fout << "KTS  ID   FD   KD   LT\n";
	for (int i = 0; i < TotalKilled; i++)
	{

		Q_Killed.dequeue(ptrEnemey);
		
		//outputting KTS
		if (ptrEnemey->getKilledTime() < 10)
		{
			fout << ptrEnemey->getKilledTime() << "    ";
		}
		else if (ptrEnemey->getKilledTime() < 100)
		{
			fout << ptrEnemey->getKilledTime() << "   ";
		}
		else if (ptrEnemey->getKilledTime() < 1000)
		{
			fout << ptrEnemey->getKilledTime() << "  ";
		}

		//outputting ID
		if (ptrEnemey->GetID() < 10)
		{
			fout << ptrEnemey->GetID() << "    ";
		}
		else if (ptrEnemey->GetID() < 100)
		{
			fout << ptrEnemey->GetID() << "   ";
		}
		else if (ptrEnemey->GetID() < 1000)
		{
			fout << ptrEnemey->GetID() << "  ";
		}

		//outputting FD
		sumFirstShotDelay += ptrEnemey->getfirstShotTime() - ptrEnemey->GetArrvTime();
		if (ptrEnemey->getfirstShotTime() - ptrEnemey->GetArrvTime() < 10)
		{
			fout << ptrEnemey->getfirstShotTime() - ptrEnemey->GetArrvTime() << "    ";
		}
		else if (ptrEnemey->getfirstShotTime() - ptrEnemey->GetArrvTime() < 100)
		{
			fout << ptrEnemey->getfirstShotTime() - ptrEnemey->GetArrvTime() << "   ";
		}
		else if (ptrEnemey->getfirstShotTime() - ptrEnemey->GetArrvTime() < 1000)
		{
			fout << ptrEnemey->getfirstShotTime() - ptrEnemey->GetArrvTime() << "  ";
		}

		//outputting KD
		sumKillDelay += ptrEnemey->getKilledTime() - ptrEnemey->getfirstShotTime();
		if (ptrEnemey->getKilledTime() - ptrEnemey->getfirstShotTime() < 10)
		{
			fout << ptrEnemey->getKilledTime() - ptrEnemey->getfirstShotTime() << "    ";
		}
		else if (ptrEnemey->getKilledTime() - ptrEnemey->getfirstShotTime() < 100)
		{
			fout << ptrEnemey->getKilledTime() - ptrEnemey->getfirstShotTime() << "   ";
		}
		else if (ptrEnemey->getKilledTime() - ptrEnemey->getfirstShotTime() < 1000)
		{
			fout << ptrEnemey->getKilledTime() - ptrEnemey->getfirstShotTime() << "  ";
		}
		
		//outputting LT
		if (ptrEnemey->getKilledTime() - ptrEnemey->GetArrvTime() < 10)
		{
			fout << ptrEnemey->getKilledTime() - ptrEnemey->GetArrvTime() << "    ";
		}
		else if (ptrEnemey->getKilledTime() - ptrEnemey->GetArrvTime() < 100)
		{
			fout << ptrEnemey->getKilledTime() - ptrEnemey->GetArrvTime() << "   ";
		}
		else if (ptrEnemey->getKilledTime() - ptrEnemey->GetArrvTime() < 1000)
		{
			fout << ptrEnemey->getKilledTime() - ptrEnemey->GetArrvTime() << "  ";
		}
		fout << endl;
	}

	fout << BCastle.getTotalDamage() << endl;

	if (gameStatus == WIN)
	{
		fout << "Total Enemies = " << TotalKilled << endl;
		fout << "Average First-Shot Delay = " << 1.0*sumFirstShotDelay/TotalKilled << endl;
		fout << "Average Kill Delay = " << 1.0 * sumKillDelay / TotalKilled << endl;
	}
	else
	{
		fout << "Killed Enemies = " << TotalKilled << endl;
		fout << "Alive Enemies = " << EnemyCount - TotalKilled << endl;
		fout << "Average First-Shot Delay for killed = " << 1.0 * sumFirstShotDelay / TotalKilled << endl;
		fout << "Average Kill Delay for killed = " << 1.0 * sumKillDelay / TotalKilled << endl;
	}
}

int Battle::getMaxEnemDist()
{
	Queue<Fighter*> TempActiveFighter;
	ArrayStack<Healer*> TempActiveHealer;
	Fighter* fighter;
	Freezer* freezer;
	Healer* healer;
	int ActiveFighter = Q_ActiveFighter.size();
	int ActiveFreezer = Q_ActiveFreezer.getC();
	int ActiveHealer = S_ActiveHealer.getCount();
	Queue<Dist*> Q_distance;
	for (int i = 0; i < 60; i++)
	{
		Dist* distance;
		distance->position = i + 1;
		Q_distance.enqueue(distance);
	}
	Dist* distance;
	for (int i = 0; i < ActiveFighter; i++)
	{
		Q_ActiveFighter.dequeueMax(fighter);
		int position = fighter->GetDistance();
		for (int i = 0; i < 60; i++)
		{
			if (distance->position == position)
			{
				distance->number++;
				Q_distance.enqueue(distance);
				break;
			}
			Q_distance.enqueue(distance);
		}
		TempActiveFighter.enqueue(fighter);
	}
	for (int i = 0; i < ActiveFighter; i++)
	{
		TempActiveFighter.dequeue(fighter);
		Q_ActiveFighter.insert(fighter, fighter->getPriority());
	}
	for (int i = 0; i < ActiveHealer; i++)
	{
		S_ActiveHealer.pop(healer);
		int position = fighter->GetDistance();
		for (int i = 0; i < 60; i++)
		{
			if (distance->position == position)
			{
				distance->number++;
				Q_distance.enqueue(distance);
				break;
			}
			Q_distance.enqueue(distance);
		}
		TempActiveHealer.push(healer);
	}
	for (int i = 0; i < ActiveHealer; i++)
	{
		TempActiveHealer.pop(healer);
		S_ActiveHealer.push(healer);
	}
	for (int i = 0; i < ActiveFreezer; i++)
	{
		Q_ActiveFreezer.dequeue(freezer);
		int position = fighter->GetDistance();
		for (int i = 0; i < 60; i++)
		{
			Q_distance.dequeue(distance);
			if (distance->position == position)
			{
				distance->number++;
				Q_distance.enqueue(distance);
				break;
			}
			Q_distance.enqueue(distance);
		}
		Q_ActiveFreezer.enqueue(freezer);
	}
	int max = 0;
	int index = 0;
	for (int i = 0; i < 60; i++)
	{
		Q_distance.enqueue(distance);
		if (max < distance->number)
		{
			max = distance->number;
			index = distance->position;
		}
	}
	return index;
}

int Battle::getCurrentTimeStep()
{
	return CurrentTimeStep;
}




GAME_STATUS Battle::runTimeStep()
{
	//enemies activate, enemies walking, enemies acting, enemies reloading, enemy picking criteria
	ActivateEnemies();
	Queue<Fighter*> TempActiveFighter;
	ArrayStack<Healer*> TempActiveHealer;
	Fighter* fighter;
	Freezer* freezer;
	Healer* healer;
	int ActiveFighter = Q_ActiveFighter.size();
	int ActiveFreezer = Q_ActiveFreezer.getC();
	int ActiveHealer = S_ActiveHealer.getCount();
	int max = ActiveFighter;
	if (max < ActiveFreezer)
		max = ActiveFreezer;

	for (int i = 0; i < max; i++) //moving fighter and freezer && fighter and freezer attacking castle
	{
		if (i < ActiveFighter)
		{
			Q_ActiveFighter.dequeueMax(fighter);
			if (!(fighter->isFrosted()))
			{
				fighter->Move();
				fighter->meltIce(); //MELT ICE FOR ALL
				if (fighter->getReloading() == 0)
				{
					fighter->attackCastle(&BCastle);
					fighter->setReloading();
				}
				else
					fighter->decrementReload();
			}
			else
			{
				if (fighter->reduceFrostedTime())
					FrostedFighter--;
			}
			TempActiveFighter.enqueue(fighter);
		}

		if (i < ActiveFreezer)
		{
			Q_ActiveFreezer.dequeue(freezer);
			if (!(freezer->isFrosted()))
			{
				freezer->Move();
				freezer->meltIce();
				if (freezer->getReloading() == 0)
				{
					freezer->frostCastle(&BCastle);
					freezer->setReloading();
				}
				else
					freezer->decrementReload();
			}
			else
			{
				if (freezer->reduceFrostedTime())
					FrostedFreezer--;
			}
			Q_ActiveFreezer.enqueue(freezer); //Mlha4 lazma n3ml temp lelfreezer
		}
	}

	for (int i = 0; i < ActiveHealer; i++)
	{
		S_ActiveHealer.pop(healer);
		if (!(healer->isFrosted()))
		{
			healer->Move();
			healer->meltIce();
			for (int j = 0; j < max; j++)
			{
				if (j < ActiveFighter)
				{
					TempActiveFighter.dequeue(fighter);
					if (fighter->GetDistance() == healer->GetDistance()
						|| abs(fighter->GetDistance() - healer->GetDistance()) == 1 || abs(fighter->GetDistance() - healer->GetDistance()) == 2)
						healer->healEnemy(fighter);
					TempActiveFighter.enqueue(fighter);
				}
				if (j < ActiveFreezer)
				{
					Q_ActiveFreezer.dequeue(freezer);
					if (freezer->GetDistance() == healer->GetDistance()
						|| abs(freezer->GetDistance() - healer->GetDistance()) == 1 || abs(freezer->GetDistance() - healer->GetDistance()) == 2)
						healer->healEnemy(freezer);
					Q_ActiveFreezer.enqueue(freezer);
				}
			}

		}
		else
		{
			if (healer->reduceFrostedTime())
				FrostedHealer--;
		}
		TempActiveHealer.push(healer);
	}
	max = ActiveFighter;
	if (max < ActiveHealer)
		max = ActiveHealer;
	for (int i = 0; i < max; i++)
	{
		if (i < ActiveFighter)
		{
			TempActiveFighter.dequeue(fighter);
			Q_ActiveFighter.insert(fighter, fighter->getPriority());
		}
		if (i < ActiveHealer)
		{
			TempActiveHealer.pop(healer);
			S_ActiveHealer.push(healer);
		}
	}

	//Check if the castle destroyed return loss
	if (BCastle.GetHealth() == 0)
		return LOSS;

	//castle attacking
	int n = BCastle.GetmaxAttack();
	srand(time(0));
	int randomnum = rand();
	if ((randomnum % 2) == 0)
	{
		int firenum = n * 0.8;
		for (int i = 0; i < firenum; i++)
		{
			if (Q_ActiveFighter.size() == 0)
				break;
			Q_ActiveFighter.dequeueMax(fighter);
			ENMY_STATUS preType = (fighter->GetStatus());
			if (BCastle.attackEnemy(fighter))
			{
				Q_Killed.enqueue(fighter);
				KilledFighter++;
				if (preType == FRST)
					FrostedFighter--;
			}
			else
				TempActiveFighter.enqueue(fighter);
		}
		if (ActiveFighter < firenum)
		{
			for (int i = 0; i < firenum - ActiveFighter; i++)
			{
				if (S_ActiveHealer.getCount() == 0)
					break;
				S_ActiveHealer.pop(healer);
				ENMY_STATUS preType = (healer->GetStatus());
				if (BCastle.attackEnemy(healer))
				{
					Q_Killed.enqueue(healer);
					BCastle.useHealerTools(healer);
					KilledHealer++;
					if (preType == FRST)
						FrostedHealer--;
				}
				else
					TempActiveHealer.push(healer);

			}

		}
		if ((ActiveFighter + ActiveHealer) < firenum)
		{
			for (int i = 0; i < (firenum - (ActiveFighter + ActiveHealer)); i++)
			{
				if (Q_ActiveFreezer.getC() == 0 || Q_ActiveFreezer.getC() < i)
					break;
				Q_ActiveFreezer.dequeue(freezer);
				ENMY_STATUS preType = (freezer->GetStatus());
				if (BCastle.attackEnemy(freezer))
				{
					Q_Killed.enqueue(freezer);
					KilledFreezers++;
					if (preType == FRST)
						FrostedFreezer--;
				}
				else
					Q_ActiveFreezer.enqueue(freezer);
			}
		}
		int icenum = n - firenum;
		int iced = 0;
		if (ActiveFighter > firenum)
		{
			for (int i = 0; i < icenum; i++)
			{
				if (Q_ActiveFighter.size() == 0)
					break;
				Q_ActiveFighter.dequeueMax(fighter);
				if (!fighter->isFrosted())
					if (BCastle.frostEnemy(fighter))
					{
						FrostedFighter++;
						iced++;
					}
				TempActiveFighter.enqueue(fighter);
			}
		}
		if (ActiveFighter < n) // && ActiveHealer>(n- ActiveFighter)
		{
			icenum = icenum - iced;
			iced = 0;
			for (int i = 0; i < icenum; i++)
			{
				if (S_ActiveHealer.getCount() == 0)
					break;
				S_ActiveHealer.pop(healer);
				if (!healer->isFrosted())
					if (BCastle.frostEnemy(healer))
					{
						FrostedHealer++;
						iced++;
					}

				TempActiveHealer.push(healer);
			}
		}
		icenum = icenum - iced + firenum-ActiveFighter-ActiveHealer;
		for (int i = firenum-ActiveFighter-ActiveHealer; i < ActiveFreezer; i++)
		{
			Q_ActiveFreezer.dequeue(freezer);
			if (i < icenum)
				if (!freezer->isFrosted())
					if (BCastle.frostEnemy(freezer))
						FrostedFreezer++; //m3dna4 m7tageen el iced foo2y ya gege
			Q_ActiveFreezer.enqueue(freezer);
		}
		int TempAF = TempActiveFighter.getC();
		for (int i = 0; i < TempAF; i++)
		{
			TempActiveFighter.dequeue(fighter);
			Q_ActiveFighter.insert(fighter, fighter->getPriority());
		}
		int TempAH = TempActiveHealer.getCount();
		for (int i = 0; i < TempAH; i++)
		{
			TempActiveHealer.pop(healer);
			S_ActiveHealer.push(healer);
		}
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			if (Q_ActiveFighter.size() == 0)
				break;
			Q_ActiveFighter.dequeueMax(fighter);
			ENMY_STATUS preType = (fighter->GetStatus());
			if (BCastle.attackEnemy(fighter))
			{
				Q_Killed.enqueue(fighter);
				KilledFighter++;
				if (preType==FRST)
					FrostedFighter--;
			}
			else
				TempActiveFighter.enqueue(fighter);
		}
		if (ActiveFighter < n)
		{
			for (int i = 0; i < n - ActiveFighter; i++)
			{
				if (S_ActiveHealer.getCount() == 0)
					break;
				S_ActiveHealer.pop(healer);
				ENMY_STATUS preType = (healer->GetStatus());
				if (BCastle.attackEnemy(healer))
				{
					Q_Killed.enqueue(healer);
					KilledHealer++;
					if (preType==FRST)
						FrostedHealer--;
				}
				else
					TempActiveHealer.push(healer);
			}
			
		}
		if ((ActiveFighter + ActiveHealer) < n)
		{
			for (int i = 0; i < ActiveFreezer; i++)
			{
				if (Q_ActiveFreezer.getC() == 0)
					break;
				Q_ActiveFreezer.dequeue(freezer);
				if (i < n - (ActiveFighter + ActiveHealer))
				{
					ENMY_STATUS preType = (freezer->GetStatus());
					if (BCastle.attackEnemy(freezer))
					{
						Q_Killed.enqueue(freezer);
						KilledFreezers++;
						if (preType==FRST)
							FrostedFreezer--;
					}
					else
						Q_ActiveFreezer.enqueue(freezer);
				}
				else
					Q_ActiveFreezer.enqueue(freezer);
			}
		}
		int TempAF = TempActiveFighter.getC();
		for (int i = 0; i < TempAF; i++)
		{
			TempActiveFighter.dequeue(fighter);
			Q_ActiveFighter.insert(fighter, fighter->getPriority());
		}
		int TempAH = TempActiveHealer.getCount();
		for (int i = 0; i < TempAH; i++)
		{
			TempActiveHealer.pop(healer);
			S_ActiveHealer.push(healer);
		}
	}

	//add the logic of SS here

	//check if all enemies killed return win
	int nn = EnemyCount;
	int mm = Q_Killed.getC();
	if (EnemyCount == Q_Killed.getC())
		return WIN;
	else return IN_PROGRESS;
}

