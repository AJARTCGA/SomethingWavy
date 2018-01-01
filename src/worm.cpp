#include "stdafx.h"
#include "worm.h"



worm::worm(std::string regionName, float varStart, float varEnd, float initVal)
{
	mRegionName = regionName;
	mVariabilityStart = varStart;
	mVariabilityEnd = varEnd;
	mValue = initVal;

}

worm::~worm()
{
}

void worm::updateValues()
{
	std::default_random_engine generator;
	std::normal_distribution<float> distribution(mVariabilityStart, mVariabilityEnd);
	float number = (distribution(generator));
	if (rand()%2 == 1)
		number *= -1;
	mValue += number;
	if (mValue <= 0)
		mValue -= number;
	printf(mRegionName.c_str());
	std::cout << mRegionName << ": " << mValue << std::endl;
}
