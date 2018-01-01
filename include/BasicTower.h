#pragma once
#include "Tower.h"

class BasicTower : public Tower
{
public:
	BasicTower()
	{
		mChar = '%';
		mName = "Basic Tower";
	}
};