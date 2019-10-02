#include <iostream>
#include <fstream>
#include <string.h>
#include "board.h"
#include <time.h>
#include <stdio.h> 
#include <stdlib.h>
#include <cstddef>

//NOTE: see readme for explanation of how I go about doing different modes and how I set up my array

using namespace std;

Cell **boardArray;
Cell **prevBoardArray;
Cell **prev2BoardArray;
int row = 0;
int col = 0;
int generation = 0;
int gameMode = 1;

board::board()
{
    
}

// sets up board by opening a file 
board::board(string filename)
{
    // opens file
    ifstream mapFile;
    string line;
    mapFile.open(filename);
    //string row/column variables
    string sRow = "";
    string sColumn = "";
    //gets first two lines and stores them as row and column
    getline(mapFile, sRow);
    getline(mapFile, sColumn);
    //converts to integer
    row = stoi(sRow);
    col = stoi(sColumn);
    cout << row << "x" << col <<endl;
    //dynamically creates 2d array
    createBoardArray();

    //instantiates previous board array
    prevBoardArray = new Cell *[row + 2];
    for (int i = 0; i < row + 2; i++)
        prevBoardArray[i] = new Cell[col + 2];

    //instiates 2 previous board array
    prev2BoardArray = new Cell *[row + 2];
    for (int i = 0; i < row + 2; i++)
        prev2BoardArray[i] = new Cell[col + 2];

    int rowCounter = 1;
    int colCounter = 1;
    //goes through file and adds each element of the grid to the array
    
    //initializes the board 
    for (int i = 0; i < row + 2; i++)
    {
        for (int k = 0; k < col + 2; k++)
        {
            boardArray[i][k].changeStatusAndLoc('-', i, k);
        }
    }

    //goes through the file and adds the board in the file and adds it to the matrix
    while (getline(mapFile, line))
    {
        for (int i = 0; i < line.length(); i++){
                boardArray[rowCounter][colCounter].changeStatusAndLoc(line[i], rowCounter, colCounter);
                colCounter++;
        }
        rowCounter++;
        colCounter = 0;
    }
    //closes file
    mapFile.close();
}

//sets up board by making a random board
board::board(int row, int col, double popDensity)
{
    //sets global variables to variables passed in
    this->row = row;
    this->col = col;
    //calculates total amount of spaces in the array
    int spaces = row*col;
    //calculates how many live cells there should be
    int Xs = spaces*popDensity;
    //instantiates previous board array
    prevBoardArray = new Cell *[row + 2];
    for (int i = 0; i < row + 2; i++)
        prevBoardArray[i] = new Cell[col + 2];
    //instantiates previous 2 board array
    prev2BoardArray = new Cell *[row + 2];
    for (int i = 0; i < row + 2; i++)
        prev2BoardArray[i] = new Cell[col + 2];
    //instantiates board array
    createBoardArray();
    //creates an array to store random integers
    int *rands = new int[Xs];
    //boolean that is used to check if a random integer is already in an array
    bool inArray = false;
    //instantiates a random array
    for (int i = 0; i < Xs; i++){
        rands[i] = 0;
    }
    /*this loop creates a random number from 1 to the total number of spaces in the array
    for ever live cell that was calculated to be needed then it assigns this to the random 
    number array as long as it is not already in the array */
    for (int i = 0; i < Xs; i++)
    {
        // temporarily stores the random number 
        int tempRand = rand() % spaces;
        for (int k = 0; k < Xs; k++)
        {
            //checks if the random number is already in the array
            if (rands[k] == tempRand)
            {
                inArray = true;
                break;
            }
        }
        //continues if the number generated was the same as another already in the array
        if (inArray == true){
            inArray = false;
            continue;
        }
        //if the random number generated is unique adds it the array
        rands[i] = tempRand;
        
    }

    //initializes the board array  
    for (int i = 0; i < row+2; i++)
    {
        for (int k = 0; k < col+2; k++)
        {
            boardArray[i][k].changeStatusAndLoc('-',i,k);
        }
    }

    //calls method to put the live cells in the array based of the random number positions generated
    putInBoard(rands, Xs);
}

board::~board()
{
    //deletes all of the arrays from memory after its not being used anymore 
    for (int i =0; i < row + 2; ++i)
        delete[] boardArray[i];
    delete[] boardArray;

    for (int i = 0; i < row + 2; ++i)
        delete[] prevBoardArray[i];
    delete[] prevBoardArray;

    for (int i = 0; i < row + 2; ++i)
        delete[] prev2BoardArray[i];
    delete[] prev2BoardArray;
}

void board::setGameMode(int gM)
{
    gameMode = gM;
}

