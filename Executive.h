#include<iostream>
#include<string>
#include"Board.h"
#include <vector>

/** Program to implement the Board
  * @Version Team 10 update
  * @Dated 3/14/21
  **/

#ifndef EXECUTIVE_H
#define EXECUTIVE_H

struct Point
{
	int x, y, h, s, hx, hy, firstx, firsty;
};

class Executive
{
private:
	/**Row column temp variables**/
	int row1, row2, col1, col2;

	/**Sets up a Board for P1 to place ships**/
	Board P1Board1;

	/**Sets up a Board for P2 to place ships**/
	Board P2Board2;

	/**Sets up a board for P1 to place attacks on**/
	Board P1AttackBoard;

	/**Sets up a board for P2 to place attacks on**/
	Board P2AttackBoard;

	/**Player 1 win tracker**/
	bool player1Won = false;

	/**Player 2 win tracker**/
	bool player2Won = false;

	int m_shipNum;

public:

	/**
	* Executive Class constructor, Initialize variables and functions
	*
	* @param int - The number of ships
	* @return Nothing
	**/
	Executive(int num);

	/**
	* Print out a board that player 1 can place their ships in order of 1X1, 1X2, 1X3 and etc.
	*
	* @param Nothing
	* @return Nothing
	**/
	void P1Place();
	/**
	  * Print out a board that player 2 can place their ships in order of 1X1, 1X2, 1X3 and etc.
	  *
	  * @param Nothing
	  * @return Nothing
	  **/
	void P2Place();

	/**
	* Player 1 attacks Player 2 ships and updates Player 1 attack board to let player see if they hit or miss
	* @param int mode - game mode
	* @param int leader - Leader chosen by player
	* @param int turn - turn counter
	* @param bool& ability used - Ability use switch
	* @return Nothing
	**/
	void P1Attack(int mode, int leader, int turn, bool& abilityused);
	/**
	  * Player 2 attacks Player 1 ships and updates Player 2 attack board to let player see if they hit or miss
	  * @param int mode - game mode
	  * @param int leader2 - Leader chosen by player
	  * @param int turn - turn counter
	  * @param bool& ability used - Ability use switch
	  * @return Nothing
	  **/
	void P2Attack(int mode, int leader2, int turn2, bool& abilityused2);

	/**
	* Determine if Player 1 Won.
	* @param Nothing
	* @return Bool - True for win, false to continue
	**/
	bool P1Won();
	/**
	  *  Determine if Player 2 Won.
	  * @param Nothing
	  * @return Bool - True for win, false to continue
	  **/
	bool P2Won();

	/**
	* Takes in user input, it must a number or else user must enter new input.
	*
	* @param int - Beggining of valid input range
	* @param int - End valid input range
	* @return int - Returns valid user input
	**/
	int inputNumber(int begin, int end);
	/**
	  * Takes in user input, it must a letter that will be converted to a number
	  *
	  * @param char - Beggining of valid input range
	  * @param char - End valid input range
	  * @return int - Returns valid user input
	  **/
	int inputAlphabet(char begin, char end);
	/**
	  * Randomly populates the AI's board
	  * @param Nothing
	  * @return Nothing
	  **/
	void AIPlacement();
	/**
	  * Allows the AI to attack based on the difficulty.
	  *
	  * @parm int difficulty - Gives the difficulty
	  * @parm Point - The previous point the AI tried to hit.
	  * @param vector - A vector of a struct pair that stores two interger values
	  * @return Point - Returns the previous point the AI tried to hit.
	  **/
	Point AIAttack(int difficulty, Point, vector<vector<pair<int, int>>>, int&, int&);

	/**
	  * Gets the cheat coordinates for the hardest difficulty.
	  *
	  * @return Point - Returns the vector with the ship's coordinates.
	  **/
	vector<vector<pair<int, int>>> cheatGet();

	/**
	  * Prompts the user if they want to use their special shot
	  *
	  * @parm int leader - Gives the leader code that the user chose.
	  * @parm bool abilityused - The check if the user has used their ability yet.
	  * @parm int player - Gives the player calling the attacks.
	  * @return bool - Returns true if the user has used their ability.
	  **/
	bool AbilityPrompt(int leader, bool abilityused, int player);

	/**
	  * Hits the opponent board with a laser that hits a whole row.
	  *
	  * @parm int row - Gives the row the player would like to hit
	  * @parm int player - Gives the player that used the attack
	  * @return Nothing
	  **/
	void LaserH(int row, int player); //Horizontal Laser attack

	/**
	  * Hits the opponent board with a laser that hits a whole column.
	  *
	  * @parm int col - Gives the column the player would like to hit
	  * @parm int player - Gives the player that used the attack
	  * @return Nothing
	  **/
	void LaserV(int col, int player); //Vertical Laser attack

	/**
	  * Hits the opponent board with 10 random attacks.
	  *
	  * @parm int player - Gives the player that used the attack
	  * @return Nothing
	  **/
	void rainOfDeath(int player);

	/**
	  * Hits the opponent board with 10 hit cone attack.
	  *
	  * @parm int player - Gives the player that used the attack
	  * @return Nothing
	  **/
	void RailGun(int player);

	/**
	  * Hits the opponent board with 5x2 rectangle attack.
	  *
	  * @parm int row - Gives the row that the user wants the top right corner to be
	  * @parm int col - Gives the col that the user wants the top right corner to be
	  * @parm int player - Gives the player that used the attack
	  * @return Nothing
	  **/
	void ringOfFireH(int row, int col, int player);

	/**
	  * Hits the opponent board with 2x5 rectangle attack.
	  *
	  * @parm int row - Gives the row that the user wants the top right corner to be
	  * @parm int col - Gives the col that the user wants the top right corner to be
	  * @parm int player - Gives the player that used the attack
	  * @return Nothing
	  **/
	void ringOfFireV(int row, int col, int player);

	/**
	* Clears the screen to remove past console outputs
	* 
	* @param Nothing
	* @returns Nothing
	*/
	void clrscn1();
};
#endif
