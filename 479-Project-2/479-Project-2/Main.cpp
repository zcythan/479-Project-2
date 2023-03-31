#include "Maze.h"
#include "Agent.h"
#include<iostream>
#include<vector>

using namespace std;

int main() {
	Agent a = Agent();

	cout << "Initial Location Probabilities" << endl;
	cout << endl;
	a.printMaze();

	cout << "Filtering after Evidence [0, 0, 0, 0]" << endl;
	cout << endl;
	a.filter({ 0, 0 ,0, 0 });
	a.printMaze();

	std::cout << "Prediction after Action N\n" << std::endl;
	a.predict('n');
	a.printMaze();

	std::cout << "Filtering after Evidence [0, 0, 1, 0]" << std::endl;
	a.filter({0, 0, 1, 0});
	a.printMaze();
	
	std::cout << "Prediction after Action N" << std::endl;
	a.predict('n');
	a.printMaze();

	std::cout << "Filtering after Evidence [0, 1, 1, 0]" << std::endl;
	a.filter({ 0, 1, 1, 0 });
	a.printMaze();

	std::cout << "Prediction after Action W\n";
	a.predict('w');
	a.printMaze();

	std::cout << "Filtering after Evidence [0, 1, 0, 0]\n";
	a.filter({ 0, 1, 0, 0 });
	a.printMaze();

	std::cout << "Prediction after Action S\n";
	a.predict('s');
	a.printMaze();

	std::cout << "Filtering after Evidence [0, 0, 0, 0]\n";
	a.filter({ 0, 0, 0, 0 });
	a.printMaze();

	

	system("pause");
	return 0;
}

