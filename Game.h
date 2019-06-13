/*****************************************************************************/
/*                                                                           */
/* File: Game.h                                                              */
/* Project: Project 2 - Reversi/Othello - CS 215 Fall 2018                   */
/* Author: Aidan Roth                                                        */
/* Date: Fall 2018                                                           */ 
/* Description: This is the header file for the Game class. It also contains */
/*  global variables for the number of rows and columns and the implementation*/
/*  of the playerType enumerated type.                                        */
/*                                                                           */
/*****************************************************************************/
 
#pragma once
#include <iostream>

using namespace std;

/*****************************************************************************/
/*                                                                           */
/* Constants: Rows and Columns (standard board is 8x8)                       */ 
/* Description: Set the global variable for the number of rows and columns   */
/*                                                                           */
/*****************************************************************************/

const int ROWS = 4;
const int COLS = 4;

/*****************************************************************************/
/*                                                                           */
/* Type: playerType                                                          */ 
/* Description: This enumerated type defines the different players in the    */
/* game. NONE is used to identify a cell that has not been claimed and a     */
/* tied game.                                                                */
/*                                                                           */
/*****************************************************************************/

#ifndef PLAYER_TYPE
#define PLAYER_TYPE
enum playerType {NONE, HUMAN, COMPUTER};
#endif

/*****************************************************************************/
/*                                                                           */
/* Class: Game                                                               */ 
/* Description: Provides the functions and structures for pretty much the    */
/*    entire Othello game program                                            */
/*                                                                           */
/*****************************************************************************/

class Game
{
	private:
		struct Cell
		{
			Cell ();
			void Display (ostream & outs);
			playerType owner;
			int cellScore;
		};
		Cell board [ROWS+2][COLS+2];
		int score[3];
		bool ValidMove (playerType Who, int Row, int Col);
		bool CheckBoard (playerType Who);
	public:
		Game ();
		void Instructions (ostream & outs);
		void Init ();
		void Display (ostream & outs);
		void MakeMove (playerType Who, int Row, int Col);
		bool ChooseMove (playerType Who, int & Row, int & Col, istream & In, ostream & Out);
		bool ChooseMove (playerType Who, int & Row, int & Col);
		bool Done ();
		playerType Winner (ostream & outs);
};
