#include "CircularDoublyLinkedList.h"
#include <iostream>
using namespace std;
#pragma once
class TopSpinADT {
public:
	// shifts the pieces 1 to the left
	virtual void shiftLeft() = 0;
	//shifts the pieces 1 to the right
	virtual void shiftRight() = 0;
	//reverses the pieces in the spin mechanism
	virtual void spin() = 0;
	//checks to see if the puzzle is solved that is to say the pieces are in numerical order 1 - 20
	virtual bool isSolved() = 0;
};

class TopSpin: public TopSpinADT {
private:
	int _size;	//Stores the size of the board
	int _spinSize;	//Stores the size of the spinner
	CircularDoublyLinkedList<int> board;	//CDLL to store the board
	void populateBoard();	//Populate the board with values equal to _size
	friend std::ostream& operator<< (std::ostream& os, const TopSpin& ts);	//Overloaded ostream operator to print the board

public: 
	TopSpin(int size, int spinSize);	//Construct a new TopSpin object
	~TopSpin(){}	//Destructor
	 void shiftLeft(); //shifts the pieces 1 to the left
	 void shiftLeft(int n); //shifts the pieces n times to the left
	void shiftRight();  //shifts the pieces 1 to the right
	void spin();	//reverses the pieces in the spin mechanism
	bool isSolved();	//checks to see if the puzzle is solved
	void randomize(int);	//Randomizes the order of the baord by shifting left a random number of times, then spinning
};

std::ostream& operator<< (std::ostream& os, const TopSpin& ts);