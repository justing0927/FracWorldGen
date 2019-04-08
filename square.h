#pragma once
#include <bits/stdc++.h>
#include <string>
#include <iostream> 
#include <list> 
#include <iterator> 

class Grid;

enum climate {
	TropicalWet, TropicalMonsoon, TropicalDry, DryArid, DrySemi, MildMedi, MildHumid, MildMarine, ContiWarm,
	ContiCool, ContiSubartic, PolarTundra, PolarIce
};

enum tempZone { //Köppen climate classification is more specific but less useful for this mayhaps? I don't know
	Frigid, Temperate, Subtropic, Tropic //Torrid instead of tropics ?
};

class Square
{
public:

	char graphic; //representation of Square in-simulation
	int loc; //index in current Grid
	int height;
	std::string desc; //Description for square.

	Grid *grid;

	int food;
	climate clim;
	tempZone zone;

	Square();
	Square(int i);
	Square(char c, int x, int y, int h, std::string d, Grid* g, int f, climate cl, tempZone z);

	void updateGraphic(char g);

	void updateDesc(std::string str);

	/*
	void populateGrid() {
	for (int i = 0; i < 400; ++i) {
	this->grid.push_back(Square(DIRT_CHAR, i, DIRT_DESC, ));
	}
	}
	*/
	void setGrid(Grid *g);
	Grid* & getGrid();
	char & getGraphic();
	int & getIndex();
	int & getHeight();
	void updateHeight(int h);
	std::string & getDesc();
	int & getFoodVal();
	climate & getClimate();
	tempZone & getZone();
};