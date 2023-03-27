#include "Header.h"
#include "Maze.h"

extern mazeSquare maze[5][6];

int main() {

	Maze m = Maze();

	m.print();
	cout << endl;
	cout << "Does a5 have obs to the north?: " << m.checkObs("a5", 'n') << endl;
	cout << "Does a5 have obs to the west?: " << m.checkObs("a5", 'w') << endl;
	cout << "Does a5 have obs to the south?: " << m.checkObs("a5", 's') << endl;
	cout << "Does a5 have obs to the east?: " << m.checkObs("a5", 'e') << endl;
	cout << "a5 probability: " << m.getProb("a5") << endl;
	m.updateProb("a5", 7.453);
	cout << "a5 probability: " << m.getProb("a5") << endl;

	//std::cout << "This is a file\n";
	//action a[9];
	// Generating data into our sequence 
	//for (int i = 1; i < 9; i++) {
		//generateSequence(a[1]);
	//}
	//initializeMazeTest2();
	system("pause");
}

// Pass this function the current square location and what it senses.
// This is probably going to be called in a loop while generating the final output
/*std::string move(std::string, std::string) {
	// Calculate probability of moving to the square
	//

}*/

// I was thinking of how to make this dynamic.
// The menu will be the same thing each time, just the specific integer we care about changes 
// First menu is initLocProb, second is Filtering after Evidence, etc. 
// We print off at least 9 menus 
// I considered labeling them 0-8, passing that integer, and then having a switch case decide 
// Ex, pass function 0 and it will print the first menu, which would be InitLocProb 
void generateMenu(int menu) {
	switch (menu) {
	case 0:
		std::cout << "This is the Initial Location Probability Menu\n";
		break;
	case 1:
		std::cout << "This is the first filtering after evidence menu\n";
		break;
		// etc...
	}

}

// I have no idea how we are going to pass information to and from the functions below.
// We could work out of a file, in and out, 
// Pass arguments and returns as strings, ints, or just use globals 

// Comes up with the probability that we are starting within each square of the maze 
void generateInitLocProbabilities() {
	// Takes accuracy probability 
	// Sums the probability of all squares
	// Each square's probability by the sum
	// Multiplies by 100 to come up with a percentage 
	// Assigns percentage to relevant squares 

}

// Passing a single node at a time 
// dir = which direction we are looking at. 1 = west, 2 = north, 3 = east, 4 = south
/*void generatePrediction(maze m, int dir) {

}*/

// Generates decimal probabilities from filtering 
void generateFiltering() {

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			// Do the thing 

		}
	}

}

// Normalizes the decimal probabilities then turns them into percents 
// Similarly to the menu, we pass an int that is a code for which way we want the program to handle 
// 1 = one functionality (which means accessing a specific attribute), 2 = Evidence Condition. Prob, etc..
void normalizeProbabilities(int mode) {
	// mode = 0 = initial probabilities
	// mode = 1 = evidence conditional probabilities 
	double sum = 0;

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			switch (mode) {
			case 0:
				sum += maze[i, j]->initStartProbD;
				break;
			case 1:
				sum += maze[i, j]->EviCondD;
				break;
			}
		}
	}
	// grid squares
	sum = sum / 42;
	// Now we update to put data into the struct 
	//Adding a test comment
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			switch (mode) {
			case 0:
				maze[i][j].initStartPerc = (sum * 100);
				break;
			case 1:
				maze[i][j].EvidenceCondPerc = (sum * 100);
				break;
			}
		}
	}

}

