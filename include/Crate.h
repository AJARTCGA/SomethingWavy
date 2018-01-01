#pragma once
#include "Entity.h"

class Crate : public Entity
{
protected:
	int	mCargoType;
	int mCargoAmount;

public:
	Crate()
	{
		mChar = '#';
		mName = "Crate";
		mHealth = 100;
	}
	void update()
	{
		float hp_f = (float)mCurrHealth / (float)mMaxHealth;
		ColorUtil::Color dest = ColorUtil::Color(1, hp_f, hp_f);
		if (mColor != dest)
		{
			mColor.interpolateColor(dest);
		}
	}
	void damage(int d) {
		mHealth -= d;
		mColor = ColorUtil::Color(1, 0, 0);
		mCurrHealth -= d;
	}

};