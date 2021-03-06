// WorldGen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include "world.h"
#include "grid.h"
#include "square.h"

/*
Given the parameters generates the random world, generating things in order.
Gasses (savegery increases oxygen, inhabitable worlds have things lost, hotter worlds more greenhouse)
All parameter based.
Can change overtime w flora???
Landmasses/Elevation (Valid configuration, may all be water dependent on configuration)
Diamond-square algorithim

Height is on a scale from 0-10.
0-5 on earth like planets, water.
6 - low level/sea level land. beaches.
7-8 - normal level land
9 - highlands, valleys
10 - mountains

Everything not above SEA_LEVEL is water.
SEA_LEVEL is set to whatever fills in WATER_PERCENT parameter.
E.G. 71% for earth-like elevations means SEA_LEVEL will be ~0.

Weather (Based on elevation, gasses, and temperatures. Most advanced interactions here)
First generates temperatures based on equator, water, and gasses (savagery, parameter, etc)
Temperate zones
Temperature of individual places
Creates the "wind" thread that the world view will display. Warm air and cold air moving appropriately.
Assuming same spin and axis as Earth - Advanced Parameter later??
Generates a sort of precipitation based on gasses (acidic) and elevation
LOTS of interaction here.
Temperature and mountains can cause deserts vs temperate lands.
Tornadoes on flatter lands held in by mountains in certain zones.
High rainfall vs low rainfall
Generates bodies of water - mostly Biome tier level.
Enough water makes a "sea" world tile
Placing rivers in random configurations until it works seems like best option.??
*World tier is now a series of mountains, water, or flatlands*
Generates "biomes"
Temperature, water, and elevation selects an appropriate biome for world tier square. E.G. Desert
Biome squares filled out from there. E.G. Dunes, Oasis, Valley, Kingdom.
World square update check for defining feature.
Should still be DESERT - most of the time, unless lots of water, or something.
Entity squares randomly filled out based on likelyhood chart.
E.G. In a DUNES, ~90% chance the tile is sand. Could also be den, sandstone, etc.

Places entities.
If Planet canSustainLife (Valid parameters (All green or yellow))
//DEPENDS ON HOW ADVANCED INTERACTIONS WILL BE - Entitiese need to hunt? e
(Based on gasses)
Higher oxygen, from lush plant live, high savagery, or appropriate temperatures causes GIANTs
Also makes higher elevations livable and lower not.
(Based on biome)
Different BEASTS for biomes.

Kingdoms are randomly placed, and only heroes are independently tracked?

Time and seasons - EVENTS


Will attempt building a UI using tools - but currently, a command-line interface is fine.


*/

//Parameters: DIstance from sun, mass of sun?, mass of planet, size of planet, temperature range?, pref biomes?, gaseous makeup?, savagery?, greenhouse gas effect?
//World object w different constructors for a d v a n c e d parameters?

/*Target temperature - Celsius, determined by sun, albedo, greenhouse gasses.

*/

/*
Given parameters, generates a world
Depreceated:
int distanceFromSun, int massRelativeToEarth, int sizeRelativeToEarth, int sizeOfSun
Parameters:
int greenhouse - Target greenhouse effect
int savagery - Aggresiveness of entities, also increases oxygen content - assuming planet is habitable
int temperature - target temperature of planet ? 7 options. frozen - normal - burning. At burning no atmosphere is possible. At frozen all liquids are ice.
int seaLevel -
*/

//Info for type of square. 
char WATER_CHAR = '~';
std::string WATER_DESC = "Splish Splash.";


//globals that I probably shouldn't have but my design has fallen apart anyway so deal with it maybe I'll clean it up one day?
bool HIGH_OXYGEN = false;
bool LOW_OXYGEN = false;

int main()
{
	srand(time(NULL));
	generateWorld(0, 0, 0, 0);
}


int gridSize = 81;
int rowSize = 9;

//advanced parameters include: bond albedo (determining makeup of planet), greenhouse gasses, size of sun, distance of sun (all to calculate temp), Atmospheric pressure at sea level

