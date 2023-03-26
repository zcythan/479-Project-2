#include "Maze.h"


Maze::Maze() {
	buildMaze();
	initialMaze();
}


void Maze::buildMaze() {
	char rows[6] = { 'a', 'b','c','d','e', 'f'};
	for (int i = 0; i < sizeof(rows)/sizeof(char); i++) {
		for (int j = 1; j < 8; j++) {
			mazeTile temp;
			temp.prob = 5.00;
			temp.row = rows[i];
			temp.col = j;
			//temp.id = string(1, temp.row) + to_string(temp.col);
			maze.push_front(temp);
		}
	}
}

void Maze::initialMaze() {
	string blockedIds[22] = { "a2", "a3", "a4", "b1", "b2", "b3", "b7", "c1", "c2", "c6", "c7"
							"d1", "d6", "d7", "e4", "e5", "e6", "e7", "f3", "f4", "f5" "f6"};

	for(mazeTile t : maze) {
		for (string s : blockedIds) {
			if (s == t.id) {
				t.blocked = true;
				t.prob = -1;
			}
		}
		if (!t.blocked) {
			t.prob = 5;
		}
	}
}