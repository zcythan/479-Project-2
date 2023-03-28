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
		if (tProb == 1)
			tProb = 0;
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

	// All std::couts are for debugging 

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
		std::cout << "I am " << id << ", my left: ";

		neighbor = maze.getNeighbor(id, left);
		maze.updateProb(neighbor, (maze.getProb(id) * 0.15));
		std::cout << neighbor << ", Right: ";

		neighbor = maze.getNeighbor(id, right);
		maze.updateProb(neighbor, (maze.getProb(id) * 0.1));
		std::cout << neighbor << ", Forward: ";

		neighbor = maze.getNeighbor(id, straight);
		maze.updateProb(neighbor, (maze.getProb(id) * 0.15));
		std::cout << neighbor << ".\n";

		//for (int i = 1; i < 4; i++) {
			/*for (int j = 1; j < 4; j++) {
				edges[j] = maze.isEdge(id, j);
			}
			*/
			//If it senses no obstical and is correct.

			/*
			std::cout << "My ID is: " << id << ", Turning " << dir << "." << std::endl;
			std::cout << "My left: ";
			if (maze.checkObs(id, left)) {
				std::cout << "Self; Right: ";
				//neighbor = maze.getNeighbor(id, dir);
				maze.updateProb(id, maze.getProb(id) * 0.15);
			}
			else {
				// neighbor's probability goes up by prob*0.15
				neighbor = maze.getNeighbor(id, dir);
				std::cout << neighbor << "; Right:";
				maze.updateProb(neighbor, maze.getProb(neighbor) * 0.15);
			}
			if (maze.checkObs(id, right)) {
				std::cout << "Self; Front: ";
				//neighbor = maze.getNeighbor(id, dir);
				maze.updateProb(id, maze.getProb(id) * 0.1);
			}
			else {

				// neighbor's probability goes up
				neighbor = maze.getNeighbor(id, dir);
				std::cout << neighbor << "; front:";
				maze.updateProb(neighbor, maze.getProb(neighbor) * 0.1);
			}
			if (maze.checkObs(id, straight)) {
				std::cout << " self\n";
				//neighbor = maze.getNeighbor(id, dir);
				maze.updateProb(id, maze.getProb(id) * 0.75);
			}
			else {
				// neighbor's probability goes up 
				neighbor = maze.getNeighbor(id, dir);
				std::cout << neighbor << ".\n";
				maze.updateProb(neighbor, maze.getProb(neighbor) * 0.75);
			}
			*/
		//}
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