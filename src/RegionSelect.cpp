#include "stdafx.h"
#include "RegionSelect.h"
#include "Fish.h"
#include "Vector2.h"
#include "globals.h"
#include <queue>
#include <StateManager.h>
#include "ConsoleUtil.h"

RegionSelect::RegionSelect() 
{
	mSelectedPort = 0;
	TCODNoise noise = TCODNoise::TCODNoise(2);
	noise.setType(TCOD_noise_type_t::TCOD_NOISE_SIMPLEX);
	float arr[2];
	for (int j = 0; j < HEIGHT; j++)
	{
		arr[1] = (float)j / 25;
		for (int i = 0; i < WIDTH; i++)
		{
			arr[0] = (float)i / 25;
			float n = (noise.getFbm(arr, 16) + 1) / 2;
			mElevation.push_back(n);
		}
	}
	findLargestBodyOfWater();
	placeRegions(5);
}

RegionSelect::~RegionSelect() {

}

void RegionSelect::findLargestBodyOfWater()
{
	for (int j = 0; j < HEIGHT; j++)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			int idx = i + j * WIDTH;
			int v = ((int)((float)255 * mElevation[idx]));
			v = v / 10 * 10;
			if (v < 150)
			{
				bool hasBeenDone = false;
				for(std::vector<int> vec : mWaterBodies)
				{
					if (std::find(vec.begin(), vec.end(), idx) != vec.end())
					{
						hasBeenDone = true;
					}
				}
				if (!hasBeenDone)
				{
					mWaterBodies.push_back(std::vector<int>());
					floodFill(i, j, mWaterBodies.size() - 1);
				}
			}
		}
	}
	int max = 0;
	for (int i = 0; i < mWaterBodies.size(); i++)
	{
		if (mWaterBodies[i].size() > max)
		{
			max = mWaterBodies[i].size();
			mLargestBodyIdx = i;
		}
	}
}

void RegionSelect::floodFill(int x, int y, int listNum)
{
	std::vector<int> visited;
	std::queue<int> Q;
	Q.push(x + y * WIDTH);
	visited.push_back(x + y * WIDTH);
	while(!Q.empty())
	{
		int idx = Q.front();
		Q.pop();
		int x2 = idx % WIDTH;
		int y2 = idx / WIDTH;
		mWaterBodies[listNum].push_back(idx);
		if (x2 > 0)
		{
			int i2 = (x2 - 1) + y2 * WIDTH;
			int v = ((int)((float)255 * mElevation[i2]));
			v = v / 10 * 10;
			if (v < 150)
			{
				if (std::find(mWaterBodies[listNum].begin(), mWaterBodies[listNum].end(), i2) == mWaterBodies[listNum].end() && std::find(visited.begin(), visited.end(), i2) == visited.end())
				{
					Q.push(i2);
					visited.push_back(i2);
				}
			}
		}
		if (x2 < WIDTH - 1)
		{
			int i2 = (x2 + 1) + y2 * WIDTH;
			int v = ((int)((float)255 * mElevation[i2]));
			v = v / 10 * 10;
			if (v < 150)
			{
				if (std::find(mWaterBodies[listNum].begin(), mWaterBodies[listNum].end(), i2) == mWaterBodies[listNum].end() && std::find(visited.begin(), visited.end(), i2) == visited.end())
				{
					Q.push(i2);
					visited.push_back(i2);
				}
			}
		}
		if (y2 > 0)
		{
			int i2 = x2 + (y2 - 1) * WIDTH;
			int v = ((int)((float)255 * mElevation[i2]));
			v = v / 10 * 10;
			if (v < 150)
			{
				if (std::find(mWaterBodies[listNum].begin(), mWaterBodies[listNum].end(), i2) == mWaterBodies[listNum].end() && std::find(visited.begin(), visited.end(), i2) == visited.end())
				{
					Q.push(i2);
					visited.push_back(i2);
				}
			}
		}
		if (y2 < HEIGHT - 1)
		{
			int i2 = x2 + (y2 + 1) * WIDTH;
			int v = ((int)((float)255 * mElevation[i2]));
			v = v / 10 * 10;
			if (v < 150)
			{
				if (std::find(mWaterBodies[listNum].begin(), mWaterBodies[listNum].end(), i2) == mWaterBodies[listNum].end() && std::find(visited.begin(), visited.end(), i2) == visited.end())
				{
					Q.push(i2);
					visited.push_back(i2);
				}
			}

		}
	}
}

