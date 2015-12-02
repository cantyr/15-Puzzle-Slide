// main.cpp

// Author: Ryan Canty

// Date: 11/24/15

// Course: CSC1610

// Description: This file implements a sliding 15-puzzle.  This game is played on a 
// 4x4 grid of tile (array of integers) There are 15 (1-15) integers and 1 blank space.
// The goal of the game is to slide the numbers around the blank space to the blank space,
// trying to make the numbers on the tiles move to when they are in numerical order.

// Input: One user-defined integer collected from the standard input stream
// (keyboard).

// Output: The changed array depending on the move the user wants to make.

#include <cstdlib>
#include <iomanip>
#include <cassert>
#include <iostream>
#include <ctime>

using namespace std;

void drawBoard( int[][4] ); //Prototype
bool puzzleSolved( int[][4]); //Prototype
void getTilePosition( int[][4], int, int&, int& ); //Prototype
bool moveTile( int[][4], int, int ); //Prototype
void populateBoard( int[][4] ); //Prototype

int main()
{
    
    int board[4][4];
    //Array that will be the board
    
    populateBoard( board );
    
    do
    {
        drawBoard( board ); //Output the board
        int row = 0;//Integer that will hold the row at which the number the user picks is.
        int col = 0;//Integer that will hold the column at which the number the user picks is.
        int tileSelect;//What tile the user select
        cout << endl;
        cout << "Please enter a tile value: "; //Prompt user
        cin >> tileSelect; //Store user input
        cout << endl;
        getTilePosition( board, tileSelect, row, col ); //Get the position of the number the 
                                                         //user picks
        moveTile( board, row, col ); //Move the tile the user picks to the blank space, and
                                    //the blank space to where the user selected number was
    }
    while( puzzleSolved( board ) != 1 );
    //Do all of the above until the puzzle is solved
    
    cout << "Congratulations! You solved the puzzle." << endl;
    
    return 0;
}
//Description: Draws the board the game will be played with.
//Precondition: The board must be a 4x4 array.
//Postcondition: The board is outputted to the user.
void drawBoard( int board[][4] )
{
    int row; //Integer used in for loop to traverse rows of array
    int col; //Integer used in for loop to traverse columns of array
    cout << "+---+---+---+---+" << endl;
    for( row = 0; row < 4; row++ ) //Traverse through each row
    {
        for( col = 0; col < 4; col++ ) //Traverse through each column
        {
            cout << "|";
            if( board[row][col] != 0 )
            {
                cout << setw(2) << board[row][col] << " ";
            }   //output the rows and columns of the board if the tile is not 0
            else
            {
                cout << setw(2) << "   ";
            }   //If the tile is 0, output a space
        }
        cout << "|" << endl;
        cout << "+---+---+---+---+" << endl;
    }
}
//Description: This function checks to see if the user solved the puzzle. If they
//solved it, return true.  If not, return false.
//Precondition: The board must be a 4x4 array.
//Postcondition: True is returned if the puzzle is solved, false if it is not.
bool puzzleSolved( int board[][4] )
{
    int row; //Integer used in for loop to traverse rows of array
    int col; //Integer used in for loop to traverse columns of array
    int tileNum = 1; //Integer that will be used to check if the numbers are in order
    for( row = 0; row < 4; row++ )//Traverse through each row
    {
        for( col = 0; col < 4; col++ )//Traverse through each column
        {
            if( board[row][col] == tileNum )
            {
                tileNum++; //Increment by 1 if the previous number is in place
                if( tileNum == 16)
                {
                    tileNum = 0;
                }
            }       //If the tile is equal to 16, set it equal to 0
            else
            {
                return false;
            }   //If a number is not in place, return false
        }
    }
    return true; //Return true if all numbers are in place
}
//Description: This function finds the location of where the user selected tile is.
//Precondition: Tile must be between 1 and 15.
//Postcondition: The row and column of the tile selected is returned.
void getTilePosition( int board[][4], int tile, int& row, int& col )
{
    //assert( tile >= 1);
    //assert( tile <= 15);
    for( int r = 0; r < 4; r++ ) //Traverse through rows
    {
        for( int c = 0; c < 4; c++ ) //Traverse through columns
        {
            if( board[r][c] == tile )
            {
                row = r;
                col = c;
            }   //Once the tile is found, set row equal to what row it is at and col 
        }       //equal to what column it is at. These values are passed by reference 
    }
}
//Description: This function moves the user selected tile to the blank space, and the 
//blank space to where the user tile was.
//Precondition: The board must be a 4x4 array.
//Postcondition: The new board is displayed with the tiles moved.
bool moveTile( int board[][4], int row, int col )
{  
   int tilePosition = board[row][col];
   if( row != 0 ) //Not on far left column to avoid out of bounds
   {
       if( board[row - 1][col] == 0 )
       {
           board[row - 1][col] = tilePosition;
           board[row][col] = 0;
           return true;
       }   //If the tile is above the selected tile, swap, and return true
   }
   if( row != 3 ) //Not on far right column to avoid out of bounds
   {
       if( board[row + 1][col] == 0 )
       {
           board[row + 1][col] = tilePosition;
           board[row][col] = 0;
           return true;
       }    //If the tile is below the selected tile, swap, and return true
   }
   if( col != 0 ) //Not on top row to avoid out of bounds
   {
       if( board[row][col - 1] == 0 )
       {
           board[row][col - 1] = tilePosition;
           board[row][col] = 0;
           return true;
       }    //If the tile is to the left of the selected tile, swap, and return true
   }
   if( col != 3 ) //Not on bottom row to avoid out of bounds
   {
       if( board[row][col + 1] == 0 )
       {
           board[row][col + 1] = tilePosition;
           board[row][col] = 0;
           return true;
       }    //If the tile is to the right of the selected tile, swap, and return true
   }
   cout << "Invalid move. Please try again." << endl;
   cout << endl;
   return false;
   //If invalid move, return false 
}
//Description: This function creates a solved board and then scrambles the tiles of that 
//board.
//Precondition: The board must be a 4x4 array.
//Postcondition: The scrambled board is outputted.
void populateBoard( int board[][4] )
{
    int row = 0; //Integer that will hold the row at which the number the user picks is
    int col = 0; //Integer that will hold the column at which the number the user picks is
    int tileNum = 1; //Integer that will be put on the board
    for( int row = 0; row < 4; row++ ) //Traverse through rows
    {
        for( int col = 0; col < 4; col++ ) //Traverse through columns
        {
            if( tileNum == 16 )
            {
                tileNum = 0;
            }   //Set the integer on the board to 0 if it is 16 (last tile is blank)
            board[row][col] = tileNum;
            tileNum++;
        }   //Place tileNum in each location of the array, incrementing by 1 each time to
    }       //fill the board
    srand(time(0)); //Seed random number generator
    for( int i = 0; i < 30; i++ ) //Repeat 30 times
    {
        getTilePosition( board, 0, row, col ); //Find the index where 0 is located
        int tileDirection; //Integer that will be used to determine where you look for a swap
        tileDirection = (rand() % 4) + 1; //Make tileDirection equal to a random number between
        int holdTile;                                    //0 and 4
        //Integer that will store the position of neighboring tiles of 0
        if( tileDirection == 1 && row > 0 )
        {
            holdTile = board[row - 1][col];
            board[row - 1][col] = board[row][col];
            board[row][col] = holdTile;
        }   //if you can swap with above tile, make the swap
        else if( tileDirection == 1 && row == 0 )
        {
            i--;
            //If you cannot swap with above tile, decrement i by 1 so a new number is generated
        }   //and looks at next if statement
        if( tileDirection == 2 && row < 3 )
        {
            holdTile = board[row + 1][col];
            board[row + 1][col] = board[row][col];
            board[row][col] = holdTile;
        }   //if you can swap with below tile, make the swap
        else if( tileDirection == 2 && row == 3 )
        {
            i--;
            //If you cannot swap with below tile, decrement i by 1 so a new number is generated
        }   //and looks at next if statement
        if( tileDirection == 3 && col > 0 )
        {
            holdTile = board[row][col - 1];
            board[row][col - 1] = board[row][col];
            board[row][col] = holdTile;
        }   //if you can swap with left tile, make the swap
        else if( tileDirection == 3 && col == 0 )
        {
            i--;
            //If you cannot swap with left tile, decrement i by 1 so a new number is generated
        }   //and looks at next if statement
        if( tileDirection == 4 && col > 3 )
        {
            holdTile = board[row][col + 1];
            board[row][col + 1] = board[row][col];
            board[row][col] = holdTile;
        }   //if you can swap with right tile, make the swap
        else if( tileDirection == 4 && col == 3 )
        {
            i--;
            //If you cannot swap with left tile, decrement i by 1 so a new number is generated
        }   //and looks at next if statement
    }
}