#ifndef _FISH_
#define _FISH_

#include "Entity.h"
#include "Vector2.h"

class Fish : public Entity
{
	/***** ATTRIBUTES *****/
public:
protected:
	int mHealth, mType;
	char mChar;

	/***** CONSTRUCTOR / DECONSTRUCTOR *****/
public:
	Fish();
	Fish(Vec2 pos, Vec2 vel = Vec2(0,0));
	~Fish();

	/***** GETTERS / SETTERS *****/

	/***** METHODS *****/
public:
	void update();
	void draw();
	void damage(int d);
};

#endif