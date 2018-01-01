#include "stdafx.h"
#include "Test.h"
#include "Fish.h"
#include "Vector2.h"

Fish temp;

Test::Test() {

}

Test::~Test() {

}

void Test::run() {
	temp = Fish(Vec2(20,20));
	toQuit = false;
	while (!TCODConsole::isWindowClosed() && !toQuit)
	{
		update();
		render();
	}
}

void Test::update() {
	TCOD_key_t key;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);

	switch (key.vk) {
	case TCODK_UP: temp.mPos += Vec2(0, -1); break;
	case TCODK_DOWN: temp.mPos += Vec2(0, 1); break;
	case TCODK_LEFT: temp.mPos += Vec2(-1, 0); break;
	case TCODK_RIGHT: temp.mPos += Vec2(1, 0); break;
	case TCODK_ENTER:; break;
	case TCODK_ESCAPE: toQuit = true; break;
	case TCODK_SPACE: temp.damage(10);
	default:break;
	}
}

void Test::render() {
	TCODConsole::root->clear();
	temp.draw();
	TCODConsole::flush();
}