// Initially initializes data into the maze, such as which blocks are neighbors to each other
// Modified to snipe out grid squares that are obstacles and tag them
void initializeMazeTest2() {
	// Initialize the maze
	// std::couts are for testing

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			maze[i][j].ID = char('A' + i) + std::to_string(j + 1);
			maze[i][j].obstacle = 0;
			std::cout << "I am item: ";
			std::cout << " " << maze[i][j].ID << ", My neighbors are W:";
			// Set neighbors
			if (j > 0) {
				maze[i][j].west = maze[i][j - 1].ID;
				std::cout << maze[i][j].west << ", ";
			}
			else {
				maze[i][j].west = "\0";
				std::cout << "0, ";
			}

			if (j < 6) {
				maze[i][j].east = maze[i][j + 1].ID;
				std::cout << "E: " << maze[i][j].east << ", ";
			}
			else {
				maze[i][j].east = "\0";
				std::cout << "E: 0, ";
			}

			if (i > 0) {
				maze[i][j].north = maze[i - 1][j].ID;
				std::cout << "N: " << maze[i][j].north << ", ";
			}
			else {
				maze[i][j].north = "\0";
				std::cout << "N: 0, ";
			}

			if (i < 5) {
				maze[i][j].south = maze[i + 1][j].ID;
				std::cout << "S: " << maze[i][j].south << ".";
			}
			else {
				maze[i][j].south = "\0";
				std::cout << "S: 0, ";
			}

			// Set obstacles
			if (maze[i][j].ID == "A2" || maze[i][j].ID == "A3" || maze[i][j].ID == "A4" ||
				maze[i][j].ID == "B1" || maze[i][j].ID == "B2" || maze[i][j].ID == "B3" ||
				maze[i][j].ID == "B7" || maze[i][j].ID == "C1" || maze[i][j].ID == "C2" ||
				maze[i][j].ID == "C6" || maze[i][j].ID == "C7" || maze[i][j].ID == "D1" ||
				maze[i][j].ID == "D6" || maze[i][j].ID == "D7" || maze[i][j].ID == "E4" ||
				maze[i][j].ID == "E5" || maze[i][j].ID == "E6" || maze[i][j].ID == "E7" ||
				maze[i][j].ID == "F3" || maze[i][j].ID == "F4" || maze[i][j].ID == "F5" ||
				maze[i][j].ID == "F6") {
				maze[i][j].obstacle = 1;
				std::cout << "\nI have an obstacle.";
			}
			std::cout << std::endl;
		}
	}
}

void generateSequence(action a) {
	for (int i = 1; i < 9; i++) {
		a.type = a.ID % 2;
	}
	switch (a.ID) {
	case 1:
		a.dir = 2;
		break;
	case 3:
		a.dir = 2;
		break;
	case 5:
		a.dir = 1;
		break;
	case 7:
		a.dir = 4;
		break;
	}
}

