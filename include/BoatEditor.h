#pragma once
#include "State.h"
#include "Watercraft.h"
#include "Fish.h"
#include <stdio.h>
#include <iostream>

class BoatEditor : public State
{
	enum EditorState {
		MAIN, 
		CURSOR,
		PLACE
	};
	/***** ATTRIBUTES *****/
	EditorState mState;
	int mCursorX, mCursorY;
	int mMenuX, mMenuW;
	int mSelection;
	Entity * mSelectedEntity;
	int mOldX, mOldY;
	/***** CONSTRUCTOR / DESTRUCTOR *****/
public:
	/// The default constructor
	BoatEditor();

	/// The destructor.  
	~BoatEditor();

	/***** METHODS *****/
protected:
	void updateMain();
	void updateCursor();
	void updatePlace();

	void drawMain();
	void drawCursor();
	void drawPlace();

	bool checkClearPos();

public:
	void run();
	void update();
	void render();

};