#pragma once
#include "State.h"
#include "Watercraft.h"
#include "Fish.h"
#include <stdio.h>
#include <iostream>

struct Wave
{
	int y;
	int lifeTime;
	int force;
	int leftSide;
	int rightSide;
	int rightDepth;
	int leftDepth;
	bool isActive;
};

class MainGame : public State
{
	/***** ATTRIBUTES *****/
protected:
	int counter;
	std::vector<char> mWaterMap;
	Wave mCurWave;
	std::vector<Fish> mFishVec;
	int mNumWaves;

private:
	Watercraft * boat;

	/***** CONSTRUCTOR / DESTRUCTOR *****/
public:
	/// The default constructor
	MainGame();

	/// The destructor.  
	~MainGame();

	/***** METHODS *****/
public:
	void run();
	void update();
	void render();

protected:
	void updateWaterMap(bool clear = false);
	char getRandomWaveChar();
	void generateWave();
	
};