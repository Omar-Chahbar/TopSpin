#include "TopSpin.h"
#include <iostream>
#include <ctime>
using namespace std;

TopSpin::TopSpin(int size = 20, int spinSize = 4) {
	//Ensure the board is being created properly
	if (size < 1 || spinSize > size) {
		_size = 20;
		_spinSize = 4;
	}
	else {
		_size = size;
		_spinSize = spinSize;
	}
	populateBoard();
}

void TopSpin::populateBoard()
{
	for (int i = _size; i >=1 ; i--) {
		board.addHead(i);
	}
}

void TopSpin::shiftLeft()
{
	board.moveLeft();
}

void TopSpin::shiftLeft(int n)
{
	for (int i = 0; i < n; i++)
		board.moveLeft();
}

void TopSpin::shiftRight()
{
	board.moveRight();
}

void TopSpin::spin()
{
	for (int i = 0; i < _spinSize/ 2; i++) {
		board.swap(i, _spinSize - 1 - i);
	}
}

bool TopSpin::isSolved()
{
	for (CircularDoublyLinkedList<int>::Iterator it = board.begin(); it != board.end(); ++it) {
		if (it.getValue() == _size) {
			if (it.getNextValue() != 1)	//if the value is equal to the size it is the largest value, and the next value should be a 1
				return false;
		}
		else {
			if (it.getNextValue() != it.getValue() + 1)	//Check that the next value is equal to the curren value + 1
				return false;
		}
	}
	return true;
}

void TopSpin::randomize(int n)
{
	//Randomize the order of the board
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		shiftLeft((rand() % 19) + 1);
		spin();
	}
}

std::ostream& operator<< (std::ostream& os, const TopSpin& ts) {
	//Print the top of the spinner box
	os << "|-";
	for (int i = 0; i < ts._spinSize; i++) {
		os << "--";
		if (ts.board.retrieve(i) >= 10)	//If a number is 2 digits, the box needs to be 1 space larger
			os << "-";
	}
	os <<"|" << endl;
	os << "| ";

	//Print the numbers in the spinner
	for (int i = 0; i < ts._spinSize; i++)
		os << ts.board.retrieve(i) << " ";
	os << "| ";
	//Print the rest of the numbers
	for (int i = ts._spinSize; i < ts._size; i++)
		os << ts.board.retrieve(i) << " ";

	//Print the bottom of the spinner box
	os << endl << "|-";
	for (int j = 0; j < ts._spinSize; j++) {
		os << "--";
		if (ts.board.retrieve(j) >= 10)  //If a number is 2 digits, the box needs to be 1 space larger
			os << "-";
	}
	os << "|" << endl;
	return os;
}