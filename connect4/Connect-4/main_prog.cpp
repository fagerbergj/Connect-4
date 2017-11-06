#include "Player.h"
#include "Board.h"
#include <iostream>
#include <Windows.h>

using namespace std;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);//for color

//Print board with colors
void print(int board[8][8])	//Print board with colors
{
	SetConsoleTextAttribute(h, 8);
	cout << "  0     1     2     3     4     5     6     7 \n";//row indicator
	SetConsoleTextAttribute(h, 121);//set blue text with gray background for board
	for (int y = 0; y < 8; y++)//go through all spots
	{
		for (int x = 0; x < 8; x++)//not sure why x and y need to be reversed...just need to be
		{
			if (board[x][y] == -1)//if empty
			{
				SetConsoleTextAttribute(h, 121);
				cout << "_____" << "|";//print empty spot
			}
			else//if full
			{
				if (board[x][y] == 1)//if yellow
				{
					SetConsoleTextAttribute(h, 224);//black text yellow background
					cout << "__Y__";
				}
				else//if red
				{
					SetConsoleTextAttribute(h, 192);//black text red background
					cout << "__R__";
				}
				SetConsoleTextAttribute(h, 121);//set color back to divider default
				cout << "|";//end space
			}
		}
		SetConsoleTextAttribute(h, 8);
		cout << endl;//new column
	}
}
//Build and execute everything
int main()
{
	SetConsoleTextAttribute(h, 8);//gray text
	int players; //Player turn tracker
	int ai;//ai level
	Board game;  //Initialize Board
	Player red(0, false); //Initialize Red Player
	Player yellow(1, false); //Initialize Yellow Player

	cout << "How many Players?\n";
	cin >> players;//set 1 or 2 player mode

				   //set AI or 2 player
	if (players == 1) //if 1 player
	{
		cout << "What Level AI?  (0 = easy, 1 = normal, 2 = hard)\n";
		cin >> ai;
		while (ai != 0 && ai != 1 && ai != 2)
		{
			cout << "\n Please Enter A valid AI level.     (0 = easy, 1 = normal, 2 = hard)";
			cin >> ai;
		}
		yellow.setAI(true); //yellow is AI
		yellow.setAIlevel(ai);
	}
	else if (players == 2)
	{
		yellow.setAI(false);//yellow is not AI
	}
	else//Improper Input
	{
		cout << "\n No reasonable number was entered, starting 1 player game \n";
		yellow.setAI(true); //You dont have a choice anymore
		cout << "What Level AI?  (0 = easy, 1 = normal, 2 = hard)\n";
		cin >> ai;
		while (ai != 0 && ai != 1 && ai != 2)
		{
			cout << "\n Please Enter A valid AI level.     (0 = easy, 1 = normal, 2 = hard)";
			cin >> ai;
		}
	}

	print(game.board);//print empty board
					  //64 possible moves
	for (int i = 0; i < 32; i++)
	{
		//coordinates
		int x;
		int y;
		//red is always user
		SetConsoleTextAttribute(h, 8);
		cout << "Please Enter Move\n";
		cin >> x;
		if (game.board[x][0] == 1 || game.board[x][0] == 0)//if top spot is full
		{
			y = -99;//junk value
		}
		else//if there is an open space
		{
			y = red.AIcheckMove(game.board, x);//y = possible valid move
		}
		while (y == -99)//check real number
		{
			cout<<"Please enter a row with an avaliable space\n";
			cin >> x;
			if (game.board[x][0] == 1 || game.board[x][0] == 0)//if top spot is full
			{
				y = -99;//junk value
			}
			else//if there is an open space
			{
				y = red.AIcheckMove(game.board, x);//y = valid move
			}
		}
		while (x > 7)//while not in bounds in terms of x
		{
			cout << "Please enter an acceptable x value \n";//keep going until an acceptable value is input
			cin >> x;
			y = red.AIcheckMove(game.board, x);
		}
		//if real option---> do it
		red.move(game.board, x, 0);
		print(game.board);
		SetConsoleTextAttribute(h, 8);//reset text
		if (game.checkWin(game.board, x, y, 0))//check if game is over
		{
			cout << "\n\n\n\n\nRED WINS\n\n\n\n\n";
			system("pause");//let the user see why the game is over before ending program
			return 0;
		}

		//if AI
		if (yellow.getAI())
		{
			SetConsoleTextAttribute(h, 8);
			cout << "\nAI moving.......\n";
			yellow.AImove(game.board, 1);//AI moves
			print(game.board);
			//need these for accurate checkWin 
			x = yellow.getAIx();
			y = yellow.AIcheckMove(game.board, x) + 1;
		}
		else//if user
		{
			SetConsoleTextAttribute(h, 8);
			cout << "Please Enter Move\n";
			cin >> x;
			if (game.board[x][0] == 1 || game.board[x][0] == 0)//if top spot is full
			{
				y = -99;//junk value
			}
			else//if there is an open space
			{
				y = yellow.AIcheckMove(game.board, x);//y = possible valid move
			}
			while (y == -99)//check real number
			{
				cout << "Please enter a row with an avaliable space\n";
				cin >> x;
				if (game.board[x][0] == 1 || game.board[x][0] == 0)//if top spot is full
				{
					y = -99;//junk value
				}
				else//if there is an open space
				{
					y = yellow.AIcheckMove(game.board, x);//y = valid move
				}
			}
			while (x > 7)//while not in bounds in terms of x
			{
				cout << "Please enter an acceptable x value \n";//keep going until an acceptable value is input
				cin >> x;
				y = yellow.AIcheckMove(game.board, x);
			}
			yellow.move(game.board, x, 1);//player 2 move
			print(game.board);
		}
		SetConsoleTextAttribute(h, 8);
		if (game.checkWin(game.board, x, y, 1))//see if yellow won
		{
			cout << "\n\n\n\n\nYELLOW WINS\n\n\n\n\n";
			system("pause");//let user see why yellow won
			return 0;
		}
	}
	//build everything
	return 0;
}