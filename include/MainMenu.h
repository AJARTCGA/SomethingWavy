#pragma once
#include "State.h"
#include <stdio.h>
#include <iostream>
#include <vector>

class MainMenu : public State
{
	/***** ATTRIBUTES *****/
private:
	int imgW;
	int imgH;
	char * cArr;
	std::vector<char> mWaterMap;

	/***** CONSTRUCTOR / DESTRUCTOR *****/
public:
	/// The default constructor
	MainMenu();

	/// The destructor.  
	~MainMenu();

	/***** METHODS *****/
public:
	void run();
	void update();
	void render();
protected:
	void updateWaterMap(bool clear = false);
	char getRandomWaveChar();
};