int board::getGameMode()
{
    return gameMode;
}

//converts the border around the 2d array in a one that will work as if the board is a donut
void board::makeItADonut()
{
    //arrays to temporarily store rows and columns to copy them to the borders of the array 
    Cell *rowPlacerArray = new Cell[row];
    Cell *colPlacerArray = new Cell[col];

    //places a copy of the top of the board and adds it to the bottom border of the array 
    for (int i = 1; i < col + 1; i++)
    {
        rowPlacerArray[i-1] = boardArray[1][i];
    }
    for (int i = 1; i < col + 1; i++)
    {
        boardArray[row + 1][i] = rowPlacerArray[i - 1];
    }

    //places a copy of the bottom of the board and adds it to the top border of the array
    for (int i = 1; i < col + 1; i++)
    {
        rowPlacerArray[i - 1] = boardArray[row][i];
    }
    for (int i = 1; i < col + 1; i++)
    {
        boardArray[0][i] = rowPlacerArray[i - 1];
    }
    
    //places a copy of the left side of the board and adds it the right border of the array
    for (int i = 1; i < row + 1; i++)
    {
        colPlacerArray[i-1] = boardArray[i][1];
    }
    for (int i = 1; i < row + 1; i++)
    {
        boardArray[i][col+1] = colPlacerArray[i-1];
    }

    //places a copy of the right side of the board and adds it the left border of the array
    for (int i = 1; i < row + 1; i++)
    {
        colPlacerArray[i - 1] = boardArray[i][col];
    }
    for (int i = 1; i < row + 1; i++)
    {
        boardArray[i][0] = colPlacerArray[i-1];
    }
}

//converts the border around the 2d array in a one that will work as if the board is a mirror
void board::makeItAMirror()
{
    Cell *rowPlacerArray = new Cell[row];
    Cell *colPlacerArray = new Cell[col];

    //places a copy of the top of the board and adds it to the bottom border of the array
    for (int i = 1; i < col + 1; i++)
    {
        rowPlacerArray[i - 1] = boardArray[1][i];
    }
    for (int i = 1; i < col + 1; i++)
    {
        boardArray[0][i] = rowPlacerArray[i - 1];
    }

    //places a copy of the bottom of the board and adds it to the top border of the array
    for (int i = 1; i < col + 1; i++)
    {
        rowPlacerArray[i - 1] = boardArray[row][i];
    }
    for (int i = 1; i < col + 1; i++)
    {
        boardArray[row+1][i] = rowPlacerArray[i - 1];
    }

    //places a copy of the left side of the board and adds it the right border of the array
    for (int i = 1; i < row + 1; i++)
    {
        colPlacerArray[i - 1] = boardArray[i][1];
    }
    for (int i = 1; i < row + 1; i++)
    {
        boardArray[i][0] = colPlacerArray[i - 1];
    }

    //places a copy of the right side of the board and adds it the left border of the array
    for (int i = 1; i < row + 1; i++)
    {
        colPlacerArray[i - 1] = boardArray[i][col];
    }
    for (int i = 1; i < row + 1; i++)
    {
        boardArray[i][col + 1] = colPlacerArray[i - 1];
    }
}

//instantiates board array()
void board::createBoardArray()
{
    boardArray = new Cell *[row+2];
    for (int i = 0; i < row+2; i++)
        boardArray[i] = new Cell[col+2];
}

//prints out the board at its current states
void board::printBoard()
{
    cout << "Generation " << generation << ":" << endl;
    for (int i = 1; i < row+1; i++)
    {
        for (int k = 1; k < col+1; k++)
        {
            cout << boardArray[i][k].getStatus();
        }
        cout << endl;
    }
    cout << endl;
}

//prints out the board to an outfile at its current states
void board::printBoardToFile()
{
    ofstream outfile;
    //opens the out file in a mode to append it
    outfile.open("arshia.out", ofstream::app);
    outfile << "Generation " << generation << ":" << endl;
    for (int i = 1; i < row + 1; i++)
    {
        for (int k = 1; k < col + 1; k++)
        {
            outfile << boardArray[i][k].getStatus();
        }
        outfile << endl;
    }
    outfile<<endl;
    outfile.close();
}

/*helper function used to print the boardarray with borders to see if it works properly
not used in the actual program*/
void board::printBoardWithBorders()
{
    for (int i = 0; i < row + 2; i++)
    {
        for (int k = 0; k < col + 2; k++)
        {
            cout << boardArray[i][k].getStatus();
        }
        cout << endl;
    }
}