void initializeBruteForce() {
	// manually initializing because the logical function was weird 
	// Row A
	maze[0][0].ID = "A1";
	maze[0][0].west = "\0";
	maze[0][0].north = "B1";
	maze[0][0].east = "A2";
	maze[0][0].south = "\0";
	maze[0][0].obstacle = 0;

	maze[0][1].ID = "A2";
	maze[0][1].west = "\0";
	maze[0][1].north = "B2";
	maze[0][1].east = "A3";
	maze[0][1].south = "A1";
	maze[0][1].obstacle = 1;

	maze[0][2].ID = "A3";
	maze[0][2].west = "\0";
	maze[0][2].north = "B3";
	maze[0][2].east = "A4";
	maze[0][2].south = "A2";
	maze[0][2].obstacle = 1;

	maze[0][3].ID = "A4";
	maze[0][3].west = "\0";
	maze[0][3].north = "B4";
	maze[0][3].east = "\0";
	maze[0][3].south = "A3";
	maze[0][3].obstacle = 1;

	maze[0][4].ID = "A5";
	maze[0][4].west = "\0";
	maze[0][4].north = "B5";
	maze[0][4].east = "A6";
	maze[0][4].south = "\0";
	maze[0][4].obstacle = 0;

	maze[0][4].ID = "A5";
	maze[0][4].west = "A4";
	maze[0][4].north = "B5";
	maze[0][4].east = "A6";
	maze[0][4].south = "\0";
	maze[0][4].obstacle = 0;

	maze[0][6].ID = "A7";
	maze[0][6].west = "A6";
	maze[0][6].north = "B7";
	maze[0][6].east = "\0";
	maze[0][6].south = "\0";
	maze[0][6].obstacle = 1;

	// Row B
	maze[1][0].ID = "B1";
	maze[1][0].west = "\0";
	maze[1][0].north = "C1";
	maze[1][0].east = "B2";
	maze[1][0].south = "A1";
	maze[1][0].obstacle = 1;

	maze[1][1].ID = "B2";
	maze[1][1].west = "B1";
	maze[1][1].north = "C2";
	maze[1][1].east = "B3";
	maze[1][1].south = "A2";
	maze[1][1].obstacle = 1;

	maze[1][2].ID = "B3";
	maze[1][2].west = "B2";
	maze[1][2].north = "C3";
	maze[1][2].east = "\0";
	maze[1][2].south = "A3";
	maze[1][2].obstacle = 1;

	maze[1][3].ID = "B4";
	maze[1][3].west = "B3";
	maze[1][3].north = "C4";
	maze[1][3].east = "B5";
	maze[1][3].south = "A4";
	maze[1][4].obstacle = 1;

	maze[1][4].ID = "B5";
	maze[1][4].west = "B4";
	maze[1][4].north = "C5";
	maze[1][4].east = "B6";
	maze[1][4].south = "A5";
	maze[1][4].obstacle = 0;

	maze[1][5].ID = "B6";
	maze[1][5].west = "B5";
	maze[1][5].north = "C6";
	maze[1][5].east = "B7";
	maze[1][5].south = "A6";
	maze[1][5].obstacle = 0;

	maze[1][6].ID = "B7";
	maze[1][6].west = "B6";
	maze[1][6].north = "C7";
	maze[1][6].east = "\0";
	maze[1][6].south = "A7";
	maze[1][6].obstacle = 1;

	// Row C
	maze[2][0].ID = "C1";
	maze[2][0].west = "\0";
	maze[2][0].north = "D1";
	maze[2][0].east = "C2";
	maze[2][0].south = "B1";
	maze[2][0].obstacle = 1;

	maze[2][1].ID = "C2";
	maze[2][1].west = "C1";
	maze[2][1].north = "D2";
	maze[2][1].east = "C3";
	maze[2][1].south = "B2";
	maze[2][1].obstacle = 1;

	maze[2][2].ID = "C3";
	maze[2][2].west = "C2";
	maze[2][2].north = "D3";
	maze[2][2].east = "C4";
	maze[2][2].south = "B3";
	maze[2][2].obstacle = 0;

	maze[2][3].ID = "C4";
	maze[2][3].west = "C3";
	maze[2][3].north = "D4";
	maze[2][3].east = "C5";
	maze[2][3].south = "B4";
	maze[2][3].obstacle = 0;

	maze[2][4].ID = "C5";
	maze[2][4].west = "C4";
	maze[2][4].north = "D5";
	maze[2][4].east = "C6";
	maze[2][4].south = "B5";
	maze[2][4].obstacle = 0;

	maze[2][5].ID = "C6";
	maze[2][5].west = "C5";
	maze[2][5].north = "D6";
	maze[2][5].east = "C7";
	maze[2][5].south = "B6";
	maze[2][5].obstacle = 1;

	maze[2][6].ID = "C7";
	maze[2][6].west = "C6";
	maze[2][6].north = "D7";
	maze[2][6].east = "\0";
	maze[2][6].south = "B7";
	maze[2][6].obstacle = 1;

	// Row D
	maze[3][0].ID = "D1";
	maze[3][0].west = "\0";
	maze[3][0].north = "E1";
	maze[3][0].east = "D2";
	maze[3][0].south = "C1";
	maze[3][0].obstacle = 1;

	maze[3][1].ID = "D2";
	maze[3][1].west = "D1";
	maze[3][1].north = "E2";
	maze[3][1].east = "D3";
	maze[3][1].south = "C2";
	maze[3][1].obstacle = 0;

	maze[3][2].ID = "D3";
	maze[3][2].west = "D2";
	maze[3][2].north = "E3";
	maze[3][2].east = "D4";
	maze[3][2].south = "C3";
	maze[3][2].obstacle = 0;

	maze[3][3].ID = "D4";
	maze[3][3].west = "D3";
	maze[3][3].north = "E4";
	maze[3][3].east = "D5";
	maze[3][3].south = "C4";
	maze[3][3].obstacle = 0;

	maze[3][4].ID = "D5";
	maze[3][4].west = "D4";
	maze[3][4].north = "E5";
	maze[3][4].east = "D6";
	maze[3][4].south = "C5";
	maze[3][4].obstacle = 0;

	maze[3][5].ID = "D6";
	maze[3][5].west = "D5";
	maze[3][5].north = "E6";
	maze[3][5].east = "D7";
	maze[3][5].south = "C6";
	maze[3][5].obstacle = 1;

	maze[3][6].ID = "D7";
	maze[3][6].west = "D6";
	maze[3][6].north = "E7";
	maze[3][6].east = "\0";
	maze[3][6].south = "C7";
	maze[3][6].obstacle = 1;

	// Row E
	maze[4][0].ID = "E1";
	maze[4][0].west = "\0";
	maze[4][0].north = "F1";
	maze[4][0].east = "E2";
	maze[4][0].south = "D1";
	maze[4][0].obstacle = 0;

	maze[4][1].ID = "E2";
	maze[4][1].west = "E1";
	maze[4][1].north = "F2";
	maze[4][1].east = "E3";
	maze[4][1].south = "D2";
	maze[4][0].obstacle = 0;

	maze[4][2].ID = "E3";
	maze[4][2].west = "E2";
	maze[4][2].north = "F3";
	maze[4][2].east = "E4";
	maze[4][2].south = "D3";
	maze[4][0].obstacle = 0;

	maze[4][3].ID = "E4";
	maze[4][3].west = "E3";
	maze[4][3].north = "F4";
	maze[4][3].east = "E5";
	maze[4][3].south = "D4";
	maze[4][3].obstacle = 1;

	maze[4][4].ID = "E5";
	maze[4][4].west = "E4";
	maze[4][4].north = "F5";
	maze[4][4].east = "E6";
	maze[4][4].south = "D5";
	maze[4][4].obstacle = 1;

	maze[4][5].ID = "E6";
	maze[4][5].west = "E5";
	maze[4][5].north = "F6";
	maze[4][5].east = "E7";
	maze[4][5].south = "D6";
	maze[4][5].obstacle = 1;

	maze[4][6].ID = "E7";
	maze[4][6].west = "E6";
	maze[4][6].north = "F7";
	maze[4][6].east = "\0";
	maze[4][6].south = "D7";
	maze[4][6].obstacle = 1;

	// Row F
	maze[5][0].ID = "F1";
	maze[5][0].west = "\0";
	maze[5][0].north = "G1";
	maze[5][0].east = "F2";
	maze[5][0].south = "E1";
	maze[5][0].obstacle = 0;

	maze[5][1].ID = "F2";
	maze[5][1].west = "F1";
	maze[5][1].north = "G2";
	maze[5][1].east = "F3";
	maze[5][1].south = "E2";
	maze[5][1].obstacle = 0;

	maze[5][2].ID = "F3";
	maze[5][2].west = "F2";
	maze[5][2].north = "G3";
	maze[5][2].east = "F4";
	maze[5][2].south = "E3";
	maze[5][2].obstacle = 1;

	maze[5][3].ID = "F4";
	maze[5][3].west = "F3";
	maze[5][3].north = "G4";
	maze[5][3].east = "F5";
	maze[5][3].south = "E4";
	maze[5][3].obstacle = 1;

	maze[5][4].ID = "F5";
	maze[5][4].west = "F4";
	maze[5][4].north = "G5";
	maze[5][4].east = "F6";
	maze[5][4].south = "E5";
	maze[5][4].obstacle = 1;

	maze[5][5].ID = "F6";
	maze[5][5].west = "F5";
	maze[5][5].north = "G6";
	maze[5][5].east = "F7";
	maze[5][5].south = "E6";
	maze[5][5].obstacle = 1;

	maze[5][6].ID = "F7";
	maze[5][6].west = "F6";
	maze[5][6].north = "\0";
	maze[5][6].east = "\0";
	maze[5][6].south = "E7";
	maze[5][6].obstacle = 0;

}


