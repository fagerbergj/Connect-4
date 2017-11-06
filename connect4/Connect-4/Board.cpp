#include "Player.h"
#include "Board.h"
#include <iostream>

using namespace std;

Board::Board()
{
	//empties board
	//0=red,1=yellow,-1=empty
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			board[x][y] = -1;
		}
	}
}

bool Board::checkWin(int board[8][8], int x, int y, int player)
{
	//checks if the game is over by looking for common color pieces
	//around the last move
	//Returns true if there is a connection for 4 returns false otherwise

	// CASE: VERT
	if (board[x][y] == player && board[x][y + 1] == player && board[x][y + 2] == player && board[x][y + 3] == player)//if three spots under move are same color
	{
		cout << "\nCASE: VERTICAL\n";
		return true;
	}

	//CASE: HORZ
	int horzStreak = 0;//tried to do this based on y input, would not work for some reason
	for (int i = 0; i < 8; i++)
	{
		if (board[i][y] == player)
		{
			horzStreak++;
		}
		else
		{
			horzStreak = 0;
		}
		if (horzStreak >= 4)
		{
			cout << "\nCASE: HORZ\n";
			return true;
		}
	}


	//CASE: LEFT DIAGONAL
	int DLstreak = 0;
	for (int n = -3; n < 4; n++)//look +3 spaces left through +3 spaces right
	{
		if (x - n < 8 && x - n > -1 && y - n < 8 && y - n > -1)//while in bounds
		{
			if (board[x - n][y - n] == player)//if spot to incrementing values to the left and up is player
			{
				DLstreak++;
			}
			else//if not then end streak
			{
				DLstreak = 0;
			}
		}
		if (DLstreak >= 4)
		{
			cout << "\nCASE: LEFT DIAGIONAL\n";
			return true;
		}
	}

	//CASE: RIGHT DIAGONAL
	int DRstreak = 0;
	for (int n = -3; n < 4; n++)
	{
		if (8 > x + n && x + n > -1 && 8 > y - n && y - n > -1)//look +3 spaces left through +3 spaces right
		{
			if (board[x + n][y - n] == player)//if spot to incrementing values to the right and up is player
			{
				DRstreak++;
			}
			else//if not then end streak
			{
				DRstreak = 0;
			}
		}
		if (DRstreak >= 4)
		{
			cout << "\nCASE: RIGHT DIAGONAL\n";
			return true;
		}
	}
	return false;
}