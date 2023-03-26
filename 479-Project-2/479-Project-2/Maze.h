#pragma once
#include<iostream>
#include<list>
#include<string>
#include<iomanip>

using namespace std;


struct mazeTile {
	float prob = -1;
	char row = -1;
	int col = -1;
	string id = "";
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
	void print();

};