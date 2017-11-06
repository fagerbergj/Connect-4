#pragma once
#ifndef Player_H
#define Player_H
#include <iostream>
using namespace std;

class Player // Player Class 
{
public:
	Player(int p, bool ai);//Constructor For class
	int getPlayer();//return player color value
	int getAIx();//for the main_prog to know where AI wants to move to
	void setAIlevel(int ai);//set difficulty
	void move(int board[8][8], int x, int player);//user move method
	void AImove(int board[8][8], int player);//AI move method
	int AIeval(int board[8][8], int x, int y, int player);//find the best move for the AI
	int AIcheckMove(int board[8][8], int x);//Find the lowest open space without executing it
	void setAI(bool ply);//set AI truth
	bool getAI();//get AI truth
private:
	bool AI;//User or computer
	int player;//Player value
	int AIx;//x value of where the AI wants to go
	int AIlevel;//AI Difficulty    0 = easy    1 = medium     2 = hard 
};
#endif
