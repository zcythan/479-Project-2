#pragma once
#include "Maze.h"

using namespace std;

class Agent {
private:
	//constants for probabilities.
	const double seeObsCor = 0.9;
	const double seeObsInCor = 0.05;
	const double seeNoObsCor = 0.95;
	const double seeNoObsInCor = 0.10;
	const double straight = 0.75;
	const double dLeft = 0.15;
	const double dRight = 0.10;
	Maze maze;
	vector<double> normalize(vector<double> probs);
	char getOpp(char dir);
	char getLeft(char dir);
	char getRight(char dir);

public:
	Agent();
	void filter(vector<int> data);
	void printMaze();
	void predict(char dir);
	double getSum();
};