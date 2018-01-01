#include "stdafx.h"
#include "libtcod.hpp"
#include "Fish.h"
#include "StateManager.h"
#include "globals.h"
#include "ColorUtil.h"

Fish::Fish(Vec2 pos, Vec2 vel)
{
	mPos = pos;
	mChar = '&';
	mVel = vel;
	mColor = ColorUtil::Color(1.0f, 1.0f, 0);
	mHealth = 100;
	mCurrHealth = 100;
	mMaxHealth = 100;
	mDamage = 20;
}

Fish::Fish() 
{
	mVel = Vec2(1, 0);
}

Fish::~Fish()
{

}

void Fish::update()
{
	float hp_f = (float)mCurrHealth / (float)mMaxHealth;
	ColorUtil::Color dest = ColorUtil::Color(1, hp_f, hp_f);
	while (mColor != dest)
	{
		mColor.interpolateColor(dest);
	}

	int boatX = mPos.getX() - WIDTH / 2 + BOAT->getWidth() * 3 / 2;
	int boatY = mPos.getY() - HEIGHT / 2 + BOAT->getHeight() * 3 / 2;
	int targetX = boatX + mVel.getX();
	int targetY = boatY + mVel.getY();
	Entity * e = BOAT->getProp(targetX, targetY);
	if (e != nullptr)
	{
		e->damage(20);
		if (e->getHealth() < 0)
		{
			BOAT->removeProp(targetX, targetY);
		}
	}
	else
	{
		mPos += mVel;
	}
}

void Fish::draw()
{
	if (mPos.getX() > 0 && mPos.getX() < WIDTH && mPos.getY() > 0 && mPos.getY() < HEIGHT)
	{
		TCODConsole::root->putChar((int)mPos.getX(), (int)mPos.getY(), (int)mChar);
		int boatX = mPos.getX() - WIDTH / 2 + BOAT->getWidth() * 3 / 2;
		int boatY = mPos.getY() - HEIGHT / 2 + BOAT->getHeight() * 3 / 2;
		if (BOAT->getFloorBool(boatX / 3, boatY / 3) && boatX > 0 && boatY > 0)
		{
			TCODConsole::root->setCharForeground((int)mPos.getX(), (int)mPos.getY(), mColor.toTCODColor());
		}
		else
		{
			TCODConsole::root->setCharForeground((int)mPos.getX(), (int)mPos.getY(), TCODColor::lightBlue);
		}
	}
	//if (mX > 0 && mX < STATE_MANAGER->getWindowWidth() / 3 && mY > 0 && mY < STATE_MANAGER->getWindowHeight() / 3)
	//{
	//	if (abs(mVelX > mVelY))
	//	{
	//		if (mVelX > 0)
	//		{
	//			TCODConsole::root->print((int)mX * 3, mY * 3 + 1, "><>");
	//		}
	//		else
	//		{
	//			TCODConsole::root->print((int)mX * 3, mY * 3 + 1, "<><");
	//		}
	//	}
	//	else
	//	{
	//		if (mVelY > 0)
	//		{
	//			TCODConsole::root->putChar((int)mX * 3 + 1, mY * 3, 'V');
	//			TCODConsole::root->putChar((int)mX * 3 + 1, mY * 3 + 1, '^');
	//			TCODConsole::root->putChar((int)mX * 3 + 1, mY * 3 + 2, 'V');
	//		}
	//		else
	//		{
	//			TCODConsole::root->putChar((int)mX * 3 + 1, mY * 3, '^');
	//			TCODConsole::root->putChar((int)mX * 3 + 1, mY * 3 + 1, 'V');
	//			TCODConsole::root->putChar((int)mX * 3 + 1, mY * 3 + 2, '^');
	//		}
	//	}
	//}
}
void Fish::damage(int d) {
	mHealth -= d;
	mColor = ColorUtil::Color(1, 0, 0);
	mCurrHealth -= d;
};
