#pragma once
#include <bits/stdc++.h>
#include <string>
#include <iostream>
#include <list>
#include <iterator>

class Square;
enum climate;

class Grid {
public:

	Square * g;

	Grid();
	Grid(Square *arr);

	Square* &getG();
	Square &getSquareAtIndex(int i);
	void display();
	int calcFood();
	climate calcClim();
};
