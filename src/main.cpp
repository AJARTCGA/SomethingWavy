#include "stdafx.h"
#include <vector>
#include <iostream>
#include "libtcod.hpp"
#include <StateManager.h>
#include "globals.h"
#include "Vector2.h"
#include <time.h>
#include "region.h"

std::ostream& operator<<(std::ostream& out, Vec2 rhs) {
	return out << "[" << rhs.getX() << "," << rhs.getY() << "]";
}

int main() {
	TCODConsole::initRoot(WIDTH, HEIGHT, "Something Wavy", true);
	srand(time(NULL));

	//TCODSystem::setFps(60);

	// Copy paste Test.h to make a new state
	// add the #define to list_of_states.h and then add the state to the state manager below in the right order

	// to change to the state, go to MainMenu.cpp and look in the update function for more info


	region * ptp = new region("pinker-than-pink", -1, 5, 5);
	region * red = new region("crimson", 2, 5, 10);
	region * green = new region("emerald", 5, 5, 25);
	region * blue = new region("cyan", 10, 5, 50);
	region * rainbow = new region("rainbow", 20, 5, 100);
	regionContainer.push_back(ptp);
	regionContainer.push_back(red);
	regionContainer.push_back(green);
	regionContainer.push_back(blue);
	regionContainer.push_back(rainbow);


	StateManager * sm = new StateManager();
	sm->mStates.push_back(new MainMenu());			// 0
	sm->mStates.push_back(new MainGame());			// 1
	sm->mStates.push_back(new Intro());				// 2
	sm->mStates.push_back(new BoatEditor());		// 3
	sm->mStates.push_back(new Test());				// 4
	sm->mStates.push_back(new RegionSelect());		// 5
	sm->mStates.push_back(new TradeMenu());          // 6
	STATE_MANAGER->runState(MAIN_MENU);

	return 0;
}