Grid * generateWorld(int temperature, int savagery, int greenhouse, int seaLevel) {
	
	//Initialize an 'empty' world - World grid, 81 biome grids, each with 81 entitySquares.
	Grid * worldGrid = &Grid();
	std::cout << "Succesfully generated World Grid." << std::endl;
	for (int i = 0; i < gridSize; ++i) {
		Square biomeSq = worldGrid->getSquareAtIndex(i);
		std::cout << "Succesfully generated Entity Grid #" << i << std::endl;
		for (int j = 0; j < gridSize; ++j) {
			biomeSq.setGrid(&Grid());
		}
	}
	std::cout << "Succesfully generated Entity Squares." << std::endl;

	//initialize four corners
	initializeSquare(0, worldGrid);
	initializeSquare(rowSize - 1, worldGrid);
	initializeSquare(gridSize - rowSize, worldGrid);
	initializeSquare(gridSize - 1, worldGrid);
	//use diamond-square to generate a heightmap landscape
	std::cout << "Succesfully Init corners." << std::endl;
	std::cout << "Corners are: " << std::endl;

	std::cout << worldGrid->getSquareAtIndex(0).getHeight() << std::endl;
	std::cout << worldGrid->getSquareAtIndex(8).getHeight() << std::endl;
	std::cout << worldGrid->getSquareAtIndex(72).getHeight() << std::endl;
	std::cout << worldGrid->getSquareAtIndex(80).getHeight() << std::endl;

	diamondSquare(worldGrid, rowSize);
	std::cout << "Succesfully crafted Landscape." << std::endl;
	
	//temperature is determined by distance from sun, gaseous makeup, and bond albedo. Need an atmosphere.

	std::cout << "Layering the atmosphere." << std::endl;

	int atmos = 1; //Atmospheric pressure at sea level. Only changed with advanced parameters. 
	int add = savagery * 2; //Only savagery affects the add parameter - more advanced ones have influence.
	

	generateGasses(temperature, atmos, add);

	//temp determines water level. Normal means 3 or 4. Hot means 2 or 3. Desert means 1. Ice means replace all water with ice (-1)
	//cooler temperature will mean more water is frozen, just during climate instead of filling ocean phase.
	int waterLevel = determineWaterLevel(temperature);
	fillOceans(worldGrid, waterLevel);
	
	createClimate();
	
	//int temp = calcMeanTemp(distanceFromSun, sizeOfSun);

	
	//calcAtmosPres(300);

	for (int i = 0; i < gridSize; ++i) {
		std::cout << "Square: #" << i << " Height: "<< worldGrid->getSquareAtIndex(i).getHeight() << std::endl;
	}
	return worldGrid;
}


/*
Impelments a diamond-square algorithim to 'generate' a heightmap landscape for the world.
Each square in the grid will be set to a height.
*/
void diamondSquare(Grid *worldGrid, int size)
{
	
	int mid = size/2;
	std::cout << "Mid is equal to: " << mid << std::endl;
	if (mid < 1)
		return;
	//square steps
	for (int z = mid; z < rowSize; z += size)
		for (int x = mid; x < rowSize; x += size)
			squareStep(worldGrid, x % rowSize, z %rowSize, mid);
	// diamond steps
	int col = 0;
	for (int x = 0; x < rowSize; x += mid)
	{
		col++;
		//If this is an odd column.
		if (col % 2 == 1)
			for (int z = mid; z < rowSize; z += size)
				diamondStep(worldGrid, x % rowSize, z % rowSize, mid);
		else
			for (int z = 0; z < rowSize; z += size)
				diamondStep(worldGrid, x % rowSize, z % rowSize, mid);
	}
	diamondSquare(worldGrid, size / 2);
}

