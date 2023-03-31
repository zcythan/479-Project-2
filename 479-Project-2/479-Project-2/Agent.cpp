#include "Agent.h"

Agent::Agent() {
	maze = Maze();
}

//Returns character opposing given direction.
char Agent::getOpp(char dir) {
	if (dir == 'n') {
		return 's';
	}
	if (dir == 's') {
		return 'n';
	}
	if (dir == 'e') {
		return 'w';
	}
	if (dir == 'w') {
		return 'e';
	}
}

//Returns character to the left of given direction.
char Agent::getLeft(char dir) {
	if (dir == 'n') {
		return 'w';
	}
	if (dir == 's') {
		return 'e';
	}
	if (dir == 'e') {
		return 'n';
	}
	if (dir == 'w') {
		return 's';
	}
}

//Returns character to the right of given direction.
char Agent::getRight(char dir) {
	if (dir == 'n') {
		return 'e';
	}
	if (dir == 's') {
		return 'w';
	}
	if (dir == 'e') {
		return 's';
	}
	if (dir == 'w') {
		return 'n';
	}
}

// Turns all probabilities of a given type into a normalized distribution.
vector<double> Agent::normalize(vector<double> probs) {
	double sum = 0;
	for (double prob : probs) {
		sum = sum + prob;
	}
	for (int i = 0; i < probs.size(); i++) {
		probs[i] = (probs[i] / sum) * 100;
	}
	return probs;
}

// Returns a sum of all of the probabilities
double Agent::getSum() {
	vector<string> openIds = maze.getOpenIds();
	double sum = 0;
	for (string id : openIds) {
		sum += maze.getProb(id);
	}
	return sum;
}

//It will produce a corresponding vector of new probabilities given sensing data.
void Agent::filter(vector<int> data) {
	char dirKey[4] = { 'w', 'n', 'e', 's' };
	//gets vector of all tile Ids that are unblocked.
	vector<string> openIds = maze.getOpenIds();
	vector<double> newProbs;

	//Calculate evidence conditional probability
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
		newProbs.push_back(maze.getProb(id) * tProb);
	}
	//here we normalize
	newProbs = normalize(newProbs);
	//update maze
	for (int i = 0; i < openIds.size(); i++) {
		maze.updateProb(openIds[i], newProbs[i]);
	}
}

//It will produce a corresponding vector of new probabilities given movement data.
void Agent::predict(char dir) {
	vector<string> openIds = maze.getOpenIds();
	vector<double> newProbs;
	//Calculate Transitional Probability
	for (string id : openIds){
		double nProb = 0;
		//add the straight calcultions.
		if (maze.getNeighbor(id, dir) == id) {
			nProb += (maze.getProb(id) * straight);
		}
		if (maze.getNeighbor(id, getOpp(dir)) != id){
			nProb += (maze.getProb(maze.getNeighbor(id, getOpp(dir))) * straight);
		}
		//drift left
		if (maze.getNeighbor(id, getLeft(dir)) == id) {
			nProb += (maze.getProb(id) * dLeft);
		}
		if (maze.getNeighbor(id, getRight(dir)) != id) {
			nProb += (maze.getProb(maze.getNeighbor(id, getRight(dir))) * dLeft);
		}
		//drift right
		if (maze.getNeighbor(id, getRight(dir)) == id) {
			nProb += (maze.getProb(id) * dRight);
		}
		if (maze.getNeighbor(id, getLeft(dir)) != id) {
			nProb += (maze.getProb(maze.getNeighbor(id, getLeft(dir))) * dRight);
		}
		
		newProbs.push_back(nProb);
	}
	//here we normalize
	newProbs = normalize(newProbs);
	//update maze
	for (int i = 0; i < openIds.size(); i++) {
		maze.updateProb(openIds[i], newProbs[i]);
	}
}

//Calls maze's print function.
void Agent::printMaze() {
	maze.print();
}