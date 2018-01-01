#ifndef _TEST_
#define _TEST_

#include "State.h"

class Test : public State
{
	/***** ATTRIBUTES *****/
protected:
	/***** CONSTRUCTOR / DESTRUCTOR *****/
public:
	Test();
	~Test();

	/***** METHODS *****/
public:
	void run();
	void update();
	void render();
};

#endif