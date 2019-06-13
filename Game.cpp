/*****************************************************************************/
/*                                                                           */
/* File: Game.cpp                                                            */
/* Project: Project 2 - Reversi/Othello - CS 215 Fall 2018                   */
/* Author: Aidan Roth                                                        */
/* Date: Fall 2018                                                           */ 
/* Description: This program creates a game of othello and plays against the */
/*  user. It prints out Instructions and a board and takes input for each    */
/*  move. Once the game ends, it displays a message and the program ends.    */
/*                                                                           */
/*****************************************************************************/

#include "Game.h"
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/*****************************************************************************/
/*                                                                           */
/* Function: Cell default constructor                                        */ 
/* Input parameters: None                                                    */ 
/* Return value: None                                                        */ 
/* Description: Constructs a cell object to be used by the Game class. Each  */
/*   cell represents one square on the board. It's owner is set to None and   */
/*   the cellscore is set to 1.                                               */
/*                                                                           */
/*****************************************************************************/

Game::Cell::Cell ()
{
	owner = NONE;
	cellScore = -1;
}

/*****************************************************************************/
/*                                                                           */
/* Function: Cell Display                                                    */ 
/* Input parameters: an output stream                                        */ 
/* Return value: output stream                                               */ 
/* Description: Displays the owner of the cell with an X, O, or blank space  */
/*                                                                           */
/*****************************************************************************/

void Game::Cell::Display (ostream & outs)
{
	char symbols []  {' ', 'X', 'O'};
	outs << symbols[owner];
}

/*****************************************************************************/
/*                                                                           */
/* Function: Game Default Constructor                                        */ 
/* Input parameters: None                                                    */ 
/* Return value: None                                                        */ 
/* Description: Constructs a Game object with a score of 0 for all players   */
/*                                                                           */
/*****************************************************************************/

Game::Game ()
{
	score[0] = 0;
	score[HUMAN] = 0;
	score[COMPUTER] = 0;
}

/*****************************************************************************/
/*                                                                           */
/* Function: Instructions                                                    */ 
/* Input parameters: an output operator                                      */ 
/* Return value: None                                                        */ 
/* Description: Displays the instructions for Othello and the user interface */
/*                                                                           */
/*****************************************************************************/

void Game::Instructions (ostream & outs)
{
  outs << endl << "Welcome to the all new Computer Video Game of Othello!" << endl <<endl << "You are embarking " 
  "on an adventure into the future of strategic recreation and ground-breaking technology. "
       << endl << "The game of Othello is played on a square board, typically 8 by 8." <<
    endl << "In this version you will be playing against our "
    "state-of-the-art Artificial Intelligence." << endl << "The objective of the game is to control "
    "the majority of the spaces by the time the board is completely filled up,"<<endl<< "or there are no more available moves for either player. Each player"
    " takes turns trying to flip their opponents spaces."<<endl<< "They do this by flanking opposing "
    "squares, meaning placing their token next to their opponents while they " << endl <<  "own another square on "
    "the directly opposite side."<<endl<< "Spaces can be flipped both horizontally and diagonally and"
    " are not limited by the number of spaces that lie in between the flanking tokens."<<endl<< "The game starts with "
    "two 'X's two 'O's near the center of the board. Have fun and good luck!" << endl << endl;
}

/*****************************************************************************/
/*                                                                           */
/* Function: Initializer                                                     */ 
/* Input parameters: None                                                    */ 
/* Return value: None                                                        */ 
/* Description: Initializes values declared in the Game class. Creates       */
/*    appropriate number of cells based on ROWS and COLS variables and sets  */
/*    starting positions to the correct owner. Sets initial scores to 2 each.*/
/*                                                                           */
/*****************************************************************************/

void Game::Init ()
{
	Cell cell;
	for (int r = 1; r <= ROWS; r++)
		for (int c = 1; c <= COLS; c++)
			board[r][c] = cell;
	board[ROWS/2][COLS/2].owner = COMPUTER;
	board[ROWS/2][COLS/2+1].owner = HUMAN;
	board[ROWS/2+1][COLS/2].owner = HUMAN;
	board[ROWS/2+1][COLS/2+1].owner = COMPUTER;
	score[HUMAN] = 2;
	score[COMPUTER] = 2;
}

/*****************************************************************************/
/*                                                                           */
/* Function: Display                                                         */ 
/* Input parameters: an output operator                                      */ 
/* Return value: None                                                        */ 
/* Description: Displays game board with letters across the top and bottom   */
/*  numbers going down the sides as well as the contents of each cell.       */
/*                                                                           */
/*****************************************************************************/

