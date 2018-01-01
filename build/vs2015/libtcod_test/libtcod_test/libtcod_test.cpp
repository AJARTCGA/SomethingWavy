#include "stdafx.h"
/*
#include <vector>
#include <iostream>
#include "libtcod.hpp"


#define width 80
#define height 50

class testBlock {
public:
	int mX, mY;

};

int main() {
	std::vector<testBlock *> v;
	for (int i = 0; i < width; i++)
	{
		v.push_back(new testBlock());
		v[i]->mX = i;
		v[i]->mY = 0;
	}
	int playerx = 40, playery = 25;
	TCODConsole::initRoot(width, height, "libtcod C++ tutorial", false);
	while (!TCODConsole::isWindowClosed()) {
		TCOD_key_t key;
		TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
		switch (key.vk) {
		case TCODK_UP: playery--; break;
		case TCODK_DOWN: playery++; break;
		case TCODK_LEFT: playerx--; break;
		case TCODK_RIGHT: playerx++; break;
		default:break;
		}
		TCODConsole::root->clear();
		for (std::vector<testBlock*>::iterator it = v.begin(); it < v.end(); it++) {
			if ((*it)->mX >= 0 && (*it)->mX < width && (*it)->mY >= 0 && (*it)->mY < height)
			{
				//std::cout << (*it)->mY << std::endl;
				TCODConsole::root->putChar((*it)->mX, (*it)->mY, '#');
				if ((*it)->mY < height - 1)
					(*it)->mY++;
			}
		}
		TCODConsole::root->putChar(playerx, playery, '@');
		TCODConsole::root->setCharBackground(playerx, playery, TCODColor::blue);
		TCODConsole::root->setCharForeground(playerx, playery, TCODColor::orange);
		TCODConsole::flush();
	}
	return 0;
}*/