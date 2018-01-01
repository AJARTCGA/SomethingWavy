#include "stdafx.h"
#include "MainMenu.h"
#include "libtcod.hpp"
#include <vector>
#include "StateManager.h"
#include "globals.h"
#include "ConsoleUtil.h"

/// The default constructor
MainMenu::MainMenu()
{
	enterText = "Press ENTER to play!";
	char tmp[] = { ' ','_','_','_','_','_','_','_',' ',' ','_','_','_','_','_','_','_',' ',' ','_','_',' ',' ',' ','_','_',' ',' ','_','_','_','_','_','_','_',' ',' ','_','_','_','_','_','_','_',' ',' ','_','_',' ',' ',' ','_','_',' ',' ','_','_','_',' ',' ',' ','_','_',' ',' ',' ',' ','_',' ',' ','_','_','_','_','_','_','_',' ',10,'|',' ',' ',' ',' ',' ',' ',' ','|','|',' ',' ',' ',' ',' ',' ',' ','|','|',' ',' ','|','_','|',' ',' ','|','|',' ',' ',' ',' ',' ',' ',' ','|','|',' ',' ',' ',' ',' ',' ',' ','|','|',' ',' ','|',' ','|',' ',' ','|','|',' ',' ',' ','|',' ','|',' ',' ','|',' ',' ','|',' ','|','|',' ',' ',' ',' ',' ',' ',' ','|',10,'|',' ',' ','_','_','_','_','_','|','|',' ',' ',' ','_',' ',' ',' ','|','|',' ',' ',' ',' ',' ',' ',' ','|','|',' ',' ',' ',' ','_','_','_','|','|','_',' ',' ',' ',' ',' ','_','|','|',' ',' ','|','_','|',' ',' ','|','|',' ',' ',' ','|',' ','|',' ',' ',' ','|','_','|',' ','|','|',' ',' ',' ',' ','_','_','_','|',10,'|',' ','|','_','_','_','_','_',' ','|',' ',' ','|',' ','|',' ',' ','|','|',' ',' ',' ',' ',' ',' ',' ','|','|',' ',' ',' ','|','_','_','_',' ',' ',' ','|',' ',' ',' ','|',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|','|',' ',' ',' ','|',' ','|',' ',' ',' ',' ',' ',' ',' ','|','|',' ',' ',' ','|',' ','_','_',' ',10,'|','_','_','_','_','_',' ',' ','|','|',' ',' ','|','_','|',' ',' ','|','|',' ',' ',' ',' ',' ',' ',' ','|','|',' ',' ',' ',' ','_','_','_','|',' ',' ','|',' ',' ',' ','|',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|','|',' ',' ',' ','|',' ','|',' ',' ','_',' ',' ',' ',' ','|','|',' ',' ',' ','|','|',' ',' ','|',10,' ','_','_','_','_','_','|',' ','|','|',' ',' ',' ',' ',' ',' ',' ','|','|',' ','|','|','_','|','|',' ','|','|',' ',' ',' ','|','_','_','_',' ',' ',' ','|',' ',' ',' ','|',' ',' ','|',' ',' ',' ','_',' ',' ',' ','|','|',' ',' ',' ','|',' ','|',' ','|',' ','|',' ',' ',' ','|','|',' ',' ',' ','|','_','|',' ','|',10,'|','_','_','_','_','_','_','_','|','|','_','_','_','_','_','_','_','|','|','_','|',' ',' ',' ','|','_','|','|','_','_','_','_','_','_','_','|',' ',' ','|','_','_','_','|',' ',' ','|','_','_','|',' ','|','_','_','|','|','_','_','_','|',' ','|','_','|',' ',' ','|','_','_','|','|','_','_','_','_','_','_','_','|',10,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','_',' ',' ',' ',' ',' ','_',' ',' ','_','_','_','_','_','_','_',' ',' ','_','_',' ',' ',' ','_','_',' ',' ','_','_',' ',' ',' ','_','_',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',10,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ','|',' ','_',' ','|',' ','|','|',' ',' ',' ','_',' ',' ',' ','|','|',' ',' ','|',' ','|',' ',' ','|','|',' ',' ','|',' ','|',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',10,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ','|','|',' ','|','|',' ','|','|',' ',' ','|','_','|',' ',' ','|','|',' ',' ','|','_','|',' ',' ','|','|',' ',' ','|','_','|',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',10,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|','|',' ',' ',' ',' ',' ',' ',' ','|','|',' ',' ',' ',' ',' ',' ',' ','|','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',10,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|','|',' ',' ',' ',' ',' ',' ',' ','|','|',' ',' ',' ',' ',' ',' ',' ','|','|','_',' ',' ',' ',' ',' ','_','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',10,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ','_',' ',' ',' ','|','|',' ',' ',' ','_',' ',' ',' ','|',' ','|',' ',' ',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',10,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|','_','_','|',' ','|','_','_','|','|','_','_','|',' ','|','_','_','|',' ',' ','|','_','_','_','|',' ',' ',' ',' ','|','_','_','_','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' };
	cArr = (char*)malloc(sizeof(tmp));
	std::memcpy(cArr, tmp, sizeof(tmp));
	imgW = 79;
	imgH = 14;
	updateWaterMap(true);
}

/// The destructor.  
MainMenu::~MainMenu()
{
}

void MainMenu::run()
{
	toQuit = false;
	while (!TCODConsole::isWindowClosed() && !toQuit) 
	{
		update();
		render();
	}
}

void MainMenu::update()
{
	TCOD_key_t key;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
	switch (key.vk) {
	case TCODK_ENTER: STATE_MANAGER->runState(TEXT_BOX_INTRO); break;
	case TCODK_ESCAPE: toQuit = true; break;
	default:break;
	}

	// To change states, follow this format
	switch (key.c) {
	case 't': STATE_MANAGER->runState(TEST); break;
	case 'b': STATE_MANAGER->runState(BOAT_EDITOR); break;
	case 'r': STATE_MANAGER->runState(REGION_SELECT); break;
	case 'w': STATE_MANAGER->runState(TRADE_MENU); break;
	default: break;
	}
	static int counter = 0;
	counter++;
	if (counter >= 20)
	{
		updateWaterMap();
		counter = 0;
	}
}

void MainMenu::render()
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


	TCODConsole::root->setDefaultForeground(TCODColor::darkGreen);
	static int x = WIDTH / 2 - imgW / 2;
	static int y = HEIGHT;

	if (y <= HEIGHT / 3 - imgH / 2)
	{
		backgroundFill(WIDTH / 10, y - HEIGHT / 8, WIDTH / 10 * 8, HEIGHT / 2, TCODColor::darkestGreen);
		fillWithChar(WIDTH / 10, y - HEIGHT / 8, WIDTH / 10 * 8, HEIGHT / 2, ' ');
		drawBox(WIDTH / 10, y - HEIGHT / 8, WIDTH / 10 * 8, HEIGHT / 2, true, TCODColor::darkGreen);
	}
	else
	{
		static int ref = HEIGHT / 3 - imgH / 2;
		backgroundFill(WIDTH / 10, ref - HEIGHT / 8, WIDTH / 10 * 8, HEIGHT / 2, TCODColor::darkestGreen - TCODColor(50, 50, 50));
		fillWithChar(WIDTH / 10, ref - HEIGHT / 8, WIDTH / 10 * 8, HEIGHT / 2, ' ');
		drawBox(WIDTH / 10, ref - HEIGHT / 8, WIDTH / 10 * 8, HEIGHT / 2, true, TCODColor::darkGreen - TCODColor(50, 50, 50));
	}


	for (int i = 0; i < imgW; i++)
	{
		for (int j = 0; j < imgH; j++)
		{
			if (cArr[i + j * imgW] >= 32 && x + i >= 0 && x + i < WIDTH && y + j >= 0 && y + j < HEIGHT)
			{
				TCODConsole::root->putChar(x + i, y + j, cArr[i + j * imgW]);
			}
		}
	}
	if (y > HEIGHT / 3 - imgH / 2)
	{
		y--;
	}
	else
	{
		TCODConsole::root->print(WIDTH / 2 - enterText.length() / 2, HEIGHT / 2, enterText.c_str());
	}
	TCODConsole::flush();
	TCODConsole::root->setDefaultForeground(originalColor);
}

char MainMenu::getRandomWaveChar()
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

void MainMenu::updateWaterMap(bool clear)
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
	}
}