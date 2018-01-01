#pragma once

#include "State.h"
#include <vector>
class RegionSelect : public State
{
	/***** ATTRIBUTES *****/
protected:

	std::vector<float> mElevation;
	std::vector<std::vector<int>> mWaterBodies;
	int mLargestBodyIdx;
	std::vector<int> mPorts;
	int mSelectedPort;
	/***** CONSTRUCTOR / DESTRUCTOR *****/
public:
	RegionSelect();
	~RegionSelect();

	/***** METHODS *****/
protected:
	void findLargestBodyOfWater();
	void floodFill(int x, int y, int listNum);
	void placeRegions(int numRegions);
	void drawCursor(int x, int y, TCODColor col = TCODColor::yellow);
public:
	void run();
	void update();
	void render();
};
