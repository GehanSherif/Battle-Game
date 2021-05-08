#include "Battle.h"
#include "GUI\GUI.h"
#include "ArrayStack.h"
#include<iostream>
using namespace std;
int main()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	Battle* pGameBattle = new Battle;
	pGameBattle->RunSimulation();
	delete pGameBattle;
	
	return 0;
	//::ShowWindow(::GetConsoleWindow(), SW_SHOW);
	//ArrayStack<int> test(5);
	//test.push(1);
	//test.push(2);
	//test.push(3);
	//test.push(4);
	//test.push(5);
	//cout << "Done" << endl;
	//const int count = test.getCount();

	//int* arr = new int[count];

	//arr = test.toArray();

	//for (int i = 0; i < count; i++)
	//	cout << arr[i] << " ";


}