void RegionSelect::placeRegions(int numRegions)
{
	if (mWaterBodies.size() > 0)
	{
		std::vector<int> vec = mWaterBodies[mLargestBodyIdx];
		int count = 0;
		while(count < numRegions)
		{
			int x = rand() % WIDTH;
			int y = rand() % HEIGHT;
			int idx = x + y * WIDTH;
			while (std::find(mWaterBodies[mLargestBodyIdx].begin(), mWaterBodies[mLargestBodyIdx].end(), idx)  == mWaterBodies[mLargestBodyIdx].end())
			{
				x = rand() % WIDTH;
				y = rand() % HEIGHT;
				idx = x + y * WIDTH;
			}
			int dX = rand() % 3 - 1;
			int dY = rand() % 3 - 1;
			while (dX == 0 && dY == 0)
			{
				dX = rand() % 3 - 1;
				dY = rand() % 3 - 1;
			}
			while (x > 0 && x < WIDTH - 1 && y > 0 && y < HEIGHT - 1 && std::find(vec.begin(),vec.end(), idx) != vec.end())
			{
				x += dX;
				y += dY;
				idx = x + y * WIDTH;
			}
			if (x > 0 && x < WIDTH - 1 && y > 0 && y < HEIGHT - 1)
			{
				mPorts.push_back(idx);
				count++;
			}
		}
	}
}

void RegionSelect::run() {
	toQuit = false;
	
	while (!TCODConsole::isWindowClosed() && !toQuit)
	{
		update();
		render();
	}
}

void RegionSelect::update() {
	TCOD_key_t key;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);

	switch (key.vk) {
	case TCODK_ENTER:
		if (currentRegion == mSelectedPort)
		{
			STATE_MANAGER->runState(TRADE_MENU);
		}
		else
		{
			currentRegion = mSelectedPort;
			WAVE_CLEAR = true;
			STATE_MANAGER->runState(MAIN_GAME);
		}
		break;
	case TCODK_ESCAPE: toQuit = true; break;
	case TCODK_RIGHT: mSelectedPort++; break;
	case TCODK_LEFT: mSelectedPort--; break;
	default:break;
	}
	if (mSelectedPort < 0)
	{
		mSelectedPort = mPorts.size() - 1;
	}
	if (mSelectedPort >=  mPorts.size())
	{
		mSelectedPort = 0;
	}
}

