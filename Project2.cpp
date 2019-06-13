/*****************************************************************************/
/*                                                                           */
/* File: Project2.cpp                                                        */
/* Project: Project 2 - Reversi/Othello - CS 215 Fall 2018                   */
/* Author: Dr. Watts                                                         */
/* Date: September 24, 2018                                                  */ 
/* Description: This is the driver file for a Human vs Computer game of	     */
/* Reversi/Othello. It will instantiate and use an object of the Game class. */
/*                                                                           */
/*****************************************************************************/

#include <iostream>
#include "Game.h"

using namespace std;

int main ()
{
	Game game;
	game.Instructions (cout);
	game.Init();
	game.Display (cout);
	string playerNames [] = {"NONE", "HUMAN", "COMPUTER"};
	playerType player = HUMAN;
	while (!game.Done())
	{
		int row, col;
		bool moveAvailable = false;
		if (player == HUMAN) // Human Player
			moveAvailable = game.ChooseMove(player, row, col, cin, cout);
		else
		  moveAvailable = game.ChooseMove(player, row, col);
		if (moveAvailable)
		{
			game.MakeMove(player, row, col);
			game.Display(cout);
		}
		else
			cout << "No move available for " << playerNames[player] << " Player.\n";
		if (player == HUMAN)
			player = COMPUTER;
		else
			player = HUMAN;
	}
	cout << "GameOver! " << endl;
	int winner = game.Winner(cout);
	return 0;
}
