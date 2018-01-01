#pragma once
#include <vector>
#include <map>
#include "Singleton.h"
#include "Entity.h"

#define BOAT Watercraft::getSingletonPtr()

class Watercraft : public Singleton<Watercraft>
{
private:
	std::vector <bool> mShape;
	//std::vector <char> mPropMap;
	std::map <int, Entity*> mPropMap;
	int mWidth, mHeight;
	std::vector<Entity*> mWormCrates;
public:
	Watercraft(int w, int h);
	~Watercraft();
	bool getFloorBool(int x, int y);
	int getWidth();
	int getHeight();
	void draw(int x, int y);
	Entity * getProp(int x, int y);
	void placeProp(int x, int y, Entity * e);
	void removeProp(int x, int y);
	void update();
protected:
	void drawProps(int x, int y);
};