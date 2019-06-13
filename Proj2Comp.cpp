/*****************************************************************************/
/*                                                                           */
/* File: Proj2Comp.cpp                                                       */
/* Project: Project 2 - Reversi/Othello - CS 215 Fall 2018                   */
/* Author: Dr. Watts                                                         */
/* Date: September 24, 2018                                                  */ 
/* Description: This is the driver file for a Computer vs Computer game of   */
/* Reversi/Othello. It will instantiate and use objects of three different   */
/* "Game" classes. In addition to Game, it will used Game1 and Game2.        */
/*                                                                           */
/*****************************************************************************/

#include <iostream>
#include <cstdlib>
#include "Game.h"
#include "Game1.h"
#include "Game2.h"

using namespace std;

/*****************************************************************************/
/*                                                                           */
/* Function:                                                                 */ 
/* Input parameters:                                                         */ 
/* Return value:                                                             */ 
/* Description:                                                              */
/*                                                                           */
/*****************************************************************************/

int main (int argc, char * argv[])
{
	int rounds = 1;
	if (argc == 2)
		rounds = atoi (argv[1]);
	Game game;
	Game1 game1;
	Game2 game2;
	string playerNames [] = {"NONE", "HUMAN", "COMPUTER"};
	int scores [] = {0, 0, 0};
	srand (time(NULL));
	playerType player = rand() % 2 ? HUMAN : COMPUTER;
	for (int i = 0; i < rounds; i++)
	{
		game.Init();
		game1.Init();
		game2.Init();
		game.Display (cout);
		cout << "Player " << playerNames[player] << " is starting the game\n";
		while (!game.Done())
		{
			int row, col;
			if (player == HUMAN)
				game1.ChooseMove(player, row, col);
			else
				game2.ChooseMove(player, row, col);
			game.MakeMove(player, row, col);
			game1.MakeMove(player, row, col);
			game2.MakeMove(player, row, col);
			game.Display (cout);
			player = player == HUMAN ? COMPUTER : HUMAN;
		}
		cout << "GameOver! ";
		int winner = game.Winner(cout);
		scores[winner]++;
	}
	cout << "Player 1 (aka HUMAN) won " << scores[1] << " games\n";
	cout << "Player 2 (aka COMPUTER) won " << scores[2] << " games\n";
	cout << scores[0] << " games ended in a tie\n";
	return 0;
}
