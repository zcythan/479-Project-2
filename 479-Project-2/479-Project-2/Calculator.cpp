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

void Calculator::prediction(int dir) {
	// dir: 1 = W, 2 = N, 3 = E, 4 = S
	vector<string> openIds = maze.getOpenIds();
	// Resetting probability container
	for (string id : openIds) {
		for (int i = 0; i < sizeof(4) / sizeof(char); i++) {
			maze.updateProb(id, 1);
		}
	}
	// 1 = W, 2 = N, 3 = E, 4 = S
	bool edges[4];

	vector<double> newProbs;
	// Chances that our robot will go each direction, L S R
	double pNoBounce[3] = {0.15, 0.75, 0.1};

	for (string id : openIds) {
		// Probability of successful move
		double mProb = 0;
		for (int i = 0; i < sizeof(4) / sizeof(char); i++) {
			for (int j = 1; j < 4; j++) {
				edges[j] = maze.isEdge(id, j);
			}
			
		}
		newProbs.push_back(mProb);
	}
	newProbs = normalize(newProbs);
	for (int i = 0; i < openIds.size(); i++) {
		maze.updateProb(openIds[i], newProbs[i]);
	}
}

void Calculator::printMaze() {
	maze.print();
}