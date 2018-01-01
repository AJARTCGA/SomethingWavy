#include "stdafx.h"
#include "BoatEditor.h"
#include "libtcod.hpp"
#include <vector>
#include "StateManager.h"
#include "globals.h"
#include "BasicTower.h"
#include "ConsoleUtil.h"

/// The default constructor
BoatEditor::BoatEditor()
{
	mState = MAIN;
	mCursorX = WIDTH / 3;
	mCursorY = HEIGHT / 2;
	mMenuX = WIDTH / 3 * 2;
	mMenuW = WIDTH - mMenuX - 1;
	mSelection = 0;
	mSelectedEntity = nullptr;
}

/// The destructor.  
BoatEditor::~BoatEditor()
{
}

void BoatEditor::run()
{
	toQuit = false;
	while (!TCODConsole::isWindowClosed() && !toQuit)
	{
		update();
		render();
	}
}

void BoatEditor::updateMain()
{
	TCOD_key_t key;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
	switch (key.vk) {
		case TCODK_ENTER:
			if (mSelection == 0)
				mState = CURSOR;
			if (mSelection == 1)
				mState = PLACE;
			break;
		case TCODK_ESCAPE: 
			toQuit = true;
			break;
		case TCODK_UP: 
			mSelection--; 
			break;
		case TCODK_DOWN: 
			mSelection++; 
			break;
		default:
			break;
	}
	if (mSelection < 0)
		mSelection = 0;
}

void BoatEditor::updateCursor()
{
	TCOD_key_t key;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
	switch (key.vk) {
	case TCODK_ESCAPE: mState = MAIN; break;
	case TCODK_LEFT: mCursorX--; break;
	case TCODK_RIGHT: mCursorX++; break;
	case TCODK_UP: mCursorY--; break;
	case TCODK_DOWN: mCursorY++; break;
	case TCODK_ENTER:
		if (!checkClearPos() && mSelectedEntity == nullptr)
		{
			int boatX = mCursorX - mMenuX / 2 + BOAT->getWidth() * 3 / 2;
			int boatY = mCursorY - HEIGHT / 2 + BOAT->getHeight() * 3 / 2;
			mSelectedEntity = BOAT->getProp(boatX, boatY);
			mOldX = boatX;
			mOldY = boatY;
		}
		else if (checkClearPos() && mSelectedEntity != nullptr)
		{
			int boatX = mCursorX - mMenuX / 2 + BOAT->getWidth() * 3 / 2;
			int boatY = mCursorY - HEIGHT / 2 + BOAT->getHeight() * 3 / 2;
			BOAT->placeProp(boatX, boatY, mSelectedEntity);
			BOAT->removeProp(mOldX, mOldY);
			mSelectedEntity = nullptr;
		}
		break;
	default:break;
	}
	if (mCursorX < 0)
		mCursorX = 0;
	if (mCursorX > WIDTH / 3 * 2 - 1)
		mCursorX = WIDTH / 3 * 2 - 1;
	if (mCursorY < 0)
		mCursorY = 0;
	if (mCursorY > HEIGHT - 1)
		mCursorY = HEIGHT - 1;
}

void BoatEditor::updatePlace()
{
	TCOD_key_t key;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
	switch (key.vk) {
	case TCODK_ESCAPE: mState = MAIN; break;
	case TCODK_LEFT: mCursorX--; break;
	case TCODK_RIGHT: mCursorX++; break;
	case TCODK_UP: mCursorY--; break;
	case TCODK_DOWN: mCursorY++; break;
	case TCODK_ENTER:
		if (checkClearPos())
		{
			int boatX = mCursorX - mMenuX / 2 + BOAT->getWidth() * 3 / 2;
			int boatY = mCursorY - HEIGHT / 2 + BOAT->getHeight() * 3 / 2;
			BOAT->placeProp(boatX, boatY, new BasicTower());
		}
		break;
	default:break;
	}
	if (mCursorX < 0)
		mCursorX = 0;
	if (mCursorX > WIDTH / 3 * 2 - 1)
		mCursorX = WIDTH / 3 * 2 - 1;
	if (mCursorY < 0)
		mCursorY = 0;
	if (mCursorY > HEIGHT - 1)
		mCursorY = HEIGHT - 1;
}

void BoatEditor::update()
{
	switch (mState)
	{
		case MAIN:
			updateMain();
			break;
		case CURSOR:
			updateCursor();
			break;
		case PLACE:
			updatePlace();
			break;
		default:
			updateMain();
			break;
	}
}
/*

void drawBox(int x, int y, int w, int h, bool isColored = false, const TCODColor & col = TCODColor::red)
{
	TCODColor originalColor = TCODConsole::root->getDefaultForeground();
	if (isColored)
	{
		TCODConsole::root->setDefaultForeground(col);
	}
	TCODConsole::root->putChar(x, y, 201);				//top-left corner
	TCODConsole::root->putChar(x, y + h - 1, 200);	//bottom-left corner
	TCODConsole::root->putChar(x + w - 1, y, 187);			//top-right corner
	TCODConsole::root->putChar(x + w - 1, y + h - 1, 188);	//bottom-right corner
	for (int j = y + 1; j < y + h - 1; j++)
	{
		TCODConsole::root->putChar(x, j, 186);			// vertical double bar
		TCODConsole::root->putChar(x + w - 1, j, 186);		// vertical double bar
	}
	for (int i = x + 1; i < x + w - 1; i++)
	{
		TCODConsole::root->putChar(i, y, 205);				// horizontal double bar
		TCODConsole::root->putChar(i, y + h - 1, 205);		// horizontal double bar
	}
	TCODConsole::root->setDefaultForeground(originalColor);
}

void backgroundFill(int x, int y, int w, int h, const TCODColor & col)
{
	for (int i = x; i < x + w ; i++)
	{
		for (int j = y; j < y + h; j++)
		{
			TCODConsole::root->setCharBackground(i, j, col);
		}
	}
}

void fillWithChar(int x, int y, int w, int h, char c,  bool isColored = false, const TCODColor & col = TCODColor::red)
{
	TCODColor originalColor = TCODConsole::root->getDefaultForeground();
	if (isColored)
	{
		TCODConsole::root->setDefaultForeground(col);
	}
	for (int i = x; i < x + w; i++)
	{
		for (int j = y; j < y + h; j++)
		{
			TCODConsole::root->putChar(i, j, c);
		}
	}
	TCODConsole::root->setDefaultForeground(originalColor);
}

void drawWater()
{
	TCODColor originalColor = TCODConsole::root->getDefaultForeground();
	TCODConsole::root->setDefaultForeground(TCODColor::blue);

	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			TCODConsole::root->putChar(i, j, '-');
		}
	}
	TCODConsole::root->setDefaultForeground(originalColor);
}

*/

