#include "Player.h"
#include "Board.h"
#include <math.h>
#include <iostream>

using namespace std;

Player::Player(int p, bool ai)
{
	//Sets player color and tells if it is an AI player
	player = p;
	AI = ai;
	AIx = 0;
	AIlevel = 0;
}
//set the ai of the player
void Player::setAI(bool ply)
{
	AI = ply;
}
//see if player is AI
bool Player::getAI()
{
	return AI;
}
//get player color
int Player::getPlayer()
{
	//returns player color
	return player;
}
int Player::getAIx()
{
	return AIx;
}
void Player::setAIlevel(int ai)
{
	AIlevel = ai;
}
//User move function
void Player::move(int board[8][8], int x, int player)
{
	//Places player piece at row x

	for (int y = 0; y < 8; y++)
	{
		//find the last open spot
		if (board[x][y] == -1 && board[x][y + 1] == 1 || board[x][y + 1] == 0 || y == 7)
		{
			board[x][y] = player;
			//after placing chip break from for loop
			break;
		}
	}
}
int Player::AIcheckMove(int board[8][8], int x)
{
	//Go through rows and sees where the last empty spot is
	if (AIlevel == 0 && (board[x][0] == 1 || board[x][0] == 0))
	{
		return -100;
	}
	for (int y = 0; y < 8; y++)
	{
		if (board[x][y] == -1 && board[x][y + 1] == 1 || board[x][y + 1] == 0)
		{
			//return empty spot
			return y;
		}
	}
	//if the column is empty
	return 7;
}

int Player::AIeval(int board[8][8], int x, int y, int player)
{
	//variables for x and y values dependent on left or right checking
	int x2 = x;
	int y2 = y;
	bool openRight = false;
	bool openLeft = false;
	int vertStreak = 1;//1 for chip that will/might be placed here
	int horzStreak = 1;//1 for chip that will/might be placed here
	int rdStreak = 1;//1 for chip that will/might be placed here
	int ldStreak = 1;
	int right = 0;
	int left = 0;

	//CASE: VERT
	//look for a chip
	if (board[x][0] != 1 || board[x][0] != 0)
	{
		y2 = y + 1;//start looking 1 chip down

		while (y2 > -1 && board[x2][y2] == player)//while still in the row and still looking at player chips
		{
			vertStreak++;//add every consecutive chip
			y2++;//go further down y
		}
	}
	else
	{
		vertStreak = -100;//if it is empty return -100 to discourage random vertical building
	}
	if (AIlevel == 2)
	{
		if ((vertStreak == 1 && y < 3) || (vertStreak == 2 && y < 2) || (vertStreak == 3 && y < 1))//if impossble to win
		{
			vertStreak = -100;//junk
		}
	}


	//CASE HORZ
	y2 = y;//does not change
		   //right
	x2 = x + 1;//start looking from the chip to the right
	while (x2 < 8 && board[x2][y2] == player)//while in bounds & same chip
	{
		right++;
		x2++;//keep moving right
	}
	if (board[x2][y2] != -1)
	{
		openRight = false;
	}
	else
	{
		openRight = true;
	}
	//left
	x2 = x - 1;//start looking from the chip to the left
	while (x2 > -1 && board[x2][y2] == player)//while in bounds & same chip
	{
		left++;
		x2--;//keep moving left
	}
	if (board[x2][y2] != -1)
	{
		openLeft = false;
	}
	else
	{
		openLeft = true;
	}
	horzStreak += right + left;//add both values and create the total streak
	if (AIlevel == 2)
	{
		if (!openLeft && !openRight)
		{
			horzStreak = -100;//junk
		}
	}
	//CASE: LEFT DIAGONAL

	right = 0;
	left = 0;
	//right
	x2 = x + 1;//right
	y2 = y - 1;//up
	while (x2 < 8 && y2>-1 && board[x2][y2] == player)//while in bounds & same chip
	{
		right++;
		x2++;//right more
		y2--;//up more
	}
	if (board[x2][y2] != -1)
	{
		openRight = false;
	}
	else
	{
		openRight = true;
	}
	//left
	x2 = x - 1;//left
	y2 = y + 1;//down
	while (x2>-1 && y2<8 && board[x2][y2] == player)//while in bounds & same chip
	{
		left++;
		x2--;//left more
		y2++;//down more
	}
	if (board[x2][y2] != -1)
	{
		openLeft = false;
	}
	else
	{
		openLeft = true;
	}
	ldStreak += right + left;
	if (AIlevel == 2)
	{
		if (!openLeft && !openRight)
		{
			ldStreak = -100;
		}
	}
	//CASE: RIGHT DIAGONAL
	right = 0;
	left = 0;
	//right
	x2 = x - 1;//left more
	y2 = y - 1;//up more
	while (x2 > -1 && y2 > -1 && board[x2][y2] == player)
	{
		right++;
		x2--;//left more
		y2--;//up more
	}
	if (board[x2][y2] != -1)
	{
		openRight = false;
	}
	else
	{
		openRight = true;
	}
	//left
	x2 = x + 1;//right
	y2 = y + 1;//down
	while (x2 < 8 && y2 < 8 && board[x2][y2] == player)
	{
		left++;
		x2++;//right more
		y2++;//left more
	}
	if (board[x2][y2] != -1)
	{
		openRight = false;
	}
	else
	{
		openRight = true;
	}
	rdStreak += right + left;//build streak
	if (AIlevel == 2)
	{
		if (!openLeft && !openRight)
		{
			ldStreak = -100;
		}
	}

	//find max streak and return it
	int highStreak = 0;
	if (vertStreak > highStreak) { highStreak = vertStreak; }
	if (horzStreak > highStreak) { highStreak = horzStreak; }
	if (ldStreak > highStreak) { highStreak = ldStreak; }
	if (rdStreak > highStreak) { highStreak = rdStreak; }
	if (AIlevel == 1 && highStreak == 4)
	{
		int mistake = rand() % 4;
		if (mistake == 1 && vertStreak != -100)
		{
			highStreak = 0;
		}
	}
	return highStreak;//return the best place to move
}
void Player::AImove(int board[8][8], int player)//move an AI player
{

	//possible moves
	int y[8];
	//initialize possible moves
	for (int i = 0; i < 8; i++)
	{
		y[i] = AIcheckMove(board, i);
	}
	//player and opponent move values
	int play[8];
	int opp[8];
	for (int i = 0; i < 8; i++)
	{
		//Set player to AIeval with the player's value and set the opponent to the other value
		if (player == 1)
		{
			play[i] = AIeval(board, i, y[i], 1);
			opp[i] = AIeval(board, i, y[i], 0);
		}
		else
		{
			play[i] = AIeval(board, i, y[i], 0);
			opp[i] = AIeval(board, i, y[i], 1);
		}
	}

	int high = 0;//streak of best play
	int bestx = 0;//best play
	for (int i = 0; i < 8; i++)
	{
		if (play[i] >= opp[i] && play[i] > high)//if the player move is better than the current best move
		{
			bestx = i;//set best move
			high = play[i];//set high streak
		}
		else if (opp[i] > play[i] && opp[i] > high)//if the opponent move is better than the current best move
		{
			bestx = i;//set best move
			high = opp[i];//set high streak
		}
	}
	AIx = bestx;
	if (AIlevel == 0)
	{
		int num = rand() % 8;
		while (AIcheckMove(board, num) == -100)
		{
			num = rand() % 8;
		}
		board[num][AIcheckMove(board, num)] = player;
	}
	else
	{
		board[bestx][y[bestx]] = player;//move to best spot
	}
}