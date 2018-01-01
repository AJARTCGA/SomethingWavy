#pragma once
#include <stdio.h>
#include <iostream>
#include "State.h"

class TextBox : public State
{
	/***** ATTRIBUTES *****/
public:

public:
	/***** CONSTRUCTOR / DESTRUCTOR *****/
	/// The default constructor
	TextBox();

	/// The destructor.  
	~TextBox();

	/***** METHODS *****/
public:
	virtual void run();
	virtual void update();
	virtual void render() = 0;
};