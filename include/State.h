#ifndef _STATE_
#define _STATE_

#include "stdafx.h"
#include "libtcod.hpp"

class State
{
	/***** ATTRIBUTES *****/
protected:
	std::string enterText = "Press ENTER to continue!";
	bool toQuit;
	/***** CONSTRUCTOR / DESTRUCTOR *****/

	/***** METHODS *****/
public:
	virtual void run() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};

#endif 
