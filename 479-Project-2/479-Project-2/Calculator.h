#pragma once
#include "Maze.h"

using namespace std;

class Calculator {
private:
	Maze maze;
	//constants for probabilities.
	const float seeObsCor = 0.9;
	const float seeObsInCor = 0.05;
	const float seeNoObsCor = 0.95;
	const float seeNoObsInCor = 0.10;
	const float straight = 0.75;
	const float dLeft = 0.15;
	const float dRight = 0.10;

public:
	Calculator();
	void getInitProb();

	//functions that will be used to calculate distributions will live here and will reference the maze variable for current maze state.
};