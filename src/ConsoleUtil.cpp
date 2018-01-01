#include "stdafx.h"
#include "libtcod.hpp"
#include "ConsoleUtil.h"
#include "globals.h"
void drawBox(int x, int y, int w, int h, bool isColored, const TCODColor & col)
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
	for (int i = x; i < x + w; i++)
	{
		for (int j = y; j < y + h; j++)
		{
			TCODConsole::root->setCharBackground(i, j, col);
		}
	}
}

void fillWithChar(int x, int y, int w, int h, char c, bool isColored, const TCODColor & col)
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

void drawEntireBox(int x, int y, int w, int h, TCODColor borderCol, TCODColor fillColor)
{
	backgroundFill(x, y, w, h, fillColor);
	fillWithChar(x, y, w, h, ' ', true, fillColor);
	drawBox(x, y, w, h, true, borderCol);
}