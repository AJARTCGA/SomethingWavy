#ifndef _WORM_H_
#define _WORM_H_

#include "stdafx.h"
#include <iostream>
#include <random>
#include <stdlib.h> 
#include <time.h>
class worm
{
	protected:
		std::string mRegionName;
		float mVariabilityStart;
		float mVariabilityEnd;
		float mValue;
		
		
	//@@@Constructor/Destructor@@@
	public:
		worm(std::string regionName, float varStart, float varEnd, float initVal = 1);
		~worm();
	//@@@Getters/Setters@@@
	public:
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
		virtual void setValue(float fluctuationAmt)
		{
			mValue += (float)(fluctuationAmt*.0001);
		}
		virtual float getValue()
		{
			return mValue;
		}

	public:
		void updateValues();
};

#endif