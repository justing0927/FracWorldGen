#pragma once
#include "stdafx.h"
#include "grid.h"
#include "square.h"
/*
Displayes the current list of 10x10 squares. Starting at world tier.
Ui allows to select squares to see a short description, or switch the grid view to that square
Meaning, display that square's 100 squares in the grid.
This is most of the OPEN GL stuff - displaying these symbols in a grid.
Can also support a:
Border view -
Weather view - Show winds and weather.

3D VIEW MODEL OF WORLD???
*/

Grid::Grid() {
	g = new Square[81];
	for (int i = 0; i < 81; ++i) {
		g[i] = Square(i);
	}
}

Grid::Grid(Square *arr) {
	g = arr;
}

Square* &Grid::getG() {
	return this->g;
}

Square &Grid::getSquareAtIndex(int i) {
	return this->g[i];
}

void Grid::display() {
	for (int i = 0; i < 81; ++i) {
		Square sq = getSquareAtIndex(i);
	}
}

int Grid::calcFood() {
	int sum = 0;
	for (int i = 0; i < 81; ++i) {
		Square sq = getSquareAtIndex(i);
		sum += sq.getFoodVal();
	}
	sum /= 81;
	return sum;
}

climate Grid::calcClim() {
	int arr[13];
	for (int j = 0; j < 13; ++j) {
		arr[j] = 0;
	}
	climate temp;
	int k = -1;
	int max = 0;
	for (int i = 0; i < 81; ++i) {
		Square sq = getSquareAtIndex(i);
		temp = sq.getClimate();
		switch (temp)
		{
		case TropicalDry:
			arr[0] += 1;
			if (arr[0] > max) {
				max = arr[0];
				k = 0;
			}
			break;
		case TropicalWet:
			arr[1] += 1;
			if (arr[1] > max) {
				max = arr[1];
				k = 1;
			}
			break;
		case TropicalMonsoon:
			arr[2] += 1;
			if (arr[2] > max) {
				max = arr[2];
				k = 2;
			}
			break;
		case MildHumid:
			arr[3] += 1;
			if (arr[3] > max) {
				max = arr[3];
				k = 3;
			}
			break;
		case MildMarine:
			arr[4] += 1;
			if (arr[4] > max) {
				max = arr[4];
				k = 4;
			}
			break;
		case MildMedi:
			arr[5] += 1;
			if (arr[5] > max) {
				max = arr[50];
				k = 5;
			}
			break;
		case ContiCool:
			arr[6] += 1;
			if (arr[6] > max) {
				max = arr[6];
				k = 6;
			}
			break;
		case ContiWarm:
			arr[7] += 1;
			if (arr[7] > max) {
				max = arr[7];
				k = 7;
			}
			break;
		case ContiSubartic:
			arr[8] += 1;
			if (arr[8] > max) {
				max = arr[8];
				k = 8;
			}
			break;
		case PolarIce:
			arr[9] += 1;
			if (arr[9] > max) {
				max = arr[9];
				k = 9;
			}
			break;
		case PolarTundra:
			arr[10] += 1;
			if (arr[10] > max) {
				max = arr[10];
				k = 10;
			}
			break;
		case DryArid:
			arr[11] += 1;
			if (arr[11] > max) {
				max = arr[11];
				k = 11;
			}
			break;
		case DrySemi:
			arr[12] += 1;
			if (arr[12] > max) {
				max = arr[12];
				k = 12;
			}
			break;
		}
	}
	switch (k) {
	case 0:
		return TropicalDry;
		break;
	case 1:
		return TropicalWet;
		break;
	case 2:
		return TropicalMonsoon;
		break;
	case 3:
		return MildHumid;
		break;
	case 4:
		return MildMarine;
		break;
	case 5:
		return MildMedi;
		break;
	case 6:
		return ContiCool;
		break;
	case 7:
		return ContiWarm;
		break;
	case 8:
		return ContiSubartic;
		break;
	case 9:
		return PolarIce;
		break;
	case 10:
		return PolarTundra;
		break;
	case 11:
		return DryArid;
		break;
	case 12:
		return DrySemi;
		break;
	}
}