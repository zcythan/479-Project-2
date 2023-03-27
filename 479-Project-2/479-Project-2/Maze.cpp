#include "Maze.h"


Maze::Maze() {
	buildMaze();
	initialMaze();
}

void Maze::buildMaze() {
	char rows[6] = { 'a', 'b','c','d','e', 'f'};
	for (int i = 0; i < sizeof(rows)/sizeof(char); i++) {
		for (int j = 7; j > 0; j--) {
			mazeTile temp;
			temp.row = rows[i];
			temp.col = j;
			temp.id = string(1, temp.row) + to_string(temp.col);
			maze.push_front(temp);
		}
	}
}

void Maze::initialMaze() {
	string blockedIds[22] = { "a2", "a3", "a4", "b1", "b2", "b3", "b7", "c1", "c2", "c6", "c7",
							"d1", "d6", "d7", "e4", "e5", "e6", "e7", "f3", "f4", "f5", "f6"};

	for(mazeTile& t : maze) {
		for (string s : blockedIds) {
			if (s == t.id) {
				t.blocked = true;
			}
		}
		if (!t.blocked) {
			t.prob = 5;
		}
	}
}

//use n for north, w west, ect ect. feel free to redo functionality if theres more convient way it could return data or something
bool Maze::checkObs(string id, char dir) {
	mazeTile t = *findTile(id);
	if (dir == 'n') {
		char nRow = t.row + 1;
		if (nRow < 'g') {
			return findTile((string(1, nRow) + to_string(t.col)))->blocked;
		}
		return true;
	}
	else if (dir == 's') {
	    char nRow = t.row - 1;
		if (nRow > '`') {
			return findTile((string(1, nRow) + to_string(t.col)))->blocked;
		}
		return true;
	}
	else if (dir == 'e') {
		int nCol = t.col + 1;
		if (nCol < 8) {
			return findTile((string(1, t.row) + to_string(nCol)))->blocked;
		}
		return true;
	}
	else if (dir == 'w') {
		int nCol = t.col - 1;
		if (nCol > 0) {
			return findTile((string(1, t.row) + to_string(nCol)))->blocked;
		}
		return true;
	}

	return true;
}

vector<string> Maze::getOpenIds() {
	vector<string> retList;
	for (mazeTile t : maze) {
		if (!t.blocked) {
			retList.push_back(t.id);
		}
	}
	return retList;
}

mazeTile* Maze::findTile(string id) {
	for (mazeTile &t : maze) {
		if (t.id == id) {
			return &t;
		}
	}
	throw invalid_argument("Value not found");
}

//returns probability of a tile.
double Maze::getProb(string id){
	return findTile(id)->prob;
}

//changes probability value at a tile in the maze given Id and new probability. 
void Maze::updateProb(string id, double nProb) {
	mazeTile* t = findTile(id);
	if (!t->blocked) {
		t->prob = nProb;
	}
}

void Maze::print() {
	int cnt = 0;
	for (mazeTile t : maze) {

		if (t.blocked == true) {
			cout << t.blocked_text << " ";
		}
		else {
			cout << fixed;
			cout << setprecision(2);
			if (t.prob < 10) {
				cout << t.prob << "  ";
			}
			else {
				cout << t.prob << " ";
			}
		}
		cnt++;
		if (cnt % 7 == 0) { 
			cout << endl;
		}
	}
	cout << endl;
}