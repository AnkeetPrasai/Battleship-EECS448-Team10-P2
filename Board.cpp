#include "Board.h"
#include <iostream>
#include <cmath>
using std::cout;
using std::vector;
using std::pair;
using std::endl;
using std::cin;

Board::Board()
{
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			board[i][k] = '.';
		}
	}
}

void Board::setShipNum(int num)
{
	m_shipNum = num;
}

void Board::setShipsLeft(int num)
{
	shipsLeft = num;
}

int Board::getShipsLeft()
{
	return shipsLeft;
}

void Board::setShipsVector(int num)
{
	for (int i = 0; i < num; i++)
	{
		shipsCoordinates.push_back({});
	}
}

void Board::printShipsCoordinates()
{
	for (int i = 0; i < shipsCoordinates.size(); i++)
	{
		for (int j = 0; j < shipsCoordinates[i].size(); j++)
		{
			cout << shipsCoordinates[i][j].first << " " << shipsCoordinates[i][j].second << endl;
		}
		cout << endl;
	}
}

int Board::getShipNum()
{
	return(m_shipNum);
}

void Board::placeShips(int x1Coor, int y1Coor, int x2Coor, int y2Coor, int shipSize)
{
	if ((x1Coor - 1 == x2Coor - 1) && (y1Coor - 1 == y2Coor - 1))
	{
		board[x1Coor - 1][y1Coor - 1] = 'S';
		shipsCoordinates[shipSize].push_back(std::make_pair(x1Coor - 1, y1Coor - 1));
	}
	else if (x1Coor - 1 == x2Coor - 1)
	{
		if ((y1Coor - 1) < (y2Coor - 1))
		{
			for (int i = y1Coor - 1; i <= y2Coor - 1; i++)
			{
				board[x1Coor - 1][i] = 'S';
				shipsCoordinates[shipSize].push_back(std::make_pair(x1Coor - 1, i));
			}
		}
		else if ((y1Coor - 1) > (y2Coor - 1))
		{
			for (int i = y2Coor - 1; i <= y1Coor - 1; i++)
			{
				board[x1Coor - 1][i] = 'S';
				shipsCoordinates[shipSize].push_back(std::make_pair(x1Coor - 1, i));
			}
		}
	}
	else if (y1Coor - 1 == y2Coor - 1)
	{
		if ((x1Coor - 1) < (x2Coor - 1))
		{
			for (int i = x1Coor - 1; i <= x2Coor - 1; i++)
			{
				board[i][y1Coor - 1] = 'S';
				shipsCoordinates[shipSize].push_back(std::make_pair(i, y1Coor - 1));
			}
		}
		else if ((x2Coor - 1) < (x1Coor - 1))
		{
			for (int i = x2Coor - 1; i <= x1Coor - 1; i++)
			{
				board[i][y1Coor - 1] = 'S';
				shipsCoordinates[shipSize].push_back(std::make_pair(i, y1Coor - 1));
			}
		}
	}
}

bool Board::checkForShips(int x1, int y1, int x2, int y2, int CountShip)
{
	//Horizontal
	int crrent = m_shipNum - CountShip;

	//makes sure ship size isn't longer than the size supposed to be placed
	if ((abs(x1 - x2)) > crrent || abs(y1 - y2) > crrent)
	{
		return false;
	}

	if (x1 == x2)
	{
		int collen = abs(y2 - y1);

		for (int i = y1 - 1; i <= y2 - 1; i++)
		{
			if (board[x1 - 1][i] == 'S')
			{
				return false;
			}
			else if (collen != crrent)
			{
				return false;
			}
		}

		for (int i = y2 - 1; i <= y1 - 1; i++)
		{
			if (board[x1 - 1][i] == 'S')
			{
				return false;
			}
		}

	}
	//Vertical
	else if (y1 == y2)
	{
		int rowlen = abs(x2 - x1);

		for (int i = x1 - 1; i < x2 - 1; i++)
		{
			if (board[i][y1 - 1] == 'S')
			{
				return false;
			}
			else if (rowlen != crrent)
			{
				return false;
			}
		}
		for (int i = x2 - 1; i < x1 - 1; i++)
		{
			if (board[i][y1 - 1] == 'S')
			{
				return false;
			}
		}
	}
	else if (x1 - 1 != x2 - 1 && y1 - 1 != y2 - 1)
	{
		return false;
	}

	return true;
}

char Board::checkCoordinates(int row, int col)
{
	return board[row][col];
}

void Board::update(int row, int col, char c)
{
	board[row][col] = c;
} 

bool Board::isSunk(int row, int col)
{

	for (int i = 0; i < shipsCoordinates.size(); i++)
	{
		for (int j = 0; j < shipsCoordinates[i].size(); j++)
		{
			if (shipsCoordinates[i][j].first == row && shipsCoordinates[i][j].second == col)
			{
				shipsCoordinates[i].erase(shipsCoordinates[i].begin() + j);

				if (shipsCoordinates[i].size() == 0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		cout << endl;
	}

	return false;
}

void Board::sinkShip()
{
	shipsLeft -= 1;
}

void Board::printBoard()
{
	std::cout << "\n     A B C D E F G H I J \n";
	for (int i = 0; i < 10; i++)
	{
		if (i != 9)
		{
			cout << "  " << i + 1 << "| ";
		}
		else
		{
			cout << " " << i + 1 << "| ";
		}

		for (int k = 0; k < 10; k++)
		{
			cout << board[i][k] << " ";
		}
		cout << "\n";
	}

}

vector<vector<pair<int, int>>> Board::getCoordinates()
{
	return shipsCoordinates;
}

