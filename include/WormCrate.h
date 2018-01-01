#pragma once
#include "Crate.h"

class WormCrate : public Crate
{
protected:
	int mWormData;

public:
	WormCrate()
	{
		mChar = '#';
		mName = "Worm Crate";
		mHealth = 100;
	}
};