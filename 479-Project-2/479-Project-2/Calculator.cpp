#include "Calculator.h"

Calculator::Calculator() {
	maze = Maze();
}

void Calculator::getInitProb() {
	int data[4] = { 1, 0, 0, 1 };
	//gets vector of all tile Ids that are unblocked.
	//It will produce a corresponding vector of new probabilities given sensing data.
	vector<string> openIds = maze.getOpenIds();


}