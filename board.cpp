#include <iostream>
#include <fstream>
#include <string.h>
#include "board.h"
#include <time.h>
#include <stdio.h> 
#include <stdlib.h>
#include <cstddef>

using namespace std;

Cell **boardArray;
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
    int rowCounter = 1;
    int colCounter = 1;
    //goes through file and adds each element of the grid to the array
    for (int i = 0; i < row + 2; i++)
    {
        for (int k = 0; k < col + 2; k++)
        {
            boardArray[i][k].changeStatusAndLoc('-', i, k);
        }
    }
    while (getline(mapFile, line))
    {
        for (int i = 0; i < line.length(); i++){
                boardArray[rowCounter][colCounter].changeStatusAndLoc(line[i], rowCounter, colCounter);
                colCounter++;
        }
        rowCounter++;
        colCounter = 0;
    }
   
    mapFile.close();
}

board::board(int row, int col, double popDensity)
{
    this->row = row;
    this->col = col;
    int spaces = row*col;
    int Xs = spaces*popDensity;
    createBoardArray();
    int *rands = new int[Xs];
    bool inArray = false;
    for (int i = 0; i < Xs; i++){
        rands[i] = 0;
    }
    for (int i = 0; i < Xs; i++)
    {
        int tempRand = rand() % spaces;
        for (int k = 0; k < Xs; k++)
        {
            if (rands[k] == tempRand)
            {
                inArray = true;
                break;
            }
        }
        if (inArray == true){
            inArray = false;
            continue;
        }
        rands[i] = tempRand;
        
    }
    
    for (int i = 0; i < row+2; i++)
    {
        for (int k = 0; k < col+2; k++)
        {
            boardArray[i][k].changeStatusAndLoc('-',i,k);
        }
    }
    putInBoard(rands, Xs);
}

board::~board()
{
}

void board::setGameMode(int gM)
{
    gameMode = gM;
}

int board::getGameMode()
{
    return gameMode;
}

void board::makeItADonut()
{
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

void board::createBoardArray()
{
    boardArray = new Cell *[row+2];
    for (int i = 0; i < row+2; i++)
        boardArray[i] = new Cell[col+2];
}

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
}

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

void board::putInBoard(int positions[], int arraySize)
{
    int counter = 0;
    bool nextNum = false;
    for (int i =0; i < arraySize; i++)
    {
        for (int j = 1; j < row+1; j++)
        {
            for (int k = 1; k < col+1; k++)
            {
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

void board::nextGeneration()
{

    Cell **tempBoardArray = new Cell *[row + 2];
    for (int i = 0; i < row + 2; i++)
        tempBoardArray[i] = new Cell[col + 2];

    for (int i = 0; i < row+2; i++)
    {
        for (int k = 0; k < col+2; k++)
        {
            tempBoardArray[i][k] = boardArray[i][k];
        }
    }

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

    for (int i = 0; i < row + 2; i++)
    {
        for (int k = 0; k < col + 2; k++)
        {
            boardArray[i][k] = tempBoardArray[i][k];
        }
    }
    generation++;
}

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