#include "libtcod.hpp"
#include <vector>
#include <time.h>
#include "TextBox.h"



/// The default constructor
TextBox::TextBox()
{
	srand(time(NULL));
}

/// The destructor.  
TextBox::~TextBox()
{
}



void TextBox::start(int w, int h)
{
	std::cout << "TextBox";
	mWidth = w;
	mHeight = h;
	run();
}

void TextBox::run()
{
	int imgW = 79;
	int imgH = 14;
	while (!TCODConsole::isWindowClosed())
	{
		TCOD_key_t key;
		TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
		switch (key.vk) {
		case TCODK_ENTER:; break;
		default:break;
		}

		TCODConsole::root->clear();
		TCODConsole::root->print(mWidth / 2 - enterText.length() / 2, mHeight / 2, enterText.c_str());
		TCODConsole::flush();
	}
}