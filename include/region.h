#include "stdafx.h"
#include "worm.h"
#include <time.h>
#include <random>
#ifndef _REGION_H_
#define _REGION_H_
class region
{
protected:
	///Postion to display region
	std::vector<float> mPos;
	///Name of the region
	std::string mRegionName;
	///Holds Worm Variation;

	///Starting parameter for value fluctuation 
	float mVariabilityStart;
	///Ending parameter for value fluctuation 
	float mVariabilityEnd;
	///Holds how many worms you own of this regions variation
	int wormBankNotes = 10;

	std::vector<float> regionDemands;
public:
	worm * wormSpecies;

public:
	region(std::string regionName, float varStart, float varEnd, float initWormVal = 1); //add color parameter TCODColor(rgb)
	~region();

public:
	virtual void setPosition(std::vector<float> pos)
	{
		mPos = pos;
	}
	virtual std::string getRegionName()
	{
		return mRegionName;
	}
	virtual float getVariabilityStart()
	{
		return mVariabilityStart;
	}
	virtual float getVariabilityEnd()
	{
		return mVariabilityEnd;
	}

	virtual void addBankNotes(int amt)
	{
		wormBankNotes += amt;
	}

	virtual void subtractBankNotes(int amt)
	{
		wormBankNotes -= amt;
	}

	virtual int getWormBankNotes()
	{
		return wormBankNotes;
	}
	virtual void setRegionDemand()
	{
		std::default_random_engine generator;
		float dArr[5] = { 0,0,0,0,0 };
		for (int i = 0; i < 5; i++)
		{
			dArr[i] = (float)((rand() % 1000) / 500.0f);
			//std::cout << mRegionName<< dArr[i] << std::endl;
		}
			
		
		regionDemands.assign(dArr, dArr + 5);
	}
	virtual float getRegionDemand(int idx)
	{
		return regionDemands[idx];
		//std::cout << regionDemands[idx] << std::endl;
	}
	void update(float dt);
};
#endif