void squareStep(Grid *worldGrid, int x, int z, int reach) //8 & 4 on second pass????
{
	std::cout << "Performing Square Step." << std::endl;
	int count = 0;
	int avg = 0;
	if (x - reach >= 0 && z - reach >= 0)
	{
		std::cout << "Reaching square #" << (rowSize * (x - reach)) + (z - reach) << std::endl;
		avg += worldGrid->getSquareAtIndex((rowSize * (x - reach)) + (z - reach)).getHeight();
		//avg += Array[x - reach][z - reach];
		count++;
	}
	if (x - reach >= 0 && z + reach < rowSize)
	{
		std::cout << "Reaching square #" << (rowSize * (x - reach)) + (z + reach) << std::endl;
		avg += worldGrid->getSquareAtIndex((rowSize * (x - reach)) + (z + reach)).getHeight();
		count++;
	}
	if (x + reach < rowSize && z - reach >= 0)
	{
		std::cout << "Reaching square #" << (rowSize * (x + reach)) + (z - reach) << std::endl;
		avg += worldGrid->getSquareAtIndex((rowSize * (x + reach)) + (z - reach)).getHeight();
		count++;
	}
	if (x + reach < rowSize && z + reach < rowSize)
	{
		std::cout << "Reaching square #" << (rowSize * (x + reach)) + (z + reach) << std::endl;
		avg += worldGrid->getSquareAtIndex((rowSize * (x + reach)) + (z + reach)).getHeight();
		count++;
	}
	std::cout << "Sum is: " << avg << std::endl;
	//avg += (rand() % (reach * 2)) - reach;
	avg /= count;
	std::cout << "Height set to " << avg << " at Square #" << ((rowSize * x) + z) << std::endl;
	worldGrid->getSquareAtIndex((rowSize * x) + z).updateHeight(avg);
}

void diamondStep(Grid *worldGrid, int x, int z, int reach)
{
	std::cout << "Performing Diamond Step." << std::endl;
	int count = 0;
	int avg = 0;
	if (x - reach >= 0)
	{
		std::cout << "Reaching square #" << (rowSize * (x - reach)) + (z) << std::endl;
		avg += worldGrid->getSquareAtIndex((rowSize * (x - reach)) + z).getHeight();
		count++;
	}
	if (x + reach < rowSize)
	{
		std::cout << "Reaching square #" << (rowSize * (x + reach)) + (z) << std::endl;
		avg += worldGrid->getSquareAtIndex((rowSize * (x + reach)) + z).getHeight();
		count++;
	}
	if (z - reach >= 0)
	{
		std::cout << "Reaching square #" << (rowSize * x) + (z - reach) << std::endl;
		avg += worldGrid->getSquareAtIndex((rowSize * x) + (z - reach)).getHeight();
		count++;
	}
	if (z + reach < rowSize)
	{
		std::cout << "Reaching square #" << (rowSize * (x)) + (z + reach) << std::endl;
		avg += worldGrid->getSquareAtIndex((rowSize * x) + (z + reach)).getHeight();
		count++;
	}
	std::cout << "Sum is: " << avg << std::endl;
	//avg += (rand() % (reach * 2)) - reach;
	avg /= count;
	std::cout << "Height set to " << avg << " at Square #" << ((rowSize * x) + z) << std::endl;
	worldGrid->getSquareAtIndex((rowSize * x) + z).updateHeight(avg);
}

//Helper for diamond square - initializes grids corners to be 
int initializeSquare(int h, Grid *g) {
	int height = rand() % 10;
	g->getSquareAtIndex(h).updateHeight(height);
	return height;
}

//Literally just puts water where its supposed to be. Sea level. And stuff.
void fillOceans(Grid * worldGrid, int waterLevel) {
	std::cout << "Filling in oceans" << std::endl;
	for (int i = 0; i < gridSize; i++) {
		if (worldGrid->getSquareAtIndex(i).getHeight() < waterLevel) {
			worldGrid->getSquareAtIndex(i).updateGraphic(WATER_CHAR);
			worldGrid->getSquareAtIndex(i).updateDesc(WATER_DESC);
		}
	}
}