void Game::Display (ostream & outs)
{
	outs << "My Game!" << endl;
	outs << "Scores\tHUMAN: " << score[HUMAN] << "\tCOMPUTER: "
	     << score[COMPUTER] << endl;

	outs << setw(4) << ' ';
	for (int j = 1; j <= COLS; j++) //Writes out letters at the tops of columns
	  {
	    char letter = j + 64; //Sets letter equal to ASCII val of letters starting at A
	    outs << "  " << letter << ' ';
	  }

	outs << endl; //newline and indent before drawing board
	for (int r = 1; r <= ROWS; r++) //loop and nested loop draw structure of board
	{
	  outs << setw(5) << '+';
	  for (int i = 1; i <= COLS; i++)
                    {
                      outs << "---+";
                    }
	  outs << endl << setw(3) << right << r << " |"; //leftside numbering
	  for (int c = 1; c <= COLS; c++)
		{
		  outs << ' ';
		  board[r][c].Display(outs); //Writes out individual cell
		  outs << " |";
		}
	  outs << ' ' << r; //rightside numbering
	  outs << endl;
	}

	//Draws bottom line of the board
	outs << setw(5) << '+'; 
        for (int i = 1; i <= COLS; i++)
              {
                outs << "---+";
               }
	outs  << endl;

	//Writes bottom row of letters
	outs << setw(4) << ' ';
        for (int j = 1; j <= COLS; j++) //Writes out letters at the tops of columns            
          {
            char letter = j + 64; //Sets letter equal to ASCII val of letters starting at A    
            outs << "  " << letter << ' ';
          }
	outs << endl;
}

/*****************************************************************************/
/*                                                                           */
/* Function: CheckBoard                                                      */ 
/* Input parameters: playerType COMPUTER or HUMAN                            */ 
/* Return value: boolean value                                               */ 
/* Description: returns true if there is a possible valid move for the       */
/*  player on the board. Returns false if not, signals end of game           */
/*                                                                           */
/*****************************************************************************/

bool Game::CheckBoard (playerType Who)
{
  for (int r = 1; r <= ROWS; r++)
    {
      for (int c = 1; c <= COLS; c++)
	{
	  if (ValidMove(Who, r, c))
	    return true;
	}
    }
  return false;
}


/*****************************************************************************/
/*                                                                           */
/* Function: ValidMove                                                       */ 
/* Input parameters: playerType HUMAN OR COMPUTER; Row number; column number */ 
/* Return value: boolean                                                     */ 
/* Description: Checks if the Row and Column passed to the function is a     */
/*  valid move for the player, Who. If it is, function returns true. If not, */
/*  function returns false.                                                  */
/*                                                                           */
/*****************************************************************************/

bool Game::ValidMove (playerType Who, int Row, int Col)
{
  //Tertiary operator:
  //Sets other to COMPUTER if Who is HUMAN; sets other to HUMAN if Who is COMPUTER
  playerType other = Who == HUMAN?COMPUTER:HUMAN;
  
  if (board[Row][Col].owner != NONE) //not valid if space is already occupied
    return false;

  if (Row > ROWS || Col > COLS)
    return false;
  if (Row < 1 || Col < 1)
    return false;
 
  //Check area above and to the left
  int r = Row -1; int c = Col -1;
  int count = 0; //used to count # of opp. tokens in path from [r][c]
  while (board[r][c].owner == other)
    {
      count++;
      r--;
      c--;
    }
  if (count > 0 && board[r][c].owner == Who)
    {
      return true;
    }

  //Check area above
  r = Row - 1; c = Col;
  count = 0;
  while (board[r][c].owner == other)
    {
      count++;
      r--;
    }
  if (count > 0 && board[r][c].owner == Who)
    {
      return true;
    }
  
  //Check area above and to the right                                                               
  r = Row -1; c = Col +1;
  count = 0; //used to count # of opp. tokens in path from [r][c]                                        
  while (board[r][c].owner == other)
    {
      count++;
      r--;
      c++;
    }
  if (count > 0 && board[r][c].owner == Who)
    {
      return true;
    }

  //Check area to the right                           
  r = Row; c = Col +1;
  count = 0; //used to count # of opp. tokens in path from [r][c]                             
  while (board[r][c].owner == other)
    {
      count++;
      c++;
    }
  if (count > 0 && board[r][c].owner == Who)
    {
      return true;
    }

  //Check area below and to the right                                                                    
  r = Row +1; c = Col +1;
  count = 0; //used to count # of opp. tokens in path from [r][c]                         
  while (board[r][c].owner == other)
    {
      count++;
      r++;
      c++;
    }
  if (count > 0 && board[r][c].owner == Who)
    {
      return true;
    }

  //Check area below 
  r = Row + 1; c = Col;
  count = 0;
  while (board[r][c].owner == other)
    {
      count++;
      r++;
    }
  if (count > 0 && board[r][c].owner == Who)
    {
      return true;
    }

  //Check area below and to the left
  r = Row +1; c = Col -1;
  count = 0; //used to count # of opp. tokens in path from [r][c]          
  while (board[r][c].owner == other)
    {
      count++;
      r++;
      c--;
    }
  if (count > 0 && board[r][c].owner == Who)
    {
      return true;
    }

  //Check area to the left
  r = Row; c = Col -1;
  count = 0; //used to count # of opp. tokens in path from [r][c]                                
  while (board[r][c].owner == other)
    {
      count++;
      c--;
    }
  if (count > 0 && board[r][c].owner == Who)
    {
      return true;
    }

  return false;
}

