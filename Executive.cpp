#include "Executive.h"
#include"Board.h"
#include "string"
#include <cctype>
#include <ctime>
using namespace std;

Executive::Executive(int num)
{
	m_shipNum = num;
	P1Board1.setShipNum(num);
	P1Board1.setShipsVector(num);
	P1Board1.setShipsLeft(num);
	P2Board2.setShipNum(num);
	P2Board2.setShipsVector(num);
	P2Board2.setShipsLeft(num);
}

void Executive::P1Place()
{
	bool placing = true;
	int count = m_shipNum;

	while (placing)
	{
		cout << "\n----------------------------------------\n";
		cout << "           --Player 1 board--             \n";
		cout << "\n----------------------------------------\n";
		P1Board1.printBoard();
		int c;

		while ((c = getchar()) != '\n' && c != EOF);

		if (count == m_shipNum)//count=6
		{
			cout << "\n ----------------------------------------\n";
			cout << "\nLet's start with the 1x1 ship!\n";
			cout << "Player 1, What row would you like to place the 1x1 ship: ";
			row2 = row1 = inputNumber(1, 10);

			cout << "Player 1, What column would you like to place the 1x1 ship: ";
			col2 = col1 = inputAlphabet('A', 'J');
		}
		else
		{
			cout << "\n----------------------------------------\nThis is a 1x" << (m_shipNum - count) + 1 << " ship.\n";
			cout << "Player 1, What row would you like to place the front of the ship: ";
			row1 = inputNumber(1, 10);

			cout << "Player 1, What column would you like to place the front of the ship: ";
			col1 = inputAlphabet('A', 'J');

			cout << "Player 1, What row would you like to place the back of the ship: ";
			row2 = inputNumber(1, 10);

			cout << "Player 1, What column would you like to place the back of the ship: ";
			col2 = inputAlphabet('A', 'J');
		}

		bool check1xN = P1Board1.checkForShips(row1, col1, row2, col2, count);

		if (check1xN == 0)
		{
			cout << "Invalid placement, please try again\n";
		}
		else
		{

			P1Board1.placeShips(row1, col1, row2, col2, m_shipNum - count);
			P1Board1.printBoard();
			cout << "\n----------------------------------------\n";
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";
			count--;
		}
		//6 5 4 3 2 1
		if (count == 0)
		{
			placing = false;
		}
	}
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

void Executive::P2Place()
{
	bool placing = true;
	int count = m_shipNum;
	while (placing)
	{
		cout << "\n----------------------------------------\n";
		cout << "           --Player 2 board--             \n";
		cout << "\n----------------------------------------\n";
		P2Board2.printBoard();
		int c;

		while ((c = getchar()) != '\n' && c != EOF);

		if (count == m_shipNum)//count=6
		{
			cout << "\n ----------------------------------------\n";
			cout << "\nLet's start with the 1x1 ship!\n";
			cout << "Player 2, What row would you like to place the 1x1 ship: ";
			row2 = row1 = inputNumber(1, 10);

			cout << "Player 2, What column would you like to place the 1x1 ship: ";
			col2 = col1 = inputAlphabet('A', 'J');
		}
		else
		{
			cout << "\n----------------------------------------\nThis is a 1x" << (m_shipNum - count) + 1 << " ship.\n";//count=(6-5)+1=2
			cout << "Player 2, What row would you like to place the front of the ship: ";
			row1 = inputNumber(1, 10);

			cout << "Player 2, What column would you like to place the front of the ship: ";
			col1 = inputAlphabet('A', 'J');

			cout << "Player 2, What row would you like to place the back of the ship: ";
			row2 = inputNumber(1, 10);

			cout << "Player 2, What column would you like to place the back of the ship: ";
			col2 = inputAlphabet('A', 'J');
		}

		bool check1xN = P2Board2.checkForShips(row1, col1, row2, col2, count);

		if (check1xN == 0)
		{
			cout << "\nInvalid placement, please try again\n\n----------------------------------------\n";
		}
		else
		{

			P2Board2.placeShips(row1, col1, row2, col2, m_shipNum - count);
			P2Board2.printBoard();
			std::cout << "\n----------------------------------------\n";
			std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";

			count--;//count=5
		}

		if (count == 0)
		{
			placing = false;
		}
	}
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

void Executive::P1Attack(int mode, int leader, int turn, bool& abilityused)
{
	int row;
	int col;
	bool preuse = abilityused;
	bool attack = true;
	cout << "\n----------------------------------------\n";
	cout << "           --Player 1 board--             \n";
	cout << "\n----------------------------------------\n";
	cout << "--This is the location of Your ships--\n";
	P1Board1.printBoard();
	cout << "\n\n--This is what you attacked--\n";
	P1AttackBoard.printBoard();
	cout << "\n----------------------------------------\n";
	while (attack)
	{
		cout << "Player 1 turn to attack" << endl;
		if (mode == 3)
		{
		abilityused = AbilityPrompt(leader, abilityused, 1);
		}
		if (preuse == abilityused)
		{
			cout << "Select Row number: ";

			row = inputNumber(1, 10);

			cout << "\nSelect Column letter: ";

			col = inputAlphabet('A', 'J');

			cout << "Value: " << P1AttackBoard.checkCoordinates(row - 1, col - 1) << "\n";
			if (P1AttackBoard.checkCoordinates(row - 1, col - 1) == 'M' || P1AttackBoard.checkCoordinates(row - 1, col - 1) == 'H')
			{
				cout << "You have already hit or miss here! Choose a new coordinate \n";
				continue;
			}
			else if (P2Board2.checkCoordinates(row - 1, col - 1) == 'S')
			{
				cout << "You hit a ship!\n";
				P1AttackBoard.update(row - 1, col - 1, 'H');
				P2Board2.update(row - 1, col - 1, 'H');
				if (P2Board2.isSunk(row - 1, col - 1))
				{
					P2Board2.sinkShip();
					cout << "You have sunk a ship!\n";
				}

				if (P2Board2.getShipsLeft() == 0)
				{
					player1Won = true;
				}
			}
			else
			{
				P1AttackBoard.update(row - 1, col - 1, 'M');
				cout << "You missed!\n";
			}

			cout << "\n----------------------------------------\n";
			cout << "--This is location of your own ships--\n";
			P1Board1.printBoard();
			cout << "\n\n--This is what you attacked--\n";
			P1AttackBoard.printBoard();
			cout << "\n----------------------------------------\n";
			attack = false;
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";
		}
		attack = false;
	}
}

void Executive::P2Attack(int mode, int leader, int turn2, bool& abilityused2)
{
	int row;
	int col;
	bool preuse = abilityused2;
	bool attack = true;
	cout << "\n----------------------------------------\n";
	cout << "           --Player 2 board--             \n";
	cout << "\n----------------------------------------\n";
	cout << "--This is location of your own ships--\n";
	P2Board2.printBoard();
	cout << "\n\n--This is what you attacked--\n";
	P2AttackBoard.printBoard();
	cout << "\n----------------------------------------\n";
	while (attack)
	{
		cout << "Player 2 turn to attack" << endl;
		if (mode == 3)
		{
		abilityused2 = AbilityPrompt(leader, abilityused2, 2);
		}

		if (preuse == abilityused2)
		{
			cout << "Select Row number: ";


			row = inputNumber(1, 10);

			cout << "\nSelect Column letter: ";

			col = inputAlphabet('A', 'J');

			cout << "Value: " << P2AttackBoard.checkCoordinates(row - 1, col - 1) << "\n";
			if (P2AttackBoard.checkCoordinates(row - 1, col - 1) == 'M' || P2AttackBoard.checkCoordinates(row - 1, col - 1) == 'H')
			{
				cout << "You have already hit or miss here! Choose a new coordinate \n";
				continue;
			}
			else if (P1Board1.checkCoordinates(row - 1, col - 1) == 'S')
			{
				cout << "You hit a ship!\n";
				P2AttackBoard.update(row - 1, col - 1, 'H');
				P1Board1.update(row - 1, col - 1, 'H');
				if (P1Board1.isSunk(row - 1, col - 1))
				{
					P1Board1.sinkShip();
					cout << "You have sunk a ship!\n";

				}

				if (P1Board1.getShipsLeft() == 0)
				{
					player2Won = true;
				}
			}
			else
			{
				P2AttackBoard.update(row - 1, col - 1, 'M');
				cout << "You missed!\n";
			}
			cout << "\n----------------------------------------\n";
			cout << "--This is location of your own ships--\n";
			P2Board2.printBoard();
			cout << "\n\n--This is what you attacked--\n";
			P2AttackBoard.printBoard();
			cout << "\n----------------------------------------\n";
			attack = false;
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";
		}
		attack = false;
	}
}

bool Executive::P1Won()
{
	return player1Won;
}

bool Executive::P2Won()
{
	return player2Won;
}

//Fix the row input.
int Executive::inputNumber(int begin, int end)
{
	int v;
	while (true) {
		if (cin >> v) {
			if (v >= begin && v <= end) {
				break;
			}
			else {
				cout << "The input range is not valid! please retry input!" << endl;
			}
		}
		else {
			cout << "input not a number! please retry input!" << endl;
			cin.clear();
			cin.ignore();
		}
	}
	return v;
}

//Convert char to number, and also check if the input in a valid range
int Executive::inputAlphabet(char begin, char end) {
	char v;
	while (true) {
		if (cin >> v)
		{
			//Convert lower case to uppercase
			if (islower(v))
			{
				v = toupper(v);
			}
			if (v >= begin && v <= end) {
				break;
			}
			else {
				cout << "The input range is not valid! please retry input!" << endl;
			}
		}
		else {
			cout << "input not a alphabet! please retry input!" << endl;
			cin.clear();
			cin.ignore();
		}
	}
	return (v - begin) + 1;
}

void Executive::AIPlacement()
{
	bool placing = true;
	int count = m_shipNum;
	srand(time(0));

	while (placing)
	{
		row1 = rand() % 10 + 1;
		col1 = rand() % 10 + 1;
		int orientation = rand() % 2;

		if (orientation == 0)
		{
			row2 = row1 + (m_shipNum - count);
			col2 = col1;
		}
		else
		{
			col2 = col1 + (m_shipNum - count);
			row2 = row1;
		}

		bool check1xN = P2Board2.checkForShips(row1, col1, row2, col2, count);
		if ((col1 + (m_shipNum - count) + 1 > 10) && (orientation == 1))
		{
			check1xN = false;
		}
		else if ((row1 + (m_shipNum - count) + 1 > 10) && (orientation == 0))
		{
			check1xN = false;
		}

		if (check1xN == true)
		{
			P2Board2.placeShips(row1, col1, row2, col2, m_shipNum - count);
			count--;
		}
		if (count == 0)
		{
			placing = false;
		}
	}
	cout << "AI Ships have been placed." << endl;
}

void Executive::LaserH(int row, int player)
{
	if (player == 1)
	{
		for (int i = 0; i < 10; i++)
		{
			if (P2Board2.checkCoordinates(row, i) == 'S')
			{
				cout << "You hit a ship\n";
				P2Board2.update(row, i, 'H');
				P1AttackBoard.update(row, i, 'H');
				if (P2Board2.isSunk(row, i))
				{
					P2Board2.sinkShip();
					cout << "You have sunk a ship!\n";
				}
				if (P2Board2.getShipsLeft() == 0)
				{
					player1Won = true;
				}
			}
			else
			{
				P2Board2.update(row, i, 'M');
				P1AttackBoard.update(row, i, 'M');
				cout << "You missed!\n";
			}
		}
	}
	else if (player == 2)
	{
		for (int i = 0; i < 10; i++)
		{
			if (P1Board1.checkCoordinates(row, i) == 'S')
			{
				cout << "You hit a ship!\n";
				P1Board1.update(row, i, 'H');
				P2AttackBoard.update(row, i, 'H');
				if (P2Board2.isSunk(row, i))
				{
					P2Board2.sinkShip();
					cout << "You have sunk a ship!\n";
				}
				if (P2Board2.getShipsLeft() == 0)
				{
					player1Won = true;
				}
			}
			else
			{
				P1Board1.update(row, i, 'M');
				P2AttackBoard.update(row, i, 'M');
				cout << "You missed!\n";
			}
		}
	}
}

void Executive::LaserV(int col, int player)
{
	if (player == 1)
	{
		for (int i = 0; i < 10; i++)
		{
			if (P2Board2.checkCoordinates(i, col) == 'S')
			{
				cout << "You hit a ship!\n";
				P2Board2.update(i, col, 'H');
				P1AttackBoard.update(i, col, 'H');
				if (P2Board2.isSunk(i, col))
				{
					P2Board2.sinkShip();
					cout << "You have sunk a ship!\n";
				}
				if (P2Board2.getShipsLeft() == 0)
				{
					player1Won = true;
				}
			}
			else
			{
				P2Board2.update(i, col, 'M');
				P1AttackBoard.update(i, col, 'M');
				cout << "You missed!\n";
			}
		}
	}
	else if (player == 2)
	{
		for (int i = 0; i < 10; i++)
		{
			if (P1Board1.checkCoordinates(i, col) == 'S')
			{
				cout << "You hit a ship!\n";
				P1Board1.update(i, col, 'H');
				P2AttackBoard.update(i, col, 'H');
				if (P2Board2.isSunk(i, col))
				{
					P2Board2.sinkShip();
					cout << "You have sunk a ship!\n";
				}
				if (P2Board2.getShipsLeft() == 0)
				{
					player1Won = true;
				}
			}
			else
			{
				P1Board1.update(i, col, 'M');
				P2AttackBoard.update(i, col, 'M');
				cout << "You missed!\n";
			}
		}
	}
}

bool Executive::AbilityPrompt(int leader, bool abilityused, int player)
{
	if (abilityused == false)
	{
		int error = 0;
		string useability = "";
		string abilityname = "";
		cout << "Would you like to use your ability (y/n): ";
		if (leader == 1)
		{
			cout << "Laser\n";
			abilityname = "Laser\n";
		}
		else if (leader == 2)
		{
			cout << "RailGun\n";
			abilityname = "RailGun\n";
		}
		else if (leader == 3)
		{
			cout << "Rain of Death\n";
			abilityname = "Rain of Death\n";
		}
		else if (leader == 4)
		{
			cout << "Ring of Fire\n";
			abilityname = "Ring of Fire\n";
		}
		else
		{
			cout << "An error has occured.\n";
			abilityname = "ERROR\n";
		}

		do
		{
			cin >> useability;
			if (useability == "y" || useability == "yes")
			{
				cout << "You have chosen to use the ability: " << abilityname << endl;
				if (leader == 1)
				{
					string horiOrVert = "";
					int error1 = 0;
					int error2 = 0;
					int error3 = 0;

					int row = 0;
					int col = 0;
					cout << "Initiate Vertical or Horizontal Laser Cannon (h/v)? ";
					do
					{
						cin >> horiOrVert;
						if  ((horiOrVert == "h")||(horiOrVert == "H"))
						{
							cout << "Which row would you like to impact? ";
							row = inputNumber(1, 10) - 1;
							LaserH(row, player);

						}
						else if ((horiOrVert == "v")||(horiOrVert == "V"))
						{
							cout << "Which column would you like to impact (A-J)? ";
							col = inputAlphabet('A', 'J') - 1;
							LaserV(col, player);
						}
						else
						{
							error1 = 1;
							cout << "Not a valid choice! Please input 'h' or 'v'\n";
						}
				} while(error1 == 1);
			}
			else if (leader == 2)
			{
				RailGun(player);
			}
			else if (leader == 3)
			{
				rainOfDeath(player);
			}
			else if (leader == 4)
			{
				string horiOrVert = "";
				int error1 = 0;

				int row = 0;
				int col = 0;
				cout << "You will enter in the top right hand corner of the box you would like to attack." << endl;
				cout << "Initiate Vertical or Horizontal Ring of Fire (h/v)? ";
				do
				{
					cin >> horiOrVert;
					if ((horiOrVert == "h")||(horiOrVert == "H"))
					{
						cout << "Input in the row you would like the top right hand corner to be (1-10) ";
						row = inputNumber(1, 10) - 1;

						cout << "Input in the column you would like the top right hand column to be (A-J) ";
						col = inputAlphabet('A', 'J') - 1;

						ringOfFireH(row, col, player);

					}
					else if ((horiOrVert == "v")||(horiOrVert == "V"))
					{
						cout << "Input in the row you would like the top right hand corner to be (1-10) ";
						row = inputNumber(1, 10) - 1;

						cout << "Input in the column you would like the top right hand column to be (A-J) ";
						col = inputAlphabet('A', 'J') - 1;

						ringOfFireV(row, col, player);
					}
					else
					{
						error1 = 1;
						cout << "Not a valid choice! Please input 'h' or 'v'\n";
					}
				} while(error1 == 1);
			}
				abilityused = true;
				return abilityused;
			}
			else if (useability == "n" || useability == "no")
			{
					cout << "You did not use your ability.\n";
				return abilityused;
			}
			else
			{
				error = 1;
				cout << "Not a valid choice! Please input 'y' or 'n'\n";
			}
		} while (error == 1);
	}
}

void Executive::clrscn() {
	std::cout << "\x1b[2J";
}

Point Executive::AIAttack(int difficulty, Point previous, vector<vector<pair<int, int>>> cheat, int& ship, int& hit)
{
	int row = 0;
	int col = 0;
	bool attack = true;
	srand(time(0));
	if (difficulty == 1)
	{
		while (attack)
		{
			row = rand() % 10 + 1;
			col = rand() % 10 + 1;
			while (P2AttackBoard.checkCoordinates(row - 1, col - 1) == 'M' || P2AttackBoard.checkCoordinates(row - 1, col - 1) == 'H')
			{
				row = rand() % 10 + 1;
				col = rand() % 10 + 1;
			}
			if (P1Board1.checkCoordinates(row - 1, col - 1) == 'S')
			{
				P2AttackBoard.update(row - 1, col - 1, 'H');
				P1Board1.update(row - 1, col - 1, 'H');
				if (P1Board1.isSunk(row - 1, col - 1))
				{
					P1Board1.sinkShip();
				}

				if (P1Board1.getShipsLeft() == 0)
				{
					player2Won = true;
				}
			}
			else
			{
				P2AttackBoard.update(row - 1, col - 1, 'M');
			}
			cout << "This is what the AI has tried to hit" << endl;
			P2AttackBoard.printBoard();
			attack = false;
		}
	}
	else if (difficulty == 2)
	{
		if (previous.h == 0 && previous.s == 0)
		{
			while (attack)
			{
				row = rand() % 10 + 1;
				col = rand() % 10 + 1;
				while (P2AttackBoard.checkCoordinates(row - 1, col - 1) == 'M' || P2AttackBoard.checkCoordinates(row - 1, col - 1) == 'H')
				{
					row = rand() % 10 + 1;
					col = rand() % 10 + 1;
				}
				if (P1Board1.checkCoordinates(row - 1, col - 1) == 'S')
				{
					P2AttackBoard.update(row - 1, col - 1, 'H');
					P1Board1.update(row - 1, col - 1, 'H');
					previous.h = 1;
					previous.s = 1;
					previous.hx = row;
					previous.hy = col;
					previous.firstx = row;
					previous.firsty = col;
					if (P1Board1.isSunk(row - 1, col - 1))
					{
						P1Board1.sinkShip();
						previous.s = 0;
						previous.h = 0;
						previous.hx = 0;
						previous.hy = 0;
						previous.firstx = 0;
						previous.firsty = 0;
					}

					if (P1Board1.getShipsLeft() == 0)
					{
						player2Won = true;
					}
				}
				else
				{
					P2AttackBoard.update(row - 1, col - 1, 'M');
					previous.h = 0;
				}
				cout << "This is what the AI has tried to hit" << endl;
				P2AttackBoard.printBoard();
				attack = false;
			}
		}
		else
		{
			row = previous.hx;
			col = previous.hy;
			int i = 0;
			while (P2AttackBoard.checkCoordinates(row - 1, col - 1) == 'M' || P2AttackBoard.checkCoordinates(row - 1, col - 1) == 'H')
			{
				if (i == 0)
				{
					row = previous.hx;
					col = previous.hy + 1;
				}
				else if (i == 1)
				{
					row = previous.hx;
					col = previous.hy - 1;
				}
				else if (i == 2)
				{
					row = previous.hx - 1;
					col = previous.hy;
				}
				else if (i == 3)
				{
					row = previous.hx + 1;
					col = previous.hy;
				}
				if (i > 3)
				{
					row = previous.firstx;
					col = previous.firsty;
					int j = 0;
					while (P2AttackBoard.checkCoordinates(row - 1, col - 1) == 'M' || P2AttackBoard.checkCoordinates(row - 1, col - 1) == 'H')
					{
						if (j == 0)
						{
							row = previous.firstx;
							col = previous.firsty + 1;
						}
						else if (j == 1)
						{
							row = previous.firstx;
							col = previous.firsty - 1;
						}
						else if (j == 2)
						{
							row = previous.firstx - 1;
							col = previous.firsty;
						}
						else if (j == 3)
						{
							row = previous.firstx + 1;
							col = previous.firsty;
						}
						j++;
					}
				}
				i++;
			}
			if (P1Board1.checkCoordinates(row - 1, col - 1) == 'S')
			{
				P2AttackBoard.update(row - 1, col - 1, 'H');
				P1Board1.update(row - 1, col - 1, 'H');
				previous.h = 1;
				previous.s = 1;
				previous.hx = row;
				previous.hy = col;
				if (P1Board1.isSunk(row - 1, col - 1))
				{
					P1Board1.sinkShip();
					previous.s = 0;
					previous.h = 0;
					previous.hx = 0;
					previous.hy = 0;
					previous.firstx = 0;
					previous.firsty = 0;
				}

				if (P1Board1.getShipsLeft() == 0)
				{
					player2Won = true;
				}
			}
			else
			{
				P2AttackBoard.update(row - 1, col - 1, 'M');
				previous.h = 0;
			}
			cout << "This is what the AI has tried to hit" << endl;
			P2AttackBoard.printBoard();
			attack = false;
		}
	}
	else if (difficulty == 3)
	{
		row = cheat[ship][hit].first;
		col = cheat[ship][hit].second;
		if (P1Board1.checkCoordinates(row, col) == 'S')
		{
			P2AttackBoard.update(row, col, 'H');
			P1Board1.update(row, col, 'H');
			hit++;
			if (P1Board1.isSunk(row, col))
			{
				P1Board1.sinkShip();
				ship++;
				hit = 0;
			}

			if (P1Board1.getShipsLeft() == 0)
			{
				player2Won = true;
			}
		}

		cout << "This is what the AI has tried to hit" << endl;
		P2AttackBoard.printBoard();
	}
	previous.x = row;
	previous.y = col;
	return previous;
}

vector<vector<pair<int, int>>> Executive::cheatGet()
{
	return P1Board1.getCoordinates();
}

void Executive::rainOfDeath(int player)
{
	srand(time(0));
	int row = 0;
	int col = 0;
	if (player == 1)
	{
		for (int i = 0; i < 10; i++)
		{
			row = rand() % 10;
			col = rand() % 10;
			if (P2Board2.checkCoordinates(row, col) == 'S')
			{
				cout << "You hit a ship!\n";
				P2Board2.update(row, col, 'H');
				P1AttackBoard.update(row, col, 'H');
				if (P2Board2.isSunk(row, col))
				{
					P2Board2.sinkShip();
					cout << "You have sunk a ship!\n";
				}

				if (P2Board2.getShipsLeft() == 0)
				{
					player1Won = true;
				}
			}
			else
			{
				P2Board2.update(row, col, 'M');
				P1AttackBoard.update(row, col, 'M');
				cout << "You missed!\n";
			}
		}
	}
	else if (player == 2)
	{
		for (int i = 0; i < 10; i++)
		{
			row = rand() % 10;
			col = rand() % 10;
			if (P1Board1.checkCoordinates(row, col) == 'S')
			{
				cout << "You hit a ship!\n";
				P1Board1.update(row, col, 'H');
				P2AttackBoard.update(row, col, 'H');
				if (P2Board2.isSunk(row, col))
				{
					P2Board2.sinkShip();
					cout << "You have sunk a ship!\n";
				}
				if (P2Board2.getShipsLeft() == 0)
				{
					player1Won = true;
				}
			}
			else
			{
				P1Board1.update(row, col, 'M');
				P2AttackBoard.update(row, col, 'M');
				cout << "You missed!\n";
			}
		}
	}
}

void Executive::RailGun(int player)
{
	int row = 0;
	int col = 0;
	int direction = 0;
	if (player == 1)
	{
		cout << "The shot will spray out in a triangle, like so" << endl;
		cout << "....." << endl << " ..." << endl << "  ." << endl;
		cout << "Enter in the row that you would like the single spot to be: ";
		row = inputNumber(1, 10) - 1;
		cout << "Enter in the column that you would like the single spot to be: ";
		col = inputAlphabet('A', 'J') - 1;
		cout << "Enter in the direction you would like the spray to face: " << endl;
		cout << "1 for upwards" << endl << "2 for towards the right" << endl << "3 for downward" << endl << "4 for towards the left" << endl;
		cin >> direction;
		while (direction != 1 && direction != 2 && direction != 3 && direction != 4)
		{
			cout << "Not valid, try again" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> direction;
		}
		switch (direction)
		{
			case 1:
				for (int i = 0; i < 3; i++)
				{
					if (row - i >= 0)
					{
						if (P2Board2.checkCoordinates(row- i, col) == 'S')
						{
							P2Board2.update(row - i, col, 'H');
							P1AttackBoard.update(row - i, col, 'H');
							if (P2Board2.isSunk(row - i, col))
							{
								P2Board2.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P2Board2.getShipsLeft() == 0)
							{
								player1Won = true;
							}
						}
						else
						{
							P2Board2.update(row - i, col, 'M');
							P1AttackBoard.update(row - i, col, 'M');
						}
						if (i == 1)
						{
							if (col + 1 < 10)
							{
								if (P2Board2.checkCoordinates(row - i, col + 1) == 'S')
								{
									P2Board2.update(row - i, col + 1, 'H');
									P1AttackBoard.update(row - i, col + 1, 'H');
									if (P2Board2.isSunk(row - i, col + 1))
									{
										P2Board2.sinkShip();
										cout << "You have sunk a ship!\n";
									}

									if (P2Board2.getShipsLeft() == 0)
									{
										player1Won = true;
									}
								}
								else
								{
									P2Board2.update(row - i, col + 1, 'M');
									P1AttackBoard.update(row - i, col + 1, 'M');
								}
							}
							if (col - 1 >= 0)
							{
								if (P2Board2.checkCoordinates(row - i, col - 1) == 'S')
								{
									P2Board2.update(row - i, col - 1, 'H');
									P1AttackBoard.update(row - i, col - 1, 'H');
									if (P2Board2.isSunk(row - i, col - 1))
									{
										P2Board2.sinkShip();
										cout << "You have sunk a ship!\n";
									}

									if (P2Board2.getShipsLeft() == 0)
									{
										player1Won = true;
									}
								}
								else
								{
									P2Board2.update(row - i, col - 1, 'M');
									P1AttackBoard.update(row - i, col - 1, 'M');
								}
							}
						}
						else if (i == 2)
						{
							if (col + 1 < 10)
							{
								if (P2Board2.checkCoordinates(row - i, col + 1) == 'S')
								{
									P2Board2.update(row - i, col + 1, 'H');
									P1AttackBoard.update(row - i, col + 1, 'H');
									if (P2Board2.isSunk(row - i, col + 1))
									{
										P2Board2.sinkShip();
										cout << "You have sunk a ship!\n";
									}

									if (P2Board2.getShipsLeft() == 0)
									{
										player1Won = true;
									}
								}
								else
								{
									P2Board2.update(row - i, col + 1, 'M');
									P1AttackBoard.update(row - i, col + 1, 'M');
								}
							}
							if (col - 1 >= 0)
							{
								if (P2Board2.checkCoordinates(row - i, col - 1) == 'S')
								{
									P2Board2.update(row - i, col - 1, 'H');
									P1AttackBoard.update(row - i, col - 1, 'H');
									if (P2Board2.isSunk(row - i, col - 1))
									{
										P2Board2.sinkShip();
										cout << "You have sunk a ship!\n";
									}

									if (P2Board2.getShipsLeft() == 0)
									{
										player1Won = true;
									}
								}
								else
								{
									P2Board2.update(row - i, col - 1, 'M');
									P1AttackBoard.update(row - i, col - 1, 'M');
								}
							}
							if (col + 2 < 10)
							{
								if (P2Board2.checkCoordinates(row - i, col + 2) == 'S')
								{
									P2Board2.update(row - i, col + 2, 'H');
									P1AttackBoard.update(row - i, col + 2, 'H');
									if (P2Board2.isSunk(row - i, col + 2))
									{
										P2Board2.sinkShip();
										cout << "You have sunk a ship!\n";
									}

									if (P2Board2.getShipsLeft() == 0)
									{
										player1Won = true;
									}
								}
								else
								{
									P2Board2.update(row - i, col + 2, 'M');
									P1AttackBoard.update(row - i, col + 2, 'M');
								}
							}
							if (col - 2 >= 0)
							{
								if (P2Board2.checkCoordinates(row - i, col - 2) == 'S')
								{
									P2Board2.update(row - i, col - 2, 'H');
									P1AttackBoard.update(row - i, col - 2, 'H');
									if (P2Board2.isSunk(row - i, col - 2))
									{
										P2Board2.sinkShip();
										cout << "You have sunk a ship!\n";
									}

									if (P2Board2.getShipsLeft() == 0)
									{
										player1Won = true;
									}
								}
								else
								{
									P2Board2.update(row - i, col - 2, 'M');
									P1AttackBoard.update(row - i, col - 2, 'M');
								}
							}
						}
					}
				}
				break;
			case 2:
				for (int i = 0; i < 3; i++)
				{
					if (col + i < 10)
					{
						if (P2Board2.checkCoordinates(row, col + i) == 'S')
						{
							P2Board2.update(row, col + i, 'H');
							P1AttackBoard.update(row, col + i, 'H');
							if (P2Board2.isSunk(row, col + i))
							{
								P2Board2.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P2Board2.getShipsLeft() == 0)
							{
								player1Won = true;
							}
						}
						else
						{
							P2Board2.update(row, col + i, 'M');
							P1AttackBoard.update(row, col + i, 'M');
						}
						if (i == 1)
						{
							if (row + 1 < 10)
							{
								if (P2Board2.checkCoordinates(row + 1, col + i) == 'S')
								{
									P2Board2.update(row + 1, col + i, 'H');
									P1AttackBoard.update(row + 1, col + i, 'H');
									if (P2Board2.isSunk(row + 1, col + i))
									{
										P2Board2.sinkShip();
										cout << "You have sunk a ship!\n";
									}

									if (P2Board2.getShipsLeft() == 0)
									{
										player1Won = true;
									}
								}
								else
								{
									P2Board2.update(row + 1, col + i, 'M');
									P1AttackBoard.update(row + 1, col + i, 'M');
								}
							}
							if (row - 1 >= 0)
							{
								if (P2Board2.checkCoordinates(row - 1, col + i) == 'S')
								{
									P2Board2.update(row - 1, col + i, 'H');
									P1AttackBoard.update(row - 1, col + i, 'H');
									if (P2Board2.isSunk(row - 1, col + i))
									{
										P2Board2.sinkShip();
										cout << "You have sunk a ship!\n";
									}

									if (P2Board2.getShipsLeft() == 0)
									{
										player1Won = true;
									}
								}
								else
								{
									P2Board2.update(row - 1, col + i, 'M');
									P1AttackBoard.update(row - 1, col + i, 'M');
								}
							}
						}
						else if (i == 2)
						{
							if (row + 1 < 10)
							{
								if (P2Board2.checkCoordinates(row + 1, col + i) == 'S')
								{
									P2Board2.update(row + 1, col + i, 'H');
									P1AttackBoard.update(row + 1, col + i, 'H');
									if (P2Board2.isSunk(row + 1, col + i))
									{
										P2Board2.sinkShip();
										cout << "You have sunk a ship!\n";
									}

									if (P2Board2.getShipsLeft() == 0)
									{
										player1Won = true;
									}
								}
								else
								{
									P2Board2.update(row + 1, col + i, 'M');
									P1AttackBoard.update(row + 1, col + i, 'M');
								}
							}
							if (row - 1 >= 0)
							{
								if (P2Board2.checkCoordinates(row - 1, col + i) == 'S')
								{
									P2Board2.update(row - 1, col + i, 'H');
									P1AttackBoard.update(row - 1, col + i, 'H');
									if (P2Board2.isSunk(row - 1, col + i))
									{
										P2Board2.sinkShip();
										cout << "You have sunk a ship!\n";
									}

									if (P2Board2.getShipsLeft() == 0)
									{
										player1Won = true;
									}
								}
								else
								{
									P2Board2.update(row - 1, col + i, 'M');
									P1AttackBoard.update(row - 1, col + i, 'M');
								}
							}
							if (row + 2 < 10)
							{
								if (P2Board2.checkCoordinates(row + 2, col + i) == 'S')
								{
									P2Board2.update(row + 2, col + i, 'H');
									P1AttackBoard.update(row + 2, col + i, 'H');
									if (P2Board2.isSunk(row + 2, col + i))
									{
										P2Board2.sinkShip();
										cout << "You have sunk a ship!\n";
									}

									if (P2Board2.getShipsLeft() == 0)
									{
										player1Won = true;
									}
								}
								else
								{
									P2Board2.update(row + 2, col + i, 'M');
									P1AttackBoard.update(row + 2, col + i, 'M');
								}
							}
							if (row - 2 >= 0)
							{
								if (P2Board2.checkCoordinates(row - 2, col + i) == 'S')
								{
									P2Board2.update(row - 2, col + i, 'H');
									P1AttackBoard.update(row - 2, col + i, 'H');
									if (P2Board2.isSunk(row - 2, col + i))
									{
										P2Board2.sinkShip();
										cout << "You have sunk a ship!\n";
									}

									if (P2Board2.getShipsLeft() == 0)
									{
										player1Won = true;
									}
								}
								else
								{
									P2Board2.update(row - 2, col + i, 'M');
									P1AttackBoard.update(row - 2, col + i, 'M');
								}
							}
						}
					}
				}
				break;
			case 3:
				for (int i = 0; i < 3; i++)
				{
					if (row + i <= 10)
					{
						if (P2Board2.checkCoordinates(row + i, col) == 'S')
						{
							P2Board2.update(row + i, col, 'H');
							P1AttackBoard.update(row + i, col, 'H');
							if (P2Board2.isSunk(row + i, col))
							{
								P2Board2.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P2Board2.getShipsLeft() == 0)
							{
								player1Won = true;
							}
						}
						else
						{
							P2Board2.update(row + i, col, 'M');
							P1AttackBoard.update(row + i, col, 'M');
						}
						if (i == 1)
						{
							if (col + 1 < 10)
							{
								if (P2Board2.checkCoordinates(row + i, col + 1) == 'S')
								{
									P2Board2.update(row + i, col + 1, 'H');
									P1AttackBoard.update(row + i, col + 1, 'H');
									if (P2Board2.isSunk(row + i, col + 1))
									{
										P2Board2.sinkShip();
										cout << "You have sunk a ship!\n";
									}

									if (P2Board2.getShipsLeft() == 0)
									{
										player1Won = true;
									}
								}
								else
								{
									P2Board2.update(row + i, col + 1, 'M');
									P1AttackBoard.update(row + i, col + 1, 'M');
								}
							}
							if (col - 1 >= 0)
							{
								if (P2Board2.checkCoordinates(row + i, col - 1) == 'S')
								{
									P2Board2.update(row + i, col - 1, 'H');
									P1AttackBoard.update(row + i, col - 1, 'H');
									if (P2Board2.isSunk(row + i, col - 1))
									{
										P2Board2.sinkShip();
										cout << "You have sunk a ship!\n";
									}

									if (P2Board2.getShipsLeft() == 0)
									{
										player1Won = true;
									}
								}
								else
								{
									P2Board2.update(row + i, col - 1, 'M');
									P1AttackBoard.update(row + i, col - 1, 'M');
								}
							}
						}
						else if (i == 2)
						{
							if (col + 1 < 10)
							{
								if (P2Board2.checkCoordinates(row + i, col + 1) == 'S')
								{
									P2Board2.update(row + i, col + 1, 'H');
									P1AttackBoard.update(row + i, col + 1, 'H');
									if (P2Board2.isSunk(row + i, col + 1))
									{
										P2Board2.sinkShip();
										cout << "You have sunk a ship!\n";
									}

									if (P2Board2.getShipsLeft() == 0)
									{
										player1Won = true;
									}
								}
								else
								{
									P2Board2.update(row + i, col + 1, 'M');
									P1AttackBoard.update(row + i, col + 1, 'M');
								}
							}
							if (col - 1 >= 0)
							{
								if (P2Board2.checkCoordinates(row + i, col - 1) == 'S')
								{
									P2Board2.update(row + i, col - 1, 'H');
									P1AttackBoard.update(row - i, col - 1, 'H');
									if (P2Board2.isSunk(row - i, col - 1))
									{
										P2Board2.sinkShip();
										cout << "You have sunk a ship!\n";
									}

									if (P2Board2.getShipsLeft() == 0)
									{
										player1Won = true;
									}
								}
								else
								{
									P2Board2.update(row + i, col - 1, 'M');
									P1AttackBoard.update(row + i, col - 1, 'M');
								}
							}
							if (col + 2 < 10)
							{
								if (P2Board2.checkCoordinates(row + i, col + 2) == 'S')
								{
									P2Board2.update(row + i, col + 2, 'H');
									P1AttackBoard.update(row + i, col + 2, 'H');
									if (P2Board2.isSunk(row + i, col + 2))
									{
										P2Board2.sinkShip();
										cout << "You have sunk a ship!\n";
									}

									if (P2Board2.getShipsLeft() == 0)
									{
										player1Won = true;
									}
								}
								else
								{
									P2Board2.update(row + i, col + 2, 'M');
									P1AttackBoard.update(row + i, col + 2, 'M');
								}
							}
							if (col - 2 >= 0)
							{
								if (P2Board2.checkCoordinates(row + i, col - 2) == 'S')
								{
									P2Board2.update(row - i, col + 2, 'H');
									P1AttackBoard.update(row + i, col - 2, 'H');
									if (P2Board2.isSunk(row + i, col - 2))
									{
										P2Board2.sinkShip();
										cout << "You have sunk a ship!\n";
									}

									if (P2Board2.getShipsLeft() == 0)
									{
										player1Won = true;
									}
								}
								else
								{
									P2Board2.update(row + i, col - 2, 'M');
									P1AttackBoard.update(row + i, col - 2, 'M');
								}
							}
						}
					}
				}
				break;
			case 4:
				for (int i = 0; i < 3; i++)
				{
					if (col - i >= 0)
					{
						if (P2Board2.checkCoordinates(row, col - i) == 'S')
						{
							P2Board2.update(row, col - i, 'H');
							P1AttackBoard.update(row, col - i, 'H');
							if (P2Board2.isSunk(row, col - i))
							{
								P2Board2.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P2Board2.getShipsLeft() == 0)
							{
								player1Won = true;
							}
						}
						else
						{
							P2Board2.update(row, col - i, 'M');
							P1AttackBoard.update(row, col - i, 'M');
						}
						if (i == 1)
						{
							if (row + 1 < 10)
							{
								if (P2Board2.checkCoordinates(row + 1, col - i) == 'S')
								{
									P2Board2.update(row + 1, col - i, 'H');
									P1AttackBoard.update(row + 1, col - i, 'H');
									if (P2Board2.isSunk(row + 1, col - i))
									{
										P2Board2.sinkShip();
										cout << "You have sunk a ship!\n";
									}

									if (P2Board2.getShipsLeft() == 0)
									{
										player1Won = true;
									}
								}
								else
								{
									P2Board2.update(row + 1, col - i, 'M');
									P1AttackBoard.update(row + 1, col - i, 'M');
								}
							}
							if (row - 1 >= 0)
							{
								if (P2Board2.checkCoordinates(row - 1, col - i) == 'S')
								{
									P2Board2.update(row - 1, col - i, 'H');
									P1AttackBoard.update(row - 1, col - i, 'H');
									if (P2Board2.isSunk(row - 1, col - i))
									{
										P2Board2.sinkShip();
										cout << "You have sunk a ship!\n";
									}

									if (P2Board2.getShipsLeft() == 0)
									{
										player1Won = true;
									}
								}
								else
								{
									P2Board2.update(row - 1, col - i, 'M');
									P1AttackBoard.update(row - 1, col - i, 'M');
								}
							}
						}
						else if (i == 2)
						{
							if (row + 1 < 10)
							{
								if (P2Board2.checkCoordinates(row + 1, col - i) == 'S')
								{
									P2Board2.update(row + 1, col - i, 'H');
									P1AttackBoard.update(row + 1, col - i, 'H');
									if (P2Board2.isSunk(row + 1, col - i))
									{
										P2Board2.sinkShip();
										cout << "You have sunk a ship!\n";
									}

									if (P2Board2.getShipsLeft() == 0)
									{
										player1Won = true;
									}
								}
								else
								{
									P2Board2.update(row + 1, col - i, 'M');
									P1AttackBoard.update(row + 1, col - i, 'M');
								}
							}
							if (row - 1 >= 0)
							{
								if (P2Board2.checkCoordinates(row - 1, col - i) == 'S')
								{
									P2Board2.update(row - 1, col - i, 'H');
									P1AttackBoard.update(row - 1, col - i, 'H');
									if (P2Board2.isSunk(row - 1, col - i))
									{
										P2Board2.sinkShip();
										cout << "You have sunk a ship!\n";
									}

									if (P2Board2.getShipsLeft() == 0)
									{
										player1Won = true;
									}
								}
								else
								{
									P2Board2.update(row - 1, col - i, 'M');
									P1AttackBoard.update(row - 1, col - i, 'M');
								}
							}
							if (row + 2 < 10)
							{
								if (P2Board2.checkCoordinates(row + 2, col - i) == 'S')
								{
									P2Board2.update(row + 2, col - i, 'H');
									P1AttackBoard.update(row + 2, col - i, 'H');
									if (P2Board2.isSunk(row + 2, col - i))
									{
										P2Board2.sinkShip();
										cout << "You have sunk a ship!\n";
									}

									if (P2Board2.getShipsLeft() == 0)
									{
										player1Won = true;
									}
								}
								else
								{
									P2Board2.update(row + 2, col - i, 'M');
									P1AttackBoard.update(row + 2, col - i, 'M');
								}
							}
							if (row - 2 >= 0)
							{
								if (P2Board2.checkCoordinates(row - 2, col - i) == 'S')
								{
									P2Board2.update(row - 2, col - i, 'H');
									P1AttackBoard.update(row - 2, col - i, 'H');
									if (P2Board2.isSunk(row - 2, col - i))
									{
										P2Board2.sinkShip();
										cout << "You have sunk a ship!\n";
									}

									if (P2Board2.getShipsLeft() == 0)
									{
										player1Won = true;
									}
								}
								else
								{
									P2Board2.update(row - 2, col - i, 'M');
									P1AttackBoard.update(row - 2, col - i, 'M');
								}
							}
						}
					}
				}
				break;
		}
	}
	else if (player == 2)
	{
	cout << "The shot will spray out in a triangle, like so" << endl;
	cout << "....." << endl << "..." << endl << "." << endl;
	cout << "Enter in the row that you would like the single spot to be: ";
	row = inputNumber(1, 10) - 1;
	cout << "Enter in the column that you would like the single spot to be: ";
	col = inputAlphabet('A', 'J') - 1;
	cout << "Enter in the direction you would like the spray to face: " << endl;
	cout << "1 for upwards" << endl << "2 for towards the right" << endl << "3 for downward" << endl << "4 for towards the left" << endl;
	cin >> direction;
	while (direction != 1 && direction != 2 && direction != 3 && direction != 4)
	{
		cout << "Not valid, try again" << endl;
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> direction;
	}
	switch (direction)
	{
	case 1:
		for (int i = 0; i < 3; i++)
		{
			if (row - i >= 0)
			{
				if (P1Board1.checkCoordinates(row - i, col) == 'S')
				{
					P1Board1.update(row - i, col, 'H');
					P2AttackBoard.update(row - i, col, 'H');
					if (P1Board1.isSunk(row - i, col))
					{
						P1Board1.sinkShip();
						cout << "You have sunk a ship!\n";
					}

					if (P1Board1.getShipsLeft() == 0)
					{
						player2Won = true;
					}
				}
				else
				{
					P1Board1.update(row - i, col, 'M');
					P2AttackBoard.update(row - i, col, 'M');
				}
				if (i == 1)
				{
					if (col + 1 < 10)
					{
						if (P1Board1.checkCoordinates(row - i, col + 1) == 'S')
						{
							P1Board1.update(row - i, col + 1, 'H');
							P2AttackBoard.update(row - i, col + 1, 'H');
							if (P1Board1.isSunk(row - i, col + 1))
							{
								P1Board1.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P1Board1.getShipsLeft() == 0)
							{
								player2Won = true;
							}
						}
						else
						{
							P1Board1.update(row - i, col + 1, 'M');
							P2AttackBoard.update(row - i, col + 1, 'M');
						}
					}
					if (col - 1 >= 0)
					{
						if (P1Board1.checkCoordinates(row - i, col - 1) == 'S')
						{
							P1Board1.update(row - i, col - 1, 'H');
							P2AttackBoard.update(row - i, col - 1, 'H');
							if (P1Board1.isSunk(row - i, col - 1))
							{
								P1Board1.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P1Board1.getShipsLeft() == 0)
							{
								player2Won = true;
							}
						}
						else
						{
							P1Board1.update(row - i, col - 1, 'M');
							P2AttackBoard.update(row - i, col - 1, 'M');
						}
					}
				}
				else if (i == 2)
				{
					if (col + 1 < 10)
					{
						if (P1Board1.checkCoordinates(row - i, col + 1) == 'S')
						{
							P1Board1.update(row - i, col + 1, 'H');
							P2AttackBoard.update(row - i, col + 1, 'H');
							if (P1Board1.isSunk(row - i, col + 1))
							{
								P1Board1.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P1Board1.getShipsLeft() == 0)
							{
								player2Won = true;
							}
						}
						else
						{
							P1Board1.update(row - i, col + 1, 'M');
							P2AttackBoard.update(row - i, col + 1, 'M');
						}
					}
					if (col - 1 >= 0)
					{
						if (P1Board1.checkCoordinates(row - i, col - 1) == 'S')
						{
							P1Board1.update(row - i, col - 1, 'H');
							P2AttackBoard.update(row - i, col - 1, 'H');
							if (P1Board1.isSunk(row - i, col - 1))
							{
								P1Board1.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P1Board1.getShipsLeft() == 0)
							{
								player2Won = true;
							}
						}
						else
						{
							P1Board1.update(row - i, col - 1, 'M');
							P2AttackBoard.update(row - i, col - 1, 'M');
						}
					}
					if (col + 2 < 10)
					{
						if (P1Board1.checkCoordinates(row - i, col + 2) == 'S')
						{
							P1Board1.update(row - i, col + 2, 'H');
							P2AttackBoard.update(row - i, col + 2, 'H');
							if (P1Board1.isSunk(row - i, col + 2))
							{
								P1Board1.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P1Board1.getShipsLeft() == 0)
							{
								player2Won = true;
							}
						}
						else
						{
							P1Board1.update(row - i, col + 2, 'M');
							P2AttackBoard.update(row - i, col + 2, 'M');
						}
					}
					if (col - 2 >= 0)
					{
						if (P1Board1.checkCoordinates(row - i, col - 2) == 'S')
						{
							P1Board1.update(row - i, col - 2, 'H');
							P2AttackBoard.update(row - i, col - 2, 'H');
							if (P1Board1.isSunk(row - i, col - 2))
							{
								P1Board1.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P1Board1.getShipsLeft() == 0)
							{
								player2Won = true;
							}
						}
						else
						{
							P1Board1.update(row - i, col - 2, 'M');
							P2AttackBoard.update(row - i, col - 2, 'M');
						}
					}
				}
			}
		}
		break;
	case 2:
		for (int i = 0; i < 3; i++)
		{
			if (col + i < 10)
			{
				if (P1Board1.checkCoordinates(row, col + i) == 'S')
				{
					P1Board1.update(row, col + i, 'H');
					P2AttackBoard.update(row, col + i, 'H');
					if (P1Board1.isSunk(row, col + i))
					{
						P1Board1.sinkShip();
						cout << "You have sunk a ship!\n";
					}

					if (P1Board1.getShipsLeft() == 0)
					{
						player2Won = true;
					}
				}
				else
				{
					P1Board1.update(row, col + i, 'M');
					P2AttackBoard.update(row, col + i, 'M');
				}
				if (i == 1)
				{
					if (row + 1 < 10)
					{
						if (P1Board1.checkCoordinates(row + 1, col + i) == 'S')
						{
							P1Board1.update(row + 1, col + i, 'H');
							P2AttackBoard.update(row + 1, col + i, 'H');
							if (P1Board1.isSunk(row + 1, col + i))
							{
								P1Board1.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P1Board1.getShipsLeft() == 0)
							{
								player2Won = true;
							}
						}
						else
						{
							P1Board1.update(row + 1, col + i, 'M');
							P2AttackBoard.update(row + 1, col + i, 'M');
						}
					}
					if (row - 1 >= 0)
					{
						if (P1Board1.checkCoordinates(row - 1, col + i) == 'S')
						{
							P1Board1.update(row - 1, col + i, 'H');
							P2AttackBoard.update(row - 1, col + i, 'H');
							if (P1Board1.isSunk(row - 1, col + i))
							{
								P1Board1.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P1Board1.getShipsLeft() == 0)
							{
								player2Won = true;
							}
						}
						else
						{
							P1Board1.update(row - 1, col + i, 'M');
							P2AttackBoard.update(row - 1, col + i, 'M');
						}
					}
				}
				else if (i == 2)
				{
					if (row + 1 < 10)
					{
						if (P1Board1.checkCoordinates(row + 1, col + i) == 'S')
						{
							P1Board1.update(row + 1, col + i, 'H');
							P2AttackBoard.update(row + 1, col + i, 'H');
							if (P1Board1.isSunk(row + 1, col + i))
							{
								P1Board1.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P1Board1.getShipsLeft() == 0)
							{
								player2Won = true;
							}
						}
						else
						{
							P1Board1.update(row + 1, col + i, 'M');
							P2AttackBoard.update(row + 1, col + i, 'M');
						}
					}
					if (row - 1 >= 0)
					{
						if (P1Board1.checkCoordinates(row - 1, col + i) == 'S')
						{
							P1Board1.update(row - 1, col + i, 'H');
							P2AttackBoard.update(row - 1, col + i, 'H');
							if (P1Board1.isSunk(row - 1, col + i))
							{
								P1Board1.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P1Board1.getShipsLeft() == 0)
							{
								player2Won = true;
							}
						}
						else
						{
							P1Board1.update(row - 1, col + i, 'M');
							P2AttackBoard.update(row - 1, col + i, 'M');
						}
					}
					if (row + 2 < 10)
					{
						if (P1Board1.checkCoordinates(row + 2, col + i) == 'S')
						{
							P1Board1.update(row + 2, col + i, 'H');
							P2AttackBoard.update(row + 2, col + i, 'H');
							if (P1Board1.isSunk(row + 3, col + i))
							{
								P1Board1.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P1Board1.getShipsLeft() == 0)
							{
								player2Won = true;
							}
						}
						else
						{
							P1Board1.update(row + 2, col + i, 'M');
							P2AttackBoard.update(row + 2, col + i, 'M');
						}
					}
					if (row - 2 >= 0)
					{
						if (P1Board1.checkCoordinates(row - 2, col + i) == 'S')
						{
							P1Board1.update(row - 2, col + i, 'H');
							P2AttackBoard.update(row - 2, col + i, 'H');
							if (P1Board1.isSunk(row - 2, col + i))
							{
								P1Board1.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P1Board1.getShipsLeft() == 0)
							{
								player2Won = true;
							}
						}
						else
						{
							P1Board1.update(row - 2, col + i, 'M');
							P2AttackBoard.update(row - 2, col + i, 'M');
						}
					}
				}
			}
		}
		break;
	case 3:
		for (int i = 0; i < 3; i++)
		{
			if (row + i <= 10)
			{
				if (P1Board1.checkCoordinates(row + i, col) == 'S')
				{
					P1Board1.update(row + i, col, 'H');
					P2AttackBoard.update(row + i, col, 'H');
					if (P1Board1.isSunk(row + i, col))
					{
						P1Board1.sinkShip();
						cout << "You have sunk a ship!\n";
					}

					if (P1Board1.getShipsLeft() == 0)
					{
						player1Won = true;
					}
				}
				else
				{
					P1Board1.update(row + i, col, 'M');
					P2AttackBoard.update(row + i, col, 'M');
				}
				if (i == 1)
				{
					if (col + 1 < 10)
					{
						if (P1Board1.checkCoordinates(row + i, col + 1) == 'S')
						{
							P1Board1.update(row + i, col + 1, 'H');
							P2AttackBoard.update(row + i, col + 1, 'H');
							if (P1Board1.isSunk(row + i, col + 1))
							{
								P1Board1.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P1Board1.getShipsLeft() == 0)
							{
								player2Won = true;
							}
						}
						else
						{
							P1Board1.update(row + i, col + 1, 'M');
							P2AttackBoard.update(row + i, col + 1, 'M');
						}
					}
					if (col - 1 >= 0)
					{
						if (P1Board1.checkCoordinates(row + i, col - 1) == 'S')
						{
							P1Board1.update(row + i, col - 1, 'H');
							P2AttackBoard.update(row + i, col - 1, 'H');
							if (P1Board1.isSunk(row + i, col - 1))
							{
								P1Board1.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P1Board1.getShipsLeft() == 0)
							{
								player2Won = true;
							}
						}
						else
						{
							P1Board1.update(row + i, col - 1, 'M');
							P2AttackBoard.update(row + i, col - 1, 'M');
						}
					}
				}
				else if (i == 2)
				{
					if (col + 1 < 10)
					{
						if (P1Board1.checkCoordinates(row + i, col + 1) == 'S')
						{
							P1Board1.update(row + i, col + 1, 'H');
							P2AttackBoard.update(row + i, col + 1, 'H');
							if (P1Board1.isSunk(row + i, col + 1))
							{
								P1Board1.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P1Board1.getShipsLeft() == 0)
							{
								player2Won = true;
							}
						}
						else
						{
							P1Board1.update(row + i, col + 1, 'M');
							P2AttackBoard.update(row + i, col + 1, 'M');
						}
					}
					if (col - 1 >= 0)
					{
						if (P1Board1.checkCoordinates(row + i, col - 1) == 'S')
						{
							P1Board1.update(row + i, col - 1, 'H');
							P2AttackBoard.update(row + i, col - 1, 'H');
							if (P1Board1.isSunk(row + i, col - 1))
							{
								P1Board1.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P1Board1.getShipsLeft() == 0)
							{
								player2Won = true;
							}
						}
						else
						{
							P1Board1.update(row + i, col - 1, 'M');
							P2AttackBoard.update(row + i, col - 1, 'M');
						}
					}
					if (col + 2 < 10)
					{
						if (P1Board1.checkCoordinates(row + i, col + 2) == 'S')
						{
							P1Board1.update(row + i, col + 2, 'H');
							P2AttackBoard.update(row + i, col + 2, 'H');
							if (P1Board1.isSunk(row + i, col + 2))
							{
								P1Board1.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P1Board1.getShipsLeft() == 0)
							{
								player2Won = true;
							}
						}
						else
						{
							P1Board1.update(row + i, col + 2, 'M');
							P2AttackBoard.update(row + i, col + 2, 'M');
						}
					}
					if (col - 2 >= 0)
					{
						if (P1Board1.checkCoordinates(row + i, col - 2) == 'S')
						{
							P1Board1.update(row - i, col + 2, 'H');
							P2AttackBoard.update(row + i, col - 2, 'H');
							if (P1Board1.isSunk(row + i, col - 2))
							{
								P1Board1.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P1Board1.getShipsLeft() == 0)
							{
								player2Won = true;
							}
						}
						else
						{
							P1Board1.update(row + i, col - 2, 'M');
							P2AttackBoard.update(row + i, col - 2, 'M');
						}
					}
				}
			}
		}
		break;
	case 4:
		for (int i = 0; i < 3; i++)
		{
			if (col - i > 0)
			{
				if (P1Board1.checkCoordinates(row, col - i) == 'S')
				{
					P1Board1.update(row, col - i, 'H');
					P2AttackBoard.update(row, col - i, 'H');
					if (P1Board1.isSunk(row, col - i))
					{
						P1Board1.sinkShip();
						cout << "You have sunk a ship!\n";
					}

					if (P1Board1.getShipsLeft() == 0)
					{
						player2Won = true;
					}
				}
				else
				{
					P1Board1.update(row, col - i, 'M');
					P2AttackBoard.update(row, col - i, 'M');
				}
				if (i == 1)
				{
					if (row + 1 < 10)
					{
						if (P1Board1.checkCoordinates(row + 1, col - i) == 'S')
						{
							P1Board1.update(row + 1, col - i, 'H');
							P2AttackBoard.update(row + 1, col - i, 'H');
							if (P1Board1.isSunk(row + 1, col - i))
							{
								P1Board1.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P1Board1.getShipsLeft() == 0)
							{
								player2Won = true;
							}
						}
						else
						{
							P1Board1.update(row + 1, col - i, 'M');
							P2AttackBoard.update(row + 1, col - i, 'M');
						}
					}
					if (row - 1 >= 0)
					{
						if (P1Board1.checkCoordinates(row - 1, col - i) == 'S')
						{
							P1Board1.update(row - 1, col - i, 'H');
							P2AttackBoard.update(row - 1, col - i, 'H');
							if (P1Board1.isSunk(row - 1, col - i))
							{
								P1Board1.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P1Board1.getShipsLeft() == 0)
							{
								player2Won = true;
							}
						}
						else
						{
							P1Board1.update(row - 1, col - i, 'M');
							P2AttackBoard.update(row - 1, col - i, 'M');
						}
					}
				}
				else if (i == 2)
				{
					if (row + 1 < 10)
					{
						if (P1Board1.checkCoordinates(row + 1, col - i) == 'S')
						{
							P1Board1.update(row + 1, col - i, 'H');
							P2AttackBoard.update(row + 1, col - i, 'H');
							if (P1Board1.isSunk(row + 1, col - i))
							{
								P1Board1.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P1Board1.getShipsLeft() == 0)
							{
								player2Won = true;
							}
						}
						else
						{
							P1Board1.update(row + 1, col - i, 'M');
							P2AttackBoard.update(row + 1, col - i, 'M');
						}
					}
					if (row - 1 >= 0)
					{
						if (P1Board1.checkCoordinates(row - 1, col - i) == 'S')
						{
							P1Board1.update(row - 1, col - i, 'H');
							P2AttackBoard.update(row - 1, col - i, 'H');
							if (P1Board1.isSunk(row - 1, col - i))
							{
								P1Board1.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P1Board1.getShipsLeft() == 0)
							{
								player2Won = true;
							}
						}
						else
						{
							P1Board1.update(row - 1, col - i, 'M');
							P2AttackBoard.update(row - 1, col - i, 'M');
						}
					}
					if (row + 2 < 10)
					{
						if (P1Board1.checkCoordinates(row + 2, col - i) == 'S')
						{
							P1Board1.update(row + 2, col - i, 'H');
							P2AttackBoard.update(row + 2, col - i, 'H');
							if (P1Board1.isSunk(row + 2, col - i))
							{
								P1Board1.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P1Board1.getShipsLeft() == 0)
							{
								player2Won = true;
							}
						}
						else
						{
							P1Board1.update(row + 2, col - i, 'M');
							P2AttackBoard.update(row + 2, col - i, 'M');
						}
					}
					if (row - 2 >= 0)
					{
						if (P1Board1.checkCoordinates(row - 2, col - i) == 'S')
						{
							P1Board1.update(row - 2, col - i, 'H');
							P2AttackBoard.update(row - 2, col - i, 'H');
							if (P1Board1.isSunk(row - 2, col - i))
							{
								P1Board1.sinkShip();
								cout << "You have sunk a ship!\n";
							}

							if (P1Board1.getShipsLeft() == 0)
							{
								player2Won = true;
							}
						}
						else
						{
							P1Board1.update(row - 2, col - i, 'M');
							P2AttackBoard.update(row - 2, col - i, 'M');
						}
					}
				}
			}
		}
		break;
	}
	}
}

void Executive::ringOfFireV(int row, int col, int player)
{
	if (player == 1)
	{
		for (int i = 0; i < 5; i++)
		{
			if (P2Board2.checkCoordinates(row + i, col) == 'S')
			{
				P2Board2.update(row + i, col, 'H');
				P1AttackBoard.update(row + i, col, 'H');
				if (P2Board2.isSunk(row + i, col))
				{
					P2Board2.sinkShip();
					cout << "You have sunk a ship!\n";
				}

				if (P2Board2.getShipsLeft() == 0)
				{
					player1Won = true;
				}
			}
			else
			{
				P2Board2.update(row + i, col, 'M');
				P1AttackBoard.update(row + i, col, 'M');
			}
		}
		col = col + 1;
		for (int i = 0; i < 5; i++)
		{
			if (P2Board2.checkCoordinates(row + i, col) == 'S')
			{
				P2Board2.update(row + i, col, 'H');
				P1AttackBoard.update(row + i, col, 'H');
				if (P2Board2.isSunk(row + i, col))
				{
					P2Board2.sinkShip();
					cout << "You have sunk a ship!\n";
				}

				if (P2Board2.getShipsLeft() == 0)
				{
					player1Won = true;
				}
			}
			else
			{
				P2Board2.update(row + i, col, 'M');
				P1AttackBoard.update(row + i, col, 'M');
			}
		}
	}
	else
	{
		for (int i = row; i < 5; i++)
		{
			if (P1Board1.checkCoordinates(row + i, col) == 'S')
			{
				P1Board1.update(row + i, col, 'H');
				P2AttackBoard.update(row + i, col, 'H');
				if (P1Board1.isSunk(row + i, col))
				{
					P1Board1.sinkShip();
					cout << "You have sunk a ship!\n";
				}

				if (P1Board1.getShipsLeft() == 0)
				{
					player2Won = true;
				}
			}
			else
			{
				P1Board1.update(row + i, col, 'M');
				P2AttackBoard.update(row + i, col, 'M');
			}
		}
		col = col + 1;
		for (int i = row; i < 5; i++)
		{
			if (P1Board1.checkCoordinates(row + i, col) == 'S')
			{
				P1Board1.update(row + i, col, 'H');
				P2AttackBoard.update(row + i, col, 'H');
				if (P1Board1.isSunk(row + i, col))
				{
					P1Board1.sinkShip();
					cout << "You have sunk a ship!\n";
				}

				if (P1Board1.getShipsLeft() == 0)
				{
					player2Won = true;
				}
			}
			else
			{
				P1Board1.update(row + i, col, 'M');
				P2AttackBoard.update(row + i, col, 'M');
			}
		}
	}
}

void Executive::ringOfFireH(int row, int col, int player)
{
	if (player == 1)
	{
		for (int i = 0; i < 5; i++)
		{
			if (P2Board2.checkCoordinates(row, i) == 'S')
			{
				P2Board2.update(row, col + i, 'H');
				P1AttackBoard.update(row, col + i, 'H');
				if (P2Board2.isSunk(row, col + i))
				{
					P2Board2.sinkShip();
					cout << "You have sunk a ship!\n";
				}

				if (P2Board2.getShipsLeft() == 0)
				{
					player1Won = true;
				}
			}
			else
			{
				P2Board2.update(row, col + i, 'M');
				P1AttackBoard.update(row, col + i, 'M');
			}
		}
		row = row + 1;
		for(int i = 0; i < 5; i++)
		{
			if (P2Board2.checkCoordinates(row, i) == 'S')
			{
				P2Board2.update(row, col + i, 'H');
				P1AttackBoard.update(row, col + i, 'H');
				if (P2Board2.isSunk(row, col + i))
				{
					P2Board2.sinkShip();
					cout << "You have sunk a ship!\n";
				}

				if (P2Board2.getShipsLeft() == 0)
				{
					player1Won = true;
				}
			}
			else
			{
				P2Board2.update(row, col + i, 'M');
				P1AttackBoard.update(row, col + i, 'M');
			}
		}
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			if (P1Board1.checkCoordinates(row, i) == 'S')
			{
				P1Board1.update(row, col + i, 'H');
				P2AttackBoard.update(row, col + i, 'H');
				if (P1Board1.isSunk(row, col + i))
				{
					P1Board1.sinkShip();
					cout << "You have sunk a ship!\n";
				}

				if (P1Board1.getShipsLeft() == 0)
				{
					player2Won = true;
				}
			}
			else
			{
				P1Board1.update(row, col + i, 'M');
				P2AttackBoard.update(row, col + i, 'M');
			}
		}
		row = row + 1;
		for (int i = 0; i < 5; i++)
		{
			if (P1Board1.checkCoordinates(row, col + i) == 'S')
			{
				P1Board1.update(row, col + i, 'H');
				P2AttackBoard.update(row, col + i, 'H');
				if (P1Board1.isSunk(row, col + i))
				{
					P1Board1.sinkShip();
					cout << "You have sunk a ship!\n";
				}

				if (P1Board1.getShipsLeft() == 0)
				{
					player2Won = true;
				}
			}
			else
			{
				P1Board1.update(row, col + i, 'M');
				P2AttackBoard.update(row, col + i, 'M');
			}
		}
	}
}
