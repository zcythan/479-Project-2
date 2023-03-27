#pragma once
#include "Maze.h"

using namespace std;

class Calculator {
private:
	Maze maze;
	//constants for probabilities.
	const double seeObsCor = 0.9;
	const double seeObsInCor = 0.05;
	const double seeNoObsCor = 0.95;
	const double seeNoObsInCor = 0.10;
	const double straight = 0.75;
	const double dLeft = 0.15;
	const double dRight = 0.10;
	vector<double> normalize(vector<double> probs);

public:
	Calculator();
	void filter(int data[4]);
	void printMaze();
	
	//functions that will be used to calculate distributions will live here and will reference the maze variable for current maze state.
};