/*********************************************************************************/
/*                                                                               */
/* Function: MakeMove                                                            */ 
/* Input parameters: playerType HUMAN or COMPUTER; Row and Column from ChooseMove*/ 
/* Return value: None                                                            */ 
/* Description: Modifies owner of destination space and all spaces between       */
/*  it and the corresponding space that completes the flank                      */
/*                                                                               */
/*********************************************************************************/

void Game::MakeMove (playerType Who, int Row, int Col)
{
  //Tertiary operator:                                                                      
  //Sets other to COMPUTER if Who is HUMAN; sets other to HUMAN if Who is COMPUTER            
  playerType other = Who == HUMAN?COMPUTER:HUMAN;
  
  board[Row][Col].owner = Who;
  //Look and move up and to the left                                                   
  int r = Row -1; int c = Col -1;
  int count = 0; //used to count # of opp. tokens in path from [r][c]                                       
  //First while and if check if direction is valid before executing direction
  while (board[r][c].owner == other)
    {
      count++;
      r--;
      c--;
    }
  if (count > 0 && board[r][c].owner == Who)
    {
      int r = Row -1; int c = Col -1;
      while (board[r][c].owner == other)
	{
	  board[r][c].owner = Who;
	  r--;
	  c--;
	}
    }

  //Look and move to the left                                                                            
  r = Row; c = Col -1;
  count = 0; //used to count # of opp. tokens in path from [r][c]                                       
  //First while and if check if direction is valid before executing direction
  while (board[r][c].owner == other)
    {
      count++;
      c--;
    }
  if (count > 0 && board[r][c].owner == Who)
    {
      int r = Row; int c = Col -1;
      while (board[r][c].owner == other)
	{
	  ValidMove(Who, r, c);
	  board[r][c].owner = Who;
	  c--;
	}
    }

  //Look and move down and to the left
  r = Row + 1; c = Col - 1;
  count = 0; //used to count # of opp. tokens in path from [r][c]   
  while (board[r][c].owner == other)
    {
      count++;
      r++;
      c--;
    }
  if (count > 0 && board[r][c].owner == Who)
    {
      int r = Row + 1; int c = Col -1;
      while (board[r][c].owner == other)
	{
	  board[r][c].owner = Who;
	  r++;
	  c--;
	}
    }

  //Look and move down   
  r = Row + 1; c = Col;
  count = 0; //used to count # of opp. tokens in path from [r][c]                                           
  while (board[r][c].owner == other)
    {
      count++;
      r++;
    }
  if (count > 0 && board[r][c].owner == Who)
    {
      int r = Row + 1; int c = Col;
      while (board[r][c].owner == other)
	{
	  board[r][c].owner = Who;
	  r++;
	}
    }

  //Look and move down and to the right
  r = Row + 1; c = Col + 1;
  count = 0; //used to count # of opp. tokens in path from [r][c]                                       
  while (board[r][c].owner == other)
    {
      count++;
      r++;
      c++;
    }
  if (count > 0 && board[r][c].owner == Who)
    {
      int r = Row + 1; int c = Col +1;
      while (board[r][c].owner == other)
	{
	  board[r][c].owner = Who;
	  r++;
	  c++;
	}
    }
  
  //Look and move to the right                                                                             
  r = Row; c = Col +1;
  count = 0; //used to count # of opp. tokens in path from [r][c]                                           
  while (board[r][c].owner == other)
    {
      count++;
      c++;
    }
  if (count > 0 && board[r][c].owner == Who)
    {
      int r = Row; int c = Col +1;
      while (board[r][c].owner == other)
	{
	  board[r][c].owner = Who;
	  c++;
	}
    }
  
  //Look and move up and to the right                                                                             
  r = Row - 1; c = Col +1;
  count = 0; //used to count # of opp. tokens in path from [r][c]                                           
  while (board[r][c].owner == other)
    {
      count++;
      c++;
      r--;
    }
  if (count > 0 && board[r][c].owner == Who)
    {
      int r = Row - 1; int c = Col + 1;
      while (board[r][c].owner == other)
	{
	  board[r][c].owner = Who;
	  r--;
	  c++;	
	}
    }
  
  //Look and move up                                                     
  r = Row - 1; c = Col;
  count = 0; //used to count # of opp. tokens in path from [r][c]                                           
  while (board[r][c].owner == other)
    {
      count++;
      r--;
    }
  if (count > 0 && board[r][c].owner == Who)
    {
      int r = Row - 1; int c = Col;
      while (board[r][c].owner == other)
	{
	  board[r][c].owner = Who;
	  r--;
	}
    }

  //Update points
  int points = 0;
  int otherPoints = 0;
  for (int i = 1; i <= ROWS; i++)
    {
      for (int j = 1; j <= COLS; j++)
        {
	  if (board[i][j].owner == Who)
	    {
	      points++;
	    }
	  else if (board[i][j].owner == other)
	    {
	      otherPoints++;
	    }
	}
    }
  score[Who] = points;
  score[other] = otherPoints;
}

