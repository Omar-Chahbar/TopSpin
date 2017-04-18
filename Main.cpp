#include "TopSpin.h"
#include <iostream>
using namespace std;

void main() {
	int random;	//Store the number of random moves
	int choice = 0;	//Store the user's choice
	int shift;	//Store the number of shifts the user wants to do
	TopSpin top(20,6); //Instantiate a topspin object of size 20 and spin size 4

	//Randomize the board
	cout << "How many random moves would you like to do?: ";
	cin >> random;
	top.randomize(random);

	cout << endl << top << endl;

	//Do not print this if the puzzle is already solved (eg. random moves = 0)
	if(!top.isSolved())
		cout << "Please choose from the following options, enter your choice by entering the corresponding number: ";
		
	//Continue the loop until the board is solved or the user quits
	while (choice != 4 && !top.isSolved()) {
		cout << endl<<"1. Shift Right" << endl << "2. Shift Left" << endl <<"3. Spin" << endl << "4. Quit" << endl << endl;
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "How many times would you like to shift?: ";
			cin >> shift;
			for (int i = 0; i < shift; i++)
				top.shiftRight();
			break;
		case 2:
			cout << "How many times would you like to shift?: ";
			cin >> shift;
			for (int i = 0; i < shift; i++)
				top.shiftLeft();
			break;
		case 3:
			top.spin();
			break;
		case 4:
			break;
		default:
			cout << endl << "Please enter a valid option" << endl;
		}
		cout << endl;

		if(choice != 4)	
			cout <<top;	//Reprint the board, unless the user wants to quit
	}

	if (top.isSolved())
		cout << endl << "Congratulations! You solved the puzzle." << endl;
	else
		cout << endl << "Thanks for playing!" << endl;
}