// Abandoned 
// Feel free to turn this into a class method if we go that route
// I am manually initializing into program memory, but alternatively, 
// We can generate a file that has this information and then read the file in to memory
// Not loading in the sensing yet 
// We could create a whole new .cpp file to dump this in because it's not pretty to look at
/*void initializeMazeData() {
	// Every row is row-1, column is column-1, because we start counting at 0

	// Row A
	maze[0, 0].ID = "A1";
	maze[0, 0].east = "A2", maze[0, 0].north = "B1";	// West, South = nullptr
	maze[0, 0].obstacle = 0;
	maze[1, 0].ID = "A2";
	maze[1, 0].west = "A1", maze[1, 0].east = "A3", maze[1, 0].north = "B2";	// South = nullptr
	maze[1, 0].obstacle = 1;
	maze[2, 0].ID = "A3";
	maze[2, 0].west = "A2", maze[2, 0].east = "A4", maze[2, 0].north = "B3";	// South = nullptr
	maze[2, 0].obstacle = 1;
	maze[3, 0].ID = "A4";
	maze[3, 0].west = "A3", maze[3, 0].east = "A5", maze[3, 0].north = "B4";	// South = nullptr
	maze[3, 0].obstacle = 1;
	maze[4, 0].ID = "A5";
	maze[4, 0].west = "A4", maze[4, 0].east = "A6", maze[4, 0].north = "B5";	// South = nullptr
	maze[4, 0].obstacle = 0;
	maze[5, 0].ID = "A6";
	maze[5, 0].west = "A5", maze[5, 0].east = "A7", maze[5, 0].north = "B6";	// South = nullptr
	maze[5, 0].obstacle = 0;
	maze[6, 0].ID = "A7";
	maze[6, 0].west = "A6", maze[6, 0].north = "B6";	// East, South = nullptr
	maze[6, 0].obstacle = 0;

	// Row B
	maze[0, 1].ID = "B1";
	maze[0, 1].east = "B2", maze[0, 1].north = "C1", maze[0, 1].south = "A1"; // West = nullptr
	maze[0, 1].obstacle = 1;
	maze[1, 1].ID = "B2";
	maze[1, 1].west = "B1", maze[1, 1].north = "C2", maze[1, 1].east = "B3", maze[1, 1].south = "A2";
	maze[1, 1].obstacle = 1;
	maze[2, 1].ID = "B3";
	maze[2, 1].west = "B2", maze[2, 1].north = "C3", maze[2, 1].east = "B4", maze[2, 1].south = "A3";
	maze[2, 1].obstacle = 1;
	maze[3, 1].ID = "B4";
	maze[3, 1].west = "B3", maze[3, 1].north = "C4", maze[3, 1].east = "B5", maze[3, 1].south = "A4";
	maze[3, 1].obstacle = 0;
	maze[4, 1].ID = "B5";
	maze[4, 1].west = "B4", maze[4, 1].north = "C5", maze[4, 1].east = "B6", maze[4, 1].south = "A5";
	maze[4, 1].obstacle = 0;
	maze[5, 1].ID = "B6";
	maze[5, 1].west = "B5", maze[5, 1].north = "C6", maze[5, 1].east = "B7", maze[5, 1].south = "A5";
	maze[5, 1].obstacle = 0;
	maze[6, 1].ID = "B7";
	maze[6, 1].west = "B6", maze[6, 1].north = "C7", maze[6, 1].south = "A5"; // East = nullptr
	maze[6, 1].obstacle = 1;




	initializeActualObstacles();
}
*/

// Doing this using better logic 
// Untested
// Does not add obstacles in 
/*void initializeMazeTest() {

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			maze[i][j].ID = char('A' + i) + std::to_string(j + 1);

			// Set neighbors
			if (j > 0) { // West neighbor
				maze[i][j].west = char('A' + i) + std::to_string(j);
			}
			else {
				maze[i][j].west = "\0";
			}
			if (i > 0) { // North neighbor
				maze[i][j].north = char('A' + i - 1) + std::to_string(j + 1);
			}
			else {
				maze[i][j].north = "\0";
			}
			if (j < 6) { // East neighbor
				maze[i][j].east = char('A' + i) + std::to_string(j + 2);
			}
			else {
				maze[i][j].east = "\0";
			}
			if (i < 5) { // South neighbor
				maze[i][j].south = char('A' + i + 1) + std::to_string(j + 1);
			}
			else {
				maze[i][j].south = "\0";
			}
		}
	}
}
*/

// Checks neighbor.obstacle to decide if its a<direction> is 0 or 1
// I was doing this by hand but it got to be too annoying
/*void initializeActualObstacles() {

	for (int i = 0, j = 0; j < 5; j++) {

		if (j == 5) {
			i++, j = 0;
		}
	}

}
*/