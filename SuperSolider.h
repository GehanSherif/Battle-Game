#pragma once
class SuperSolider
{
private:
	int Distance;
	
	const int Destiny, speed = 3;

public:
	SuperSolider(int distance, int destiny);

	//getters
	int getDistance();
	int getDestiny();

	//setters
	
	//operations
	void move();
};