/*
Waterlevel is dependent on randomization and temperature.
*/
int determineWaterLevel(int temperature) {
	int waterLevel = -2;
	if (temperature == 0) {
		waterLevel = -1;
	}
	else if (temperature == 3) {
		int coinFlip = rand() % 1;
		if (coinFlip == 1) {
			waterLevel = 3;
		}
		else {
			waterLevel = 4;
		}
	}
	else if (temperature == 4) {
		int coinFlip = rand() % 1;
		if (coinFlip == 1) {
			waterLevel = 2;
		}
		else {
			waterLevel = 3;
		}
	}
	else if (temperature == 5) {
		waterLevel = 1;
	}
	else if (temperature == 6) {
		waterLevel = 0;
	}
	return waterLevel;
}

/*
Generates the world's general gaseous makeup.
Parameters determine ranges for possible gaseous makeup, which are selected at random
These selections result in some possible effects:
Inhabitable - Air is poisonous or too heavy/light to breathe, or not made up of breathable elements
HighOxygen - Air at low levels is poisonous, air is available at high altitudes, and creatures are more often larger. More prone to fires.
LowOxtgen - Breathable air only at low elevations, smaller creatures. Less prone to fires.
HighPressure - More intense weather
LowPressure - Less intense weather
*/
double generateGasses(int temp, double atmPress, int add) {
	if (temp == 6) {
		//set world to inhabitable - gasses escape at this temperature.
	}
	else {

		double v = (double)(rand() % (10000)) / 10000.0; //randomization factor 

		double N = (v + 78);
		double A = (.9 - v);
		double O = (100.0 - N - A);

		if (O > 25.0) {
			//set high oxygen, and update global oxygen parameter
			HIGH_OXYGEN = true;
		}
		else if (O < 18.0) {
			//set low oxygen, and update global oxygen parameter
			LOW_OXYGEN = false;
		}
		return O;
		//otherwise keep normal
	}
}

/*
Uses a function to calculate the atmospheric pressure at a given square - by using the gasses and elevation.
More oxygen, a heavier atmosphere, causing events and interactions at certain elevations.
*/
int calcAtmosPres(int altitude) {
	//atmp*exp(-(altitude) / scaleHeight)
	//exp = e^(); ~2.178

	//scale height = 8.3144598 * temp / .028949469
	//scale constant, atomic weight constant
	return 1;
}

/*
The mean temperature across a planets surface is ~Luminosity^1/4 / Distance^1/2, assuming a similar gaseous makeup.

int calcMeantemp(int d, int s) {
int l = sqrt(s);
int di = sqrt(d);

return l / di;
}

*/

void createClimate(int temp) {
	/*
	Weather(Based on elevation, gasses, and temperatures. Most advanced interactions here)
	First generates temperatures based on equator, water, and gasses(savagery, parameter, etc)
	Temperate zones
	Temperature of individual places
	Creates the "wind" thread that the world view will display.Warm air and cold air moving appropriately.
	Assuming same spin and axis as Earth - Advanced Parameter later ? ?
	Generates a sort of precipitation based on gasses(acidic) and elevation
	LOTS of interaction here.
	Temperature and mountains can cause deserts vs temperate lands.
	Tornadoes on flatter lands held in by mountains in certain zones.
	High rainfall vs low rainfall

	If square index past 4th row on world grid is south, before is north, 4th row is equator.

	Climate is mostly based on temperature and rainfall.
	*/

	genTemperateZones(temp);


}

void genTemperateZones(int temp) {
	//Define normal, and expand/contract zones as necessary

	//temp = 3
	//Breakdown: N Frigid 1, N Temp 2, Torrid N 1, Equator(Tropic 1), Torrid S 1, S Temp 2, S Frigid 1. 
	if (temp == 3) {
		//Frigid sone = ~10%
		for (int i = 0; i < rowSize; ++i) {

		}
		for (int j = 0; j < rowSize * 2; ++j) {

		}
		for (int k = 0; j < rowSize * 3; ++k) {

		}
	}
}