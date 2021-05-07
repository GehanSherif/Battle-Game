#include "Battle.h"
#include "GUI\GUI.h"

int main()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	Battle* pGameBattle = new Battle;
	//pGameBattle->RunSimulation();
	pGameBattle->ImportInputFile();
	delete pGameBattle;
	
	return 0;
}
