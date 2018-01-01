#pragma once
#include "stdafx.h"
#include "libtcod.hpp"

void drawBox(int x, int y, int w, int h, bool isColored = false, const TCODColor & col = TCODColor::red);
void backgroundFill(int x, int y, int w, int h, const TCODColor & col);
void fillWithChar(int x, int y, int w, int h, char c, bool isColored = false, const TCODColor & col = TCODColor::red);
void drawEntireBox(int x, int y, int w, int h, TCODColor borderCol, TCODColor fillColor);
void drawWater();