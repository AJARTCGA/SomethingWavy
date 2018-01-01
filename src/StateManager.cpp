#include "StateManager.h"


// A template-specialization of the msSingleton attribute for the StateManager class
template<> StateManager * Singleton<StateManager>::msSingleton = nullptr;

// TODO:
// A vector that contains the states accessible by the state manager
// std::vector<State> mStates;

StateManager::StateManager()
{
}

StateManager::~StateManager()
{
	//Do nothing
}

void StateManager::runState(int state)
{
	mStates[state]->run();
}


int StateManager::getState()
{
	return MAIN_MENU; //StateManager::mCurState;
}

int StateManager::getWindowWidth()
{
	return mScreenWidth;
}

int StateManager::getWindowHeight()
{
	return mScreenHeight;
}