void RegionSelect::drawCursor(int x, int y, TCODColor col)
{
	TCODColor originalColor = TCODConsole::root->getDefaultForeground();
	TCODConsole::root->setDefaultForeground(col);
	if (x > 0)
	{
		if (y > 0)
		{
			TCODConsole::root->putChar(x - 1, y - 1, TCOD_CHAR_NW);
			int v = ((int)((float)255 * mElevation[x + y * WIDTH]));
			v = v / 10 * 10;
			TCODColor col(v / 2, v, v / 3);
			if (v < 150)
			{
				col.r = 0;
				col.g = 100 + (int)(mElevation[x - 1 + (y-1) * WIDTH] * 50);
				col.b = 200 + (int)(mElevation[x - 1 + (y - 1) * WIDTH] * 50);
			}
			TCODConsole::root->setCharBackground(x - 1, (y - 1), col);
		}
		if (y < HEIGHT - 1)
		{
			TCODConsole::root->putChar((x - 1), y + 1, TCOD_CHAR_SW);
			int v = ((int)((float)255 * mElevation[(x - 1) + (y + 1) * WIDTH]));
			v = v / 10 * 10;
			TCODColor col(v / 2, v, v / 3);
			if (v < 150)
			{
				col.r = 0;
				col.g = 100 + (int)(mElevation[(x - 1) + (y + 1) * WIDTH] * 50);
				col.b = 200 + (int)(mElevation[(x - 1) + (y + 1) * WIDTH] * 50);
			}
			TCODConsole::root->setCharBackground(x - 1, y + 1, col);
		}
		TCODConsole::root->putChar(x - 1, y, TCOD_CHAR_VLINE);
		int v = ((int)((float)255 * mElevation[x - 1 + y * WIDTH]));
		v = v / 10 * 10;
		TCODColor col(v / 2, v, v / 3);
		if (v < 150)
		{
			col.r = 0;
			col.g = 100 + (int)(mElevation[x - 1 + y * WIDTH] * 50);
			col.b = 200 + (int)(mElevation[x - 1 + y * WIDTH] * 50);
		}
		TCODConsole::root->setCharBackground(x - 1, y, col);
	}
	if (x < WIDTH - 1)
	{
		if (y > 0)
		{
			TCODConsole::root->putChar(x + 1, (y - 1), TCOD_CHAR_NE);
			int v = ((int)((float)255 * mElevation[x + 1 + (y - 1) * WIDTH]));
			v = v / 10 * 10;
			TCODColor col(v / 2, v, v / 3);
			if (v < 150)
			{
				col.r = 0;
				col.g = 100 + (int)(mElevation[x + 1 + (y - 1) * WIDTH] * 50);
				col.b = 200 + (int)(mElevation[x + 1 + (y - 1) * WIDTH] * 50);
			}
			TCODConsole::root->setCharBackground(x + 1, (y - 1), col);
		}
		if (y < HEIGHT - 1)
		{
			TCODConsole::root->putChar(x + 1, y + 1, TCOD_CHAR_SE);
			int v = ((int)((float)255 * mElevation[x + 1 + (y + 1) * WIDTH]));
			v = v / 10 * 10;
			TCODColor col(v / 2, v, v / 3);
			if (v < 150)
			{
				col.r = 0;
				col.g = 100 + (int)(mElevation[x + 1 + (y + 1) * WIDTH] * 50);
				col.b = 200 + (int)(mElevation[x + 1 + (y + 1) * WIDTH] * 50);
			}
			TCODConsole::root->setCharBackground(x + 1, (y + 1), col);
		}
		TCODConsole::root->putChar(x + 1, y, TCOD_CHAR_VLINE);
		int v = ((int)((float)255 * mElevation[x + 1 + y * WIDTH]));
		v = v / 10 * 10;
		TCODColor col(v / 2, v, v / 3);
		if (v < 150)
		{
			col.r = 0;
			col.g = 100 + (int)(mElevation[x + 1 + y * WIDTH] * 50);
			col.b = 200 + (int)(mElevation[x + 1 + y * WIDTH] * 50);
		}
		TCODConsole::root->setCharBackground(x + 1, y, col);
	}
	if (y > 0)
	{
		TCODConsole::root->putChar(x, y - 1, TCOD_CHAR_HLINE);
		int v = ((int)((float)255 * mElevation[x + (y - 1) * WIDTH]));
		v = v / 10 * 10;
		TCODColor col(v / 2, v, v / 3);
		if (v < 150)
		{
			col.r = 0;
			col.g = 100 + (int)(mElevation[x + (y - 1) * WIDTH] * 50);
			col.b = 200 + (int)(mElevation[x + (y - 1) * WIDTH] * 50);
		}
		TCODConsole::root->setCharBackground(x, (y - 1), col);
	}
	if (y < HEIGHT - 1)
	{
		TCODConsole::root->putChar(x, y + 1, TCOD_CHAR_HLINE);
		int v = ((int)((float)255 * mElevation[x + (y + 1) * WIDTH]));
		v = v / 10 * 10;
		TCODColor col(v / 2, v, v / 3);
		if (v < 150)
		{
			col.r = 0;
			col.g = 100 + (int)(mElevation[x + (y + 1) * WIDTH] * 50);
			col.b = 200 + (int)(mElevation[x + (y + 1) * WIDTH] * 50);
		}
		TCODConsole::root->setCharBackground(x,  (y + 1), col);
	}
	TCODConsole::root->setDefaultForeground(originalColor);
}

