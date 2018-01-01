
#include "worm.h"
#include "region.h"
#include <vector>

#ifndef _GLOBALS_H_
#define _GLOBALS_H_
#define WIDTH 100
#define HEIGHT 75
#define FRAMES_PER_SECOND 30

///Holds the different types of worms
extern std::vector<worm*> wormVariationContainer;

///Holds the different regions
extern std::vector<region*> regionContainer;

extern bool WAVE_CLEAR;

extern float totalValue;

extern int coinPouch;

extern std::vector<int> wormPouch;

extern region* currentRegionPosition;

extern region* targetRegionPosition;

extern int currentRegion;

#endif