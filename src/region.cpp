#include "stdafx.h"
#include "region.h"
#include "globals.h"

region::region(std::string regionName, float varStart, float varEnd, float initWormVal)
{
	mRegionName = regionName;
	mVariabilityStart = varStart;
	mVariabilityEnd = varEnd;
	wormSpecies = new worm(regionName, varStart, varEnd, initWormVal); //Add color here
	wormVariationContainer.push_back(wormSpecies);
	setRegionDemand();
}

region::~region()
{

}

void region::update(float dt)
{
	//this needs to be changed to be able to change after the completiton of each wave
	if(WAVE_CLEAR)
		wormSpecies->updateValues();
}
