#pragma once
#include<iostream>
#include<list>
#include<string>
#include<iomanip>
#include<vector>

using namespace std;

struct mazeTile {
	double prob = -1;
	char row = -1;
	int col = -1;
	string id = "";
	bool blocked = false;
	const string blocked_text = "#####";
};

class Maze {
private:
	list<mazeTile> maze;
	void initialMaze();
	mazeTile* findTile(string id);

public:
	Maze();
	void buildMaze();
	void print();
	vector<string> getOpenIds();
	void updateProb(string id, double nProb);
	bool checkObs(string id, char dir);
	double getProb(string id);
	std::string getNeighbor(string id, char dir);
};