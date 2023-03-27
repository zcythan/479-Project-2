#include "Maze.h"
#include "Calculator.h"
#include<iostream>
#include<vector>

int main() {
	Calculator c = Calculator();

	cout << "Initial Location Probabilities" << endl;
	cout << endl;
	c.printMaze();

	cout << "Filtering after Evidence [0, 0, 0, 0]" << endl;
	cout << endl;
	c.filter({ 0, 0 ,0, 0 });
	c.printMaze();
	
	system("pause");
	return 0;
}

