#include "Maze.h"
#include "Calculator.h"
#include<iostream>
#include<vector>

using namespace std;

int main() {
	Calculator c = Calculator();

	cout << "Initial Location Probabilities" << endl;
	cout << endl;
	c.printMaze();

	cout << "Filtering after Evidence [0, 0, 0, 0]" << endl;
	cout << endl;
	c.filter({ 0, 0 ,0, 0 });
	c.printMaze();

	std::cout << "Prediction after Action N\n" << std::endl;
	c.prediction(2);
	c.printMaze();

	system("pause");
	return 0;
}