void RegionSelect::render() {
	TCODConsole::root->clear();
	for (int j = 0; j < HEIGHT; j++)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			TCODConsole::root->putChar(i, j, 178);
			int v = ((int)((float)255 * mElevation[i + j * WIDTH]));
			v = v / 10 * 10;
			TCODColor col(v / 2,v,v / 3);
			if (v < 150)
			{
				col.r = 0;
				col.g = 100 + (int)(mElevation[i + j * WIDTH] * 50);
				col.b = 200 + (int)(mElevation[i + j * WIDTH] * 50);
			}
			TCODConsole::root->setCharForeground(i, j, col);
		}
	}
	
	for (int i = 0; i < mPorts.size(); i++)
	{
		int idx = mPorts[i];
		int x = idx % WIDTH;
		int y = idx / WIDTH;
		TCODConsole::root->putChar(idx % WIDTH, idx / WIDTH, 'O');
		TCODConsole::root->setCharForeground(x, y, TCODColor::red);
		int v = ((int)((float)255 * mElevation[idx]));
		v = v / 10 * 10;
		TCODColor col(v / 2, v, v / 3);
		TCODConsole::root->setCharBackground(x, y, col);
		if (mSelectedPort == i)
		{
			if(i == currentRegion)
				drawCursor(x, y, TCODColor::orange);
			else
				drawCursor(x, y, TCODColor::yellow);
		}
		else if (i == currentRegion)
		{
			drawCursor(x, y, TCODColor::red);
		}
	}

	drawEntireBox(2, HEIGHT - 10, WIDTH - 4, 8, TCODColor::darkerGreen, TCODColor::darkestGreen);
	TCODColor originalColor = TCODConsole::root->getDefaultForeground();

	std::string s = "REGIONAL WORM PRICES";
	TCODConsole::root->setDefaultForeground(TCODColor::darkGreen);

	TCODConsole::root->print(WIDTH / 2 - s.length() / 2, HEIGHT - 10, s.c_str());

	TCODConsole::root->setDefaultForeground(TCODColor::crimson);
	s = "CRIMSON: " + std::to_string((int)(wormVariationContainer[0]->getValue() * regionContainer[mSelectedPort]->getRegionDemand(0)));
	TCODConsole::root->print(WIDTH / 4 - s.length() / 2, HEIGHT - 8, s.c_str());

	TCODConsole::root->setDefaultForeground(TCODColor::cyan);
	s = "CYAN: " + std::to_string((int)(wormVariationContainer[1]->getValue() * regionContainer[mSelectedPort]->getRegionDemand(1)));
	TCODConsole::root->print( 3 * WIDTH / 4 - s.length() / 2, HEIGHT - 8, s.c_str());

	TCODConsole::root->setDefaultForeground(TCODColor::green);
	s = "EMERALD: " + std::to_string((int)(wormVariationContainer[2]->getValue() * regionContainer[mSelectedPort]->getRegionDemand(2)));
	TCODConsole::root->print(WIDTH / 4 - s.length() / 2, HEIGHT - 6, s.c_str());

	TCODConsole::root->setDefaultForeground(TCODColor::pink);
	s = "PINKER-THAN-PINK: " + std::to_string((int)(wormVariationContainer[3]->getValue() * regionContainer[mSelectedPort]->getRegionDemand(3)));
	TCODConsole::root->print(3 * WIDTH / 4 - s.length() / 2, HEIGHT - 6, s.c_str());

	TCODConsole::root->setDefaultForeground(TCODColor::yellow);
	s = "RAINBOW: " + std::to_string((int)(wormVariationContainer[4]->getValue() * regionContainer[mSelectedPort]->getRegionDemand(4)));
	TCODConsole::root->print(WIDTH / 2 - s.length() / 2, HEIGHT - 6, s.c_str());

	//drawBox(2, HEIGHT - 10, WIDTH - 4, 8, true, TCODColor::darkGreen);

	TCODConsole::flush();
	TCODConsole::root->setDefaultForeground(originalColor);
}
