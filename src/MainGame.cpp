#include "stdafx.h"
#include "MainGame.h"
#include <time.h>
#include "Watercraft.h"
#include "Fish.h"
#include "globals.h"
#include "StateManager.h"


/// The default constructor
MainGame::MainGame()
{
	srand(time(NULL));
	boat = new Watercraft(rand() % 10 + 6, rand() % 10 + 6);
	
}

/// The destructor.  
MainGame::~MainGame()
{
}

void MainGame::run()
{
	toQuit = false;
	counter = 0;
	updateWaterMap(true);
	mFishVec.push_back(Fish(Vec2(0, HEIGHT / 2), Vec2(1,0)));
	mNumWaves = 0;
	while (!TCODConsole::isWindowClosed() && !toQuit) 
	{
		update();
		render();
	}
}

void MainGame::update() 
{
	TCOD_key_t key;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
	switch (key.vk) {
	case TCODK_ENTER:; break;
	case TCODK_ESCAPE: toQuit = true; break;
	default:break;
	}

	
	counter++;
	if (counter == 20)
	{
		counter = 0;
		for (int i = 0; i < mFishVec.size(); i++)
		{
			mFishVec[i].update();
		}
		updateWaterMap();
		
	}
	if (mNumWaves >= 5)
	{
		STATE_MANAGER->runState(TRADE_MENU);
	}
}

void MainGame::render()
{
	TCODColor originalColor = TCODConsole::root->getDefaultForeground();
	TCODConsole::root->setDefaultForeground(TCODColor::blue);
	TCODConsole::root->clear();
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			TCODConsole::root->putChar(i, j, mWaterMap[i + j * WIDTH]);
		}
	}
	TCODConsole::root->setDefaultForeground(originalColor);
	BOAT->draw(WIDTH / 2, HEIGHT / 2);
	for (int i = 0; i < mFishVec.size(); i++)
	{
		mFishVec[i].draw();
	}
	//mFish.draw();
	TCODConsole::flush();
}

void MainGame::generateWave()
{
	mNumWaves++;
	mCurWave.isActive = true;
	mCurWave.y = rand() % HEIGHT + 1;
	mCurWave.lifeTime = 0;
	mCurWave.force = rand() % 5 + 3;
	mCurWave.leftSide = 1;
	mCurWave.rightSide = 1;
	mCurWave.leftDepth = 0;
	mCurWave.rightDepth = 0;
	std::cout << "Wave generated at y=" << mCurWave.y << std::endl;
}

char MainGame::getRandomWaveChar()
{
	int r = rand() % 100 + 1;
	if (r < 50)
	{
		return '-';
	}
	else if (r < 75)
	{
		return '^';
	}
	else
	{
		return '~';
	}
}

void MainGame::updateWaterMap(bool clear)
{
	if (clear)
	{
		mWaterMap.clear();
		for (int i = 0; i < WIDTH; i++)
		{
			for (int j = 0; j < HEIGHT; j++)
			{

				mWaterMap.push_back(getRandomWaveChar());
			}
		}
	}
	else
	{
		for (int i = WIDTH - 1; i > 0; i--)
		{
			for (int j = 0; j < HEIGHT; j++)
			{
				mWaterMap[i + j * WIDTH] = mWaterMap[(i - 1) + j * WIDTH];
				if (rand() % 100 + 1 > 80 && mWaterMap[i + j * WIDTH] != '|' && mWaterMap[i + j * WIDTH] != '\\' && mWaterMap[i + j * WIDTH] != '/')
					mWaterMap[i + j * WIDTH] = getRandomWaveChar();
			}
		}
		if (!mCurWave.isActive && rand() % 100 + 1 < 5)
		{
			generateWave();
		}
		for (int j = 0; j < HEIGHT; j++)
		{
			mWaterMap[j * WIDTH] = getRandomWaveChar();
		}
		if (mCurWave.isActive)
		{
			for (int j = 0; j < HEIGHT / 2; j++)
			{
				if (j == 0)
				{
					if (mCurWave.lifeTime == 0)
						mWaterMap[mCurWave.y * WIDTH] = '|';
				}
				else
				{
					if (mCurWave.y - j >= 0 && mCurWave.y + j < (HEIGHT - 1))
					{
						if (j == mCurWave.leftSide && mCurWave.leftDepth == mCurWave.lifeTime)
						{
							mCurWave.leftSide++;
							if (rand() % 100 + 1 > 50)
							{
								mWaterMap[(mCurWave.y - j) * WIDTH] = '|';
							}
							else
							{
								mWaterMap[(mCurWave.y - j) * WIDTH] = '\\';
								mCurWave.leftDepth++;

							}
						}
						if (j == mCurWave.rightSide && mCurWave.rightDepth == mCurWave.lifeTime)
						{
							mCurWave.rightSide++;
							if (rand() % 100 + 1 > 50)
							{
								mWaterMap[(mCurWave.y + j) * WIDTH] = '|';
							}
							else
							{
								mWaterMap[(mCurWave.y + j) * WIDTH] = '/';
								mCurWave.rightDepth++;
							}
						}
					}
				}
			}
			mCurWave.lifeTime++;
			if (mCurWave.lifeTime > mCurWave.leftDepth)
				mCurWave.leftDepth = mCurWave.lifeTime;
			if (mCurWave.lifeTime > mCurWave.rightDepth)
				mCurWave.rightDepth = mCurWave.lifeTime;

			if (mCurWave.lifeTime >= mCurWave.force)
			{
				mCurWave.isActive = false;
			}
		}
	}
}