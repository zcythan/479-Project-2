#include "Maze.h"
#include "Calculator.h"


int main() {

	//Maze m = Maze();
	Calculator c = Calculator();
	cout << "Initial Location Probabilities" << endl;
	cout << endl;
	c.printMaze();
	cout << "Filtering after Evidence [0, 0, 0, 0]" << endl;
	cout << endl;
	int data[4] = { 0, 0, 0, 0 };
	c.filter(data);
	c.printMaze();
	cout << endl;
	
	system("pause");
}

