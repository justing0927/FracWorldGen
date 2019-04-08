
#pragma once
#include "stdafx.h"
#include <bits/stdc++.h>
#include <iostream> 
#include <list> 
#include <iterator> 
#include "square.h"
#include "grid.h"

/*
So a 10x10 sheet of squares makes up the currently displayed "Grid" - each square has its own display.
That Grid is sorta the view.
This is a sorta fractal project so a square is made up of other squares that form a grid.
So every square contains a list of 100 squares that make it up, forming another grid.
This has a total of three tiers: World, biome, and entity.
So every square of the world tier is made up of a 100 squares of the biome tier, each made up of 100 squares
of the entity tier.

Different things also interact at the world tier that influence the tiers below it, and vice versa.

A square itself thus always has:
A symbol representing the defining characteristic of a square - e.g. A ^ for a mountain.
A world tier square, made up of mostly high elevation rock, is a mountain.
It could theoretically be mined or destroyed to become a flat, or populated to become a Kingdom.
These symbols obviously change by tier, mountains, hills, entities themselves.
These symbols update as either entities interact with them, or their composite squares change.
A location - their spot in a grid.
A description of the square (its symbol).
Squares also have:
A list of 100 squares that make it up (World and Biome tier)
Food level - varies leading to entities thriving or starving, attacking, etc.
Climate - The current weather in the area. World level has a variety in weather to account for seasons.
Gasses - Affects the entities. Oxygen can lead to higher growth or poison. CO2 can choke out life. Affected
by weather and events - such as volcanoes. Can also influence weather?

Some of these values, in the cases of Biome and World Squares are the average of their grids' squares.

*/

char DIRT_CHAR = 'D';
std::string DIRT_DESC = "Loose earth.";

Square::Square() : graphic(' '), loc(-1), height(0), desc("The Final Frontier"), food(0), clim(MildHumid) {}

Square::Square(int i) : graphic(' '), loc(i), height(0), desc("The Final Frontier"), food(0), clim(MildHumid) {}

Square::Square(char c, int x, int y, int h, std::string d, Grid* g, int f, climate cl, tempZone z) : graphic(c), loc(x), height(h), desc(d), grid(g), food(f), clim(cl), zone(z) {}

void Square::updateGraphic(char g) {
	//synchronize threads
	this->graphic = g;
	//update
}

void Square::updateDesc(std::string str) {
	//synch
	this->desc = str;
	//update
}

/*
void populateGrid() {
for (int i = 0; i < 400; ++i) {
this->grid.push_back(Square(DIRT_CHAR, i, DIRT_DESC, ));
}
}
*/

Grid* &Square::getGrid() {
	return grid;
}
void Square::setGrid(Grid *g) {
	grid = g;
}
char &Square::getGraphic() { return graphic; }
int &Square::getIndex() { return loc; }
int &Square::getHeight() { return height; }
void Square::updateHeight(int h) { height = h; }
std::string &Square::getDesc() { return desc; }
int &Square::getFoodVal() { return food; }
climate &Square::getClimate() { return clim; }
tempZone &Square::getZone() { return zone; }