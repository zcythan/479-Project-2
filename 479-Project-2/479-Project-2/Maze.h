#pragma once
#include<iostream>
#include<list>
#include<string>

using namespace std;


struct mazeTile {
	float prob;
	char row;
	int col;
	string id = string(1, row) + to_string(col);
	bool blocked = false;
	const string blocked_text = "####";
};

class Maze {
private:
	list<mazeTile> maze;
	void initialMaze();

public:
	Maze();
	void buildMaze();

};