bool BoatEditor::checkClearPos()
{
	int boatX = mCursorX - mMenuX / 2 + BOAT->getWidth() * 3 / 2;
	int boatY = mCursorY - HEIGHT / 2 + BOAT->getHeight() * 3 / 2;
	Entity * e = BOAT->getProp(boatX, boatY);
	if (e != nullptr)
		return false;
	if (!BOAT->getFloorBool(boatX / 3, boatY / 3))
		return false;
	if (boatX < 0 || boatX > BOAT->getWidth() * 3 || boatY < 0 || boatY > BOAT->getHeight() * 3)
		return false;
	return true;
}

void BoatEditor::drawMain()
{
	int movementFactor = 5;
	TCODColor originalColor = TCODConsole::root->getDefaultForeground();
	drawBox(mMenuX + 2, (mSelection + 1) * movementFactor - 2, mMenuW - 4, movementFactor, true, TCODColor::darkGreen);
	std::string s;
	TCODConsole::root->setDefaultForeground(TCODColor::darkGreen);
	s = "CURSOR";
	TCODConsole::root->print(mMenuX + mMenuW / 2 - s.length() / 2, movementFactor, s.c_str());
	s = "PLACE";
	TCODConsole::root->print(mMenuX + mMenuW / 2 - s.length() / 2, movementFactor * 2, s.c_str());
	s = "TEST";
	TCODConsole::root->print(mMenuX + mMenuW / 2 - s.length() / 2, movementFactor * 3, s.c_str());
	s = "TEST";
	TCODConsole::root->print(mMenuX + mMenuW / 2 - s.length() / 2, movementFactor * 4, s.c_str());
	s = "TEST";
	TCODConsole::root->print(mMenuX + mMenuW / 2 - s.length() / 2, movementFactor * 5, s.c_str());
	TCODConsole::root->setDefaultForeground(originalColor);
	
}

void BoatEditor::drawCursor()
{
	TCODColor originalColor = TCODConsole::root->getDefaultForeground();
	TCODConsole::root->putChar(mCursorX, mCursorY, 'X');
	TCODConsole::root->setCharForeground(mCursorX, mCursorY, TCODColor::yellow);
	Entity * e = BOAT->getProp(mCursorX - mMenuX / 2 + BOAT->getWidth() * 3 / 2, mCursorY - HEIGHT / 2 + BOAT->getHeight() * 3 / 2);
	if (e != nullptr)
	{
		std::string s = e->getString();
		TCODConsole::root->setDefaultForeground(TCODColor::darkGreen);
		TCODConsole::root->print(mMenuX + mMenuW / 2 - s.length() / 2, 3, s.c_str());
	}
	TCODConsole::root->setDefaultForeground(originalColor);
}

void BoatEditor::drawPlace()
{
	TCODColor originalColor = TCODConsole::root->getDefaultForeground();
	TCODConsole::root->putChar(mCursorX, mCursorY, 'X');
	TCODConsole::root->setCharForeground(mCursorX, mCursorY, TCODColor::darkGreen);
	if(!checkClearPos())
		TCODConsole::root->setCharForeground(mCursorX, mCursorY, TCODColor::red);
	TCODConsole::root->setDefaultForeground(originalColor);
}

void BoatEditor::render()
{
	TCODConsole::root->clear();
	TCODColor originalColor = TCODConsole::root->getDefaultForeground();

	
	drawWater();
	BOAT->draw(mMenuX / 2, HEIGHT / 2);
	drawBox(mMenuX, 1, mMenuW, HEIGHT - 2, true, TCODColor::darkGreen);
	backgroundFill(mMenuX, 1, mMenuW, HEIGHT - 2, TCODColor::darkestGreen);
	backgroundFill(mMenuX, 1, mMenuW, HEIGHT - 2, TCODColor::darkestGreen);
	fillWithChar(mMenuX + 1, 2, mMenuW - 2, HEIGHT - 4, ' ');
	std::string s = " SHIP EDITOR ";
	TCODConsole::root->setDefaultForeground(TCODColor::darkGreen);
	TCODConsole::root->print(mMenuX + mMenuW / 2 - s.length() / 2, 1, s.c_str());
	TCODConsole::root->setDefaultForeground(originalColor);

	switch (mState)
	{
		case MAIN:
			drawMain();
			break;
		case CURSOR:
			drawCursor();
			break;
		case PLACE:
			drawPlace();
			break;
	}

	TCODConsole::flush();
}