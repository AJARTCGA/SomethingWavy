#pragma once
#include "Singleton.h"
#include "list_of_states.h"

#define STATE_MANAGER StateManager::getSingletonPtr()

class StateManager : public Singleton<StateManager>
{
	/***** ATTRIBUTES *****/
protected:
	static int mCurState; // an integer corresponding to the list of state defines in list_of_states.h
						  // eg. if (StateManager::mCurState == MAIN_MENU) ...

	StateManager * mInstance;
	int mScreenWidth, mScreenHeight;

public:
	std::vector<State *> mStates;

	/***** CONSTRUCTOR / DECONSTRUCTOR *****/
public:
	// the default constructor
	StateManager();

	// the destructor
	~StateManager();

	/***** METHODS *****/
public:
	void runState(int state);
	//void runTextBox(TEXTBOXSTATE state = (TEXTBOXSTATE)0);
	int getState();
	int getWindowWidth();
	int getWindowHeight();
};