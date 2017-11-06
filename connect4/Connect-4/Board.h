#pragma once
#ifndef Board_H
#define Board_H
#include <iostream>
using namespace std;

class Board
{
public:
	Board();//Constructs empty board
	bool checkWin(int board[8][8], int x, int y, int player);//see if game is over
	int board[8][8];//basis of entire game
};
#endif