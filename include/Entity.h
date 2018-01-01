#ifndef _ENTITY_
#define _ENTITY_

#include "Vector2.h"
#include "libtcod.hpp"
#include "ColorUtil.h"

class Entity
{
	/***** ATTRIBUTES *****/
public:
	Vec2 mPos, mVel;
protected:
	int mHealth;
	char mChar;
	std::string mName;
	ColorUtil::Color mColor;
	int mDamage;
	float mCurrHealth;
	float mMaxHealth;
	/***** CONSTRUCTOR / DECONSTRUCTOR *****/

	/***** GETTERS / SETTERS *****/
public:
	int getHealth() { return mHealth; }
	void setHealth(int health) { mHealth = health; }
	char getChar() { return mChar; }
	void setChar(char c) { mChar = c; }
	std::string getString() { return mName; }
	ColorUtil::Color getColor() { return mColor; }
	/***** METHODS *****/

	virtual void update()
	{

	}
	virtual void damage(int d) { 
		mHealth -= d;
		mColor = ColorUtil::Color(1, 0, 0);
		mCurrHealth -= d;
	};
};


#endif
