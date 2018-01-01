#pragma once
#include <stdio.h>
#include <iostream>
#include "TextBox.h"

class Intro : public State
{
	/***** ATTRIBUTES *****/
public:

private:
	std::string welcomeText2;
	std::string welcomeText3;
	std::string welcomeText;

public:
	/***** CONSTRUCTOR / DESTRUCTOR *****/
	/// The default constructor
	Intro();

	/// The destructor.  
	~Intro();

	/***** METHODS *****/
public:
	void run();
	void update();
	void render();
};