#pragma once
class SuperSolider
{
private:
	int ssID, Distance, Destiny;
	const int speed = 3;

public:
	SuperSolider(int id);

	//getters
	int getDistance();
	int getDestiny();

	//setters
	void setDestiny(int d);
	
	//operations
	void move();
};