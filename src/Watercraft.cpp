#include "stdafx.h"
#include "Watercraft.h"
#include <time.h>
#include <math.h>
#include "globals.h"
#include "libtcod.hpp"
#include "Crate.h"

// A template-specialization of the msSingleton attribute for the StateManager class
template<> Watercraft * Singleton<Watercraft>::msSingleton = nullptr;

Watercraft::Watercraft(int w, int h)
{	
	srand(time(NULL));
	mWidth = w;
	mHeight = h;
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			if (rand() % 100 + 1 > abs((i - mWidth / 2) + (j - mHeight / 2)))
				mShape.push_back(true);
			else
				mShape.push_back(false);
		}
	}
	for (int i = 0; i < mWidth * 3; i++)
	{
		for (int j = 0; j < mHeight * 3; j++)
		{
			if (getFloorBool(i / 3, j / 3))
			{
				if (rand() % 100 + 1 > 95)
					mPropMap[i * mHeight * 3 + j] = new Crate();
			}
		}
	}
}

Watercraft::~Watercraft()
{

}

bool Watercraft::getFloorBool(int x, int y)
{
	if (x < 0 || x > mWidth - 1 || y < 0 || y > mHeight - 1)
	{
		return false;
	}
	return mShape.at(x + y * mWidth);
}

int Watercraft::getWidth()
{
	return mWidth;
}

int Watercraft::getHeight()
{
	return mHeight;
}

void drawEast(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar( 3 * i + xOffset + 2, 3 * j + yOffset + 1, 179);
}
void drawEastOpen(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset + 2, 3 * j + yOffset + 1, ' ');
}

void drawNorthEastCorner(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset + 2, 3 * j + yOffset, 191);
}
void drawNorthEastFlat(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset + 2, 3 * j + yOffset, 196);
}
void drawNorthEastOpen(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset + 2, 3 * j + yOffset, ' ');
}
void drawNorthEastVert(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset + 2, 3 * j + yOffset, 179);
}
void drawNorthEastOpp(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset + 2, 3 * j + yOffset, 192);
}

void drawSouthEastCorner(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset + 2, 3 * j + yOffset + 2, 217);
}
void drawSouthEastFlat(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset + 2, 3 * j + yOffset + 2, 196);
}
void drawSouthEastOpen(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset + 2, 3 * j + yOffset + 2, ' ');
}
void drawSouthEastVert(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset + 2, 3 * j + yOffset + 2, 179);
}
void drawSouthEastOpp(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset + 2, 3 * j + yOffset + 2, 218);
}

void drawWest(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset, 3 * j + yOffset + 1, 179);
}
void drawWestOpen(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset, 3 * j + yOffset + 1, ' ');
}

void drawNorthWestCorner(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset, 3 * j + yOffset, 218);
}
void drawNorthWestFlat(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset, 3 * j + yOffset, 196);
}
void drawNorthWestOpen(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset, 3 * j + yOffset, ' ');
}
void drawNorthWestVert(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset, 3 * j + yOffset, 179);
}
void drawNorthWestOpp(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset, 3 * j + yOffset, 217);
}

void drawSouthWestCorner(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset, 3 * j + yOffset + 2, 192);
}
void drawSouthWestFlat(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset, 3 * j + yOffset + 2, 196);
}
void drawSouthWestOpen(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset, 3 * j + yOffset + 2, ' ');
}
void drawSouthWestVert(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset, 3 * j + yOffset + 2, 179);
}
void drawSouthWestOpp(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset, 3 * j + yOffset + 2, 191);
}

void drawSouth(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset + 1, 3 * j + yOffset + 2, 196);
}
void drawSouthOpen(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset + 1, 3 * j + yOffset + 2, ' ');
}

void drawNorth(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset + 1, 3 * j + yOffset, 196);
}
void drawNorthOpen(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset + 1, 3 * j + yOffset, ' ');
}

void drawSpace(int i, int j, int xOffset, int yOffset)
{
	TCODConsole::root->putChar(3 * i + xOffset + 1, 3 * j + yOffset + 1, ' ');
}

