#pragma once
#include <bits/stdc++.h>
#include <string>
#include <iostream> 
#include <list> 
#include <iterator> 

class Square;
class Grid;

/*
class World
{
public:
//various parameters you can use for world generations
World();
};
*/

Grid * generateWorld(int temperature, int savagery, int greenhouse, int seaLevel);
void diamondSquare(Grid *worldGrid, int size);
void squareStep(Grid *worldGrid, int x, int z, int reach);
void diamondStep(Grid *worldGrid, int x, int z, int reach);
int initializeSquare(int h, Grid *g);
double generateGasses(double temp, double atmPress, int add);
int determineWaterLevel(int temperature);
void fillOceans(Grid * worldGrid, int waterLevel);
void createClimate(int temp);
void genTemperateZones(int temp);