/*****************************************************************************/
/*                                                                           */
/* Function: Human ChooseMove                                                */ 
/* Input parameters: playerType HUMAN or Computer; Row and Column number     */ 
/*  player chooses; Input and Output streams                                 */ 
/* Return value: boolean value                                               */ 
/* Description:  Prompt user for location of move                            */
/*                                                                           */
/*****************************************************************************/

bool Game::ChooseMove (playerType Who, int & Row, int & Col, istream & In, ostream & Out)
{  
  if (CheckBoard(Who) == false)
    return false;

  char tempCol;
  char tempRow;
  Out << "Enter your move (column row): ";
  In >> tempCol >> tempRow;

  //cout << "Result is : " << isalpha(tempCol) << endl;
  //  return false;
  while (isalpha(tempCol) == 0 )
    {
      //  Out << tempCol << endl;
      Out << endl << "Please make sure you enter Column letter first: ";
      In >> tempCol >> tempRow;
      cout <<"Col: " <<  tempCol << "Row: " << tempRow << endl;
    }

  tempCol = toupper(tempCol) - 64;
  Col = int(tempCol);

  char z = '0';
  Row = int( tempRow - z );
  cout << "Col: " << Col << "\tRow: " << Row << endl;
  while (!ValidMove(Who, Row, Col))
    {
      Out << endl << "Invalid move. Please try again (column row): ";
      In >> tempCol >> Row;
      tempCol = toupper(tempCol) - 64;
      Col = int(tempCol);
    }
  return true;
}

/*****************************************************************************/
/*                                                                           */
/* Function: AI ChooseMove                                                   */ 
/* Input parameters: playerType, Row number, Column number                   */ 
/* Return value: boolean value                                               */ 
/* Description: AI determines desired location of move                       */
/*                                                                           */
/*****************************************************************************/

bool Game::ChooseMove (playerType Who, int & Row, int & Col)
{
  if (CheckBoard(Who) == false)
    return false;
  
  srand(time(0));

  Row = rand() % ROWS + 1;
  Col = rand() % COLS + 1;
      
  while (!ValidMove(Who, Row, Col))
    {
      Row = rand() % ROWS + 1;
      Col = rand() % COLS + 1;
    }

  return true;
}

/*****************************************************************************/
/*                                                                           */
/* Function: Game Done                                                       */ 
/* Input parameters: None                                                    */ 
/* Return value: boolean value                                               */ 
/* Description: Checks if the game is over. Returns true if neither player   */
/*  has any valid moves. Returns false if either one does.                   */
/*                                                                           */
/*****************************************************************************/

bool Game::Done ()
{
  if ((CheckBoard(HUMAN) == true) || (CheckBoard(COMPUTER) == true))
    return false;
  return true;
}

/*****************************************************************************/
/*                                                                           */
/* Function: Game Winner                                                     */ 
/* Input parameters: output stream                                           */ 
/* Return value: playerType HUMAN or COMPUTER                                */ 
/* Description: Prints congratulatory message for correct winner of the game */
/*                                                                           */
/*****************************************************************************/

playerType Game::Winner (ostream & outs)
{
  playerType winner = NONE;
  if(score[HUMAN] > score[COMPUTER])
    {
      winner = HUMAN;
      outs << "Congratulations! You are the winner" << endl;
    }
  else if (score[COMPUTER] > score[HUMAN])
    {
      winner = COMPUTER;
      outs << "The Computer wins!" << endl;
    }
  else
    outs << "The game is a tie! Nobody wins." << endl;

  return winner;
}
