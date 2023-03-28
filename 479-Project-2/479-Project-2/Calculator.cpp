#include "Calculator.h"

Calculator::Calculator() {
	maze = Maze();
}

// Turns all probabilities of a given type into 
vector<double> Calculator::normalize(vector<double> probs) {
	double sum = 0;
	for (double prob : probs) {
		sum = sum + prob;
	}
	for (int i = 0; i < probs.size(); i++) {
		probs[i] = (probs[i] / sum)*100;
	}
	return probs;
}

//It will produce a corresponding vector of new probabilities given sensing data.
void Calculator::filter(vector<int> data) {
	char dirKey[4] = { 'w', 'n', 'e', 's' };
	//gets vector of all tile Ids that are unblocked.
	vector<string> openIds = maze.getOpenIds();
	vector<double> newProbs;

	for (string id : openIds) {
		//calculate the new probability here based on sensor data.
		double tProb = 0;
		for (int i = 0; i < sizeof(dirKey) / sizeof(char); i++) {
			//If it senses no obstical and is correct.
			if (maze.checkObs(id, dirKey[i]) == static_cast<bool>(data[i]) && data[i] == 0) {
				if (tProb == 0) {
					tProb = seeNoObsCor;
				}
				else {
					tProb = tProb * seeNoObsCor;
				}
			}
			//If it senses obstical and is correct.
			else if (maze.checkObs(id, dirKey[i]) == static_cast<bool>(data[i]) && data[i] == 1) {
				if (tProb == 0) {
					tProb = seeObsCor;
				}
				else {
					tProb = tProb * seeObsCor;
				}
			}
			//If it senses obstical and is incorrect.
			else if (maze.checkObs(id, dirKey[i]) != static_cast<bool>(data[i]) && data[i] == 1) {
				if (tProb == 0) {
					tProb = seeObsInCor;
				}
				else {
					tProb = tProb * seeObsInCor;
				}
			}
			//If it senses no obstical and is incorrect.
			else if (maze.checkObs(id, dirKey[i]) != static_cast<bool>(data[i]) && data[i] == 0) {
				if (tProb == 0) {
					tProb = seeNoObsInCor;
				}
				else {
					tProb = tProb * seeNoObsInCor;
				}
			}
		}
		newProbs.push_back(tProb);
	}
	//here we normalize
	newProbs = normalize(newProbs);
	//update maze
	for (int i = 0; i < openIds.size(); i++) {
		maze.updateProb(openIds[i], newProbs[i]);
	}
}

void Calculator::prediction(char dir) {
	// dir: 1 = W, 2 = N, 3 = E, 4 = S
	vector<string> openIds = maze.getOpenIds();
	// Resetting probability container
	for (string id : openIds) {
		maze.updateProb(id, 1);
	}
	// 1 = W, 2 = N, 3 = E, 4 = S
	double oldProb = 0;

	char left = '\0', right = '\0', straight = '\0';
	switch (dir) {
		// We are going west
	case 'w':
		left = 's', right = 'n', straight = 'w';
		break;
		// Going north
	case 'n':
		left = 'w', right = 'e', straight = 'n';
		break;
		// going east
	case 'e':
		left = 'n', right = 's', straight = 'e';
		break;
		// going south
	case 's':
		left = 'e', right = 'w', straight = 's';
		break;
	}

	vector<double> newProbs;
	// Chances that our robot will go each direction, L S R
	double pNoBounce[3] = {0.15, 0.75, 0.1};
	string neighbor = "\0";
	for (string id : openIds) {
		// Probability of successful move
		double mProb = 0;
		for (int i = 1; i < 4; i++) {
			/*for (int j = 1; j < 4; j++) {
				edges[j] = maze.isEdge(id, j);
			}
			*/
			if (maze.checkObs(id, left)) {
				// neighbor's probability goes up by prob*0.15
				neighbor = maze.getNeighbor(id, dir);
				maze.updateProb(neighbor, maze.getProb(neighbor) * 0.15);
			}
			else {
				neighbor = maze.getNeighbor(id, dir);
				maze.updateProb(id, maze.getProb(id) * 0.15);
			}
			if (maze.checkObs(id, right)) {
				// neighbor's probability goes up
				neighbor = maze.getNeighbor(id, dir);
				maze.updateProb(neighbor, maze.getProb(neighbor) * 0.1);
			}
			else {
				neighbor = maze.getNeighbor(id, dir);
				maze.updateProb(id, maze.getProb(id) * 0.1);
			}
			if (maze.checkObs(id, straight)) {
				// neighbor's probability goes up 
				neighbor = maze.getNeighbor(id, dir);
				maze.updateProb(neighbor, maze.getProb(neighbor) * 0.75);
			}
			else {
				neighbor = maze.getNeighbor(id, dir);
				maze.updateProb(id, maze.getProb(id) * 0.75);
			}
		}
	}
	for (string id : openIds) {
		newProbs.push_back(maze.getProb(id));
	}

		newProbs = normalize(newProbs);
	for (int i = 0; i < openIds.size(); i++) {
		maze.updateProb(openIds[i], newProbs[i]);
	}
}

void Calculator::printMaze() {
	maze.print();
}