/*Determines where to put the live cells (Xs) in the array based off the positions passed in*/
void board::putInBoard(int positions[], int arraySize)
{
    //counter is used to calculate what position to put the X into the array
    int counter = 0;
    //used to break out of loops and restart process
    bool nextNum = false;
    //for loop to go through each position in the position array
    for (int i =0; i < arraySize; i++)
    {
        //next two for loops are to go through the 2D array
        for (int j = 1; j < row+1; j++)
        {
            for (int k = 1; k < col+1; k++)
            {
                // once the correct location is found change the Cell status to X
                if (counter == positions[i])
                {
                    boardArray[j][k].changeStatusAndLoc('X',j,k);
                    counter = 0;
                    nextNum = true;
                    break;
                }
                counter++;
            }
            if (nextNum == true)
            {
                nextNum = false;
                break;
            }
        }
    }
} 

int board::getGenNum()
{
    return generation;
}

//stores the previous generation in array to be used to compare 
void board::storePreviousGen()
{
    for (int i = 0; i < row+2; i++)
    {
        for (int k = 0; k < col+2; k++)
        {
            prevBoardArray[i][k] = boardArray[i][k];
        }
    }
}

//stores the previous, previous generation in array to be used to compare
void board::store2GensBack()
{
    for (int i = 0; i < row + 2; i++)
    {
        for (int k = 0; k < col + 2; k++)
        {
            prev2BoardArray[i][k] = prevBoardArray[i][k];
        }
    }
}

//checks wether or not the game is stable. returns it as a bool
bool board::isStable()
{
    bool stable = true;
    /*checks wether or not the last two generations were the same and if it is sets stable 
     to false*/
    for (int i = 1; i < row+1; i++)
    {
        for (int k = 1; k < col+1; k++)
        {
            if (prevBoardArray[i][k].getStatus() != boardArray[i][k].getStatus())
            {
                stable = false;
                //cout << "it works1";
                break;
            }
        }
    }
    /*checks wether or not the generations are are alternating between two states and 
    if it is sets stable to false*/
    /*
    for (int i = 1; i < row + 1; i++)
    {
        for (int k = 1; k < col + 1; k++)
        {
            if (prev2BoardArray[i][k].getStatus() != boardArray[i][k].getStatus())
            {
                stable = false;
                cout << "it works2";
                break;
            }
        }
    }
    cout << stable <<endl;*/
    return stable;

}

//checks if the board is empty and returns it as a bool
bool board::isEmpty()
{
    for (int i = 1; i < row+1; i++)
    {
        for (int k = 1; k < col+1; k++)
        {
            if (boardArray[i][k].getStatus() == 'X')
                return false;
        }
    }
    return true;
}

//generates the next generation
void board::nextGeneration()
{
    /*instantiates a temp board array so that when changes are made they are all changed at the same time 
      and it doesnt affect the current generation */
    Cell **tempBoardArray = new Cell *[row + 2];
    for (int i = 0; i < row + 2; i++)
        tempBoardArray[i] = new Cell[col + 2];

    //sets the temp array equal to all elements in the boardArray
    for (int i = 0; i < row+2; i++)
    {
        for (int k = 0; k < col+2; k++)
        {
            tempBoardArray[i][k] = boardArray[i][k];
        }
    }

    /*goes through the array and checks the neighbor count and decides for each cell wether it
      dies, if a new cell "grows" or if it stays the same */
    for (int i = 1; i < row+1; i++)
    {
        for (int k = 1; k < col+1; k++)
        {
            if (tempBoardArray[i][k].countNeighbors(boardArray, row, col) <= 1)
            {
                tempBoardArray[i][k].setStatus('-');
            }
            else if (tempBoardArray[i][k].countNeighbors(boardArray, row, col) == 3)
            {
                tempBoardArray[i][k].setStatus('X');
            }
            else if (tempBoardArray[i][k].countNeighbors(boardArray, row, col) >= 4)
            {
                tempBoardArray[i][k].setStatus('-');
            }
        }
    }

    //adds the new temp array that has the next generation stored to the actual board array
    for (int i = 0; i < row + 2; i++)
    {
        for (int k = 0; k < col + 2; k++)
        {
            boardArray[i][k] = tempBoardArray[i][k];
        }
    }
    //adds a number to the generation
    generation++;
}

//helper function used to see the neighbors of each cell, not used in the class
void board::printNeighbors()
{
    for (int i = 1; i < row+1; i++)
    {
        for (int k = 1; k < col+1; k++)
        {
            cout << boardArray[i][k].countNeighbors(boardArray, row, col);
        }
        cout << endl;
    }
   
}

//clears a file
void board::clearFile()
{
    ofstream outfile;
    outfile.open("arshia.out", std::ofstream::out | std::ofstream::trunc);
    outfile.close();
}