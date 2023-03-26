#include "Maze.h"


Maze::Maze() {
	buildMaze();
}


void Maze::buildMaze() {
	char rows[6] = { 'a', 'b','c','d','e', 'f'};
	for (int i = 0; i < sizeof(rows)/sizeof(char); i++) {
		for (int j = 1; j < 8; j++) {
			mazeTile temp;
			temp.prob = 5.00;
			temp.row = rows[i];
			temp.col = j;
			maze.push_front(temp);
		}
	}
}

void Maze::initialMaze() {
	for(mazeTile t : maze) {

	}
}