void Watercraft::draw(int x, int y)
{
	int xOffset = x - mWidth * 3 / 2;
	int yOffset = y - mHeight * 3 / 2;
	for (int i = 0; i < mWidth; i++)
	{
		for (int j = 0; j < mHeight; j++)
		{
			if (getFloorBool(i, j))
			{
				drawSpace(i, j, xOffset, yOffset);
				//NORTH
				if (getFloorBool(i, j - 1))
					drawNorthOpen(i, j, xOffset, yOffset);
				else
					drawNorth(i, j, xOffset, yOffset);

				//SOUTH
				if (getFloorBool(i, j + 1))
					drawSouthOpen(i, j, xOffset, yOffset);
				else
					drawSouth(i, j, xOffset, yOffset);

				//EAST
				if (getFloorBool(i+ 1, j))
					drawEastOpen(i, j, xOffset, yOffset);
				else
					drawEast(i, j, xOffset, yOffset);

				//WEST
				if (getFloorBool(i - 1, j))
					drawWestOpen(i, j, xOffset, yOffset);
				else
					drawWest(i, j, xOffset, yOffset);

				//NORTHEAST
				bool top = getFloorBool(i, j-1);
				bool topRight = getFloorBool(i + 1, j - 1);
				bool right = getFloorBool(i + 1, j);
				if(top && !right && !topRight)
					drawNorthEastVert(i, j, xOffset, yOffset);
				else if (!top && right && !topRight)
					drawNorthEastFlat(i, j, xOffset, yOffset);
				else if (top && right && topRight)
					drawNorthEastOpen(i, j, xOffset, yOffset);
				else if (top && right && !topRight)
					drawNorthEastOpp(i, j, xOffset, yOffset);
				else if (!top && !right && !topRight)
					drawNorthEastCorner(i, j, xOffset, yOffset);
				else if (!top && right && topRight)
					drawNorthEastFlat(i, j, xOffset, yOffset);
				else if (top && !right && topRight)
					drawNorthEastVert(i, j, xOffset, yOffset);
				else if (!top && !right && topRight)
					drawNorthEastCorner(i, j, xOffset, yOffset);

				//NORTHWEST
				top = getFloorBool(i, j - 1);
				bool topLeft = getFloorBool(i - 1, j - 1);
				bool left = getFloorBool(i - 1, j);
				if (top && !left && !topLeft)
					drawNorthWestVert(i, j, xOffset, yOffset);
				else if (!top && left && !topLeft)
					drawNorthWestFlat(i, j, xOffset, yOffset);
				else if (top && left && topLeft)
					drawNorthWestOpen(i, j, xOffset, yOffset);
				else if (top && left && !topLeft)
					drawNorthWestOpp(i, j, xOffset, yOffset);
				else if (!top && !left && !topLeft)
					drawNorthWestCorner(i, j, xOffset, yOffset);
				else if (!top && left && topLeft)
					drawNorthWestFlat(i, j, xOffset, yOffset);
				else if (top && !left && topLeft)
					drawNorthWestVert(i, j, xOffset, yOffset);
				else if (!top && !left && topLeft)
					drawNorthWestCorner(i, j, xOffset, yOffset);

				//SOUTHEAST
				bool bottom = getFloorBool(i, j + 1);
				bool bottomRight = getFloorBool(i + 1, j + 1);
				right = getFloorBool(i + 1, j);
				if (bottom && !right && !bottomRight)
					drawSouthEastVert(i, j, xOffset, yOffset);
				else if (!bottom && right && !bottomRight)
					drawSouthEastFlat(i, j, xOffset, yOffset);
				else if (bottom && right && bottomRight)
					drawSouthEastOpen(i, j, xOffset, yOffset);
				else if (bottom && right && !bottomRight)
					drawSouthEastOpp(i, j, xOffset, yOffset);
				else if (!bottom && !right && !bottomRight)
					drawSouthEastCorner(i, j, xOffset, yOffset);
				else if(!bottom && right && bottomRight)
					drawSouthEastFlat(i, j, xOffset, yOffset);
				else if(bottom && !right && bottomRight)
					drawSouthEastVert(i, j, xOffset, yOffset);
				else if (!bottom && !right && bottomRight)
					drawSouthEastCorner(i, j, xOffset, yOffset);

				//SOUTHWEST
				bottom = getFloorBool(i, j + 1);
				bool bottomLeft = getFloorBool(i - 1, j + 1);
				left = getFloorBool(i - 1, j);
				if (bottom && !left && !bottomLeft)
					drawSouthWestVert(i, j, xOffset, yOffset);
				else if (!bottom && left && !bottomLeft)
					drawSouthWestFlat(i, j, xOffset, yOffset);
				else if (bottom && left && bottomLeft)
					drawSouthWestOpen(i, j, xOffset, yOffset);
				else if (bottom && left && !bottomLeft)
					drawSouthWestOpp(i, j, xOffset, yOffset);
				else if (!bottom && !left && !bottomLeft)
					drawSouthWestCorner(i, j, xOffset, yOffset);
				else if (!bottom && left && bottomLeft)
					drawSouthWestFlat(i, j, xOffset, yOffset);
				else if (bottom && !left && bottomLeft)
					drawSouthWestVert(i, j, xOffset, yOffset);
				else if (!bottom && !left && bottomLeft)
					drawSouthWestCorner(i, j, xOffset, yOffset);
				
			}
		}
	}
	drawProps(x, y);
}

void Watercraft::update()
{
	for (int i = 0; i < mWidth * 3; i++)
	{
		for (int j = 0; j < mHeight * 3; j++)
		{
			if (mPropMap.find(i * mHeight * 3 + j) != mPropMap.end())
			{
				Entity * e = mPropMap[i * mHeight * 3 + j];
				e->update();
				if (e->getHealth() < 0)
					removeProp(i, j);
			}
		}
	}
}

void Watercraft::drawProps(int x, int y)
{
	for (int i = 0; i < mWidth * 3; i++)
	{
		for (int j = 0; j < mHeight * 3; j++)
		{
			if (mPropMap.find(i * mHeight * 3 + j) != mPropMap.end())
			{
				Entity * e = mPropMap[i * mHeight * 3 + j];
				int xOffset = x - mWidth * 3 / 2;
				int yOffset = y - mHeight * 3 / 2;
				TCODConsole::root->putChar(i + xOffset, j + yOffset, e->getChar());
				TCODConsole::root->setCharForeground(i + xOffset, j + yOffset, e->getColor().toTCODColor());
			}
		}
	}
}

Entity * Watercraft::getProp(int x, int y)
{
	if (x < 0 || x > mWidth * 3 || y < 0 || y > mHeight * 3)
	{
		return nullptr;
	}
	if (mPropMap.find(x * mHeight * 3 + y) != mPropMap.end())
	{
		return mPropMap[x * mHeight * 3 + y];
	}
	return nullptr;
}

void Watercraft::placeProp(int x, int y, Entity * e)
{
	mPropMap[x * mHeight * 3 + y] = e;
}

void Watercraft::removeProp(int x, int y)
{
	mPropMap.erase(x * mHeight * 3 + y);
}