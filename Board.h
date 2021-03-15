#include <iostream>
#include <vector>
using namespace std;

#ifndef BOARD_H
#define BOARD_H

class Board
{
private:

	char board[10][10];
	int m_shipNum;
	int shipsLeft;
	std::vector<std::vector<std::pair<int, int>>> shipsCoordinates;

public:

	/**
	* Inlitialize a blank board and variables
	*
	**/
	Board();

	/**
	* Set the number of ships
	*
	* @param int - The number of ships get from getShipsNum function
	* @return int - Nothing
	**/
	void setShipNum(int);

	/**
	* get the number of ships
	* @param int num
	* @return int - The number of ships
	**/
	int getShipNum();

	/**
	* get how many number of ship left
	* @param nothing
	* @return The number of the ships that still left
	**/
	int getShipsLeft();

	/**
	*Placing ship at the loction that player want, and also make sure it will not over size
	*
	* @param int - row1 coordinate
	* @param int - column1 coordinate
	* @param int - row2 coordinate
	* @param int - column2 coordinateand
	* @param int - ship size
	* @return Nothing
	**/
	void placeShips(int, int, int, int, int);

	/**
	*Check if player hit or miss in the entered location
	*
	* @param int - Take in the row coordinate
	* @param int - Take in the col coordinate
	* @return Char - Return 'M' shows Missed, return 'H' shows hitted
	**/
	char checkCoordinates(int, int);

	/**
	*Update the current attack result to board
	*
	* @param int - row coordinate
	* @param int - column coordinate
	* @param Char - Char to show the attack is miss or hit
	* @return Nothing
	**/
	void update(int, int, char c);

	/**
	*Set the number of left ships
	* @param char - array to store the board
	* @param int - number of left ships getting from getShipsLeft function
	* @return None
	**/
	void setShipsLeft(int);

	/**
	*Help count the number of left ship. Once player sink a ship, the ship left number -1.
	* @ param int - the num of steps
	* @return Nothing
	**/
	void sinkShip();

	/**
	*Check if the ship placement is valid
	*
	* @param int - row1 coordinate
	* @param int - column1 coordinate
	* @param int - row2 coordinate
	* @param int - column2 coordinateand
	* @param int - number of ships
	* @return Bool - True for valid, false for invalid
	**/
	bool checkForShips(int, int, int, int, int);

	/**
	*Initialize a 2D vector
	*
	* @param int - Take in the number of ships
	* @return Nothing
	**/
	void setShipsVector(int num);

	/**
	*This is a test function we used to see if the coordinate works well
	* @int - num of steps
	* @return Nothing
	**/
	void printShipsCoordinates();

	/**
	*Check if player's attack sunk a ship
	*
	* @param int - Row coordinate
	* @param int - Col coordinate
	* @return Bool - True for sunk, false for not missed
	**/
	bool isSunk(int, int);

	/**
	*Print out the board with
	*
	* @param int - Row coordinate
	* @param int - Col coordinate
	* @return Bool - True for sunk, false for not missed
	**/
	void printBoard();

	/**
	* Gives the vector of coordinates
	*
	* @return std::vector<std::vector<std::pair<int, int>>> - Returns the vector filled with the coordinates
	**/
	std::vector<std::vector<std::pair<int, int>>> getCoordinates();
};
#endif
