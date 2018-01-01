#include "libtcod.hpp"
#include <vector>
#include <time.h>
#include "StateManager.h"
#include "Intro.h"
#include "globals.h"


/// The default constructor
Intro::Intro()
{
	srand(time(NULL));
	welcomeText = "Welcome to Something Wavey";
	welcomeText2 = "This is a survival, tower-defense, and partially legal worm trading simulator.";
	welcomeText3 = "Help Something Guy embark on his journey to fund Timmy's college fund.";
}

/// The destructor.  
Intro::~Intro()
{
}

void Intro::run()
{
	int imgW = 79;
	int imgH = 14;
	toQuit = false;

	while (!TCODConsole::isWindowClosed() && !toQuit)
	{
		update();
		render();
	}
}

void Intro::update()
{
	TCOD_key_t key;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
	switch (key.vk) {
	case TCODK_ENTER: STATE_MANAGER->runState(TRADE_MENU); break;
	case TCODK_ESCAPE: toQuit = true; break;
	default:break;
	}
}

void Intro::render()
{
	TCODConsole::root->clear();
	TCODConsole::root->print(WIDTH / 2 - welcomeText.length() / 2, HEIGHT / 3, welcomeText.c_str());
	TCODConsole::root->print(WIDTH / 2 - welcomeText2.length() / 2, HEIGHT / 2, welcomeText2.c_str());
	TCODConsole::root->print(WIDTH / 2 - welcomeText3.length() / 2, HEIGHT / 3 * 2, welcomeText3.c_str());
	TCODConsole::root->print(WIDTH / 2 - enterText.length() / 2, HEIGHT / 5 * 4, enterText.c_str());
	TCODConsole::flush();
}