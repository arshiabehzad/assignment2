#include "cell.h"
#include <iostream> 

using namespace std;

bool isAlive;
char status;
int rowPos;
int colPos;

Cell::Cell()
{
    status = '-';
    isAlive = false;
    rowPos = -1;
    colPos = -1;
}

Cell::Cell(char status)
{
    this->status = status;
    if (status == '-')
        isAlive = false;
    else if (status == 'X')
        isAlive = true;
}

Cell::~Cell()
{

}

void Cell::changeStatusAndLoc(char status, int rowPos, int colPos)
{
    this->status = status;
    this->rowPos = rowPos;
    this->colPos = colPos;
    if (status == '-')
        isAlive = false;
    else if (status == 'X')
        isAlive = true;
}

char Cell::getStatus()
{
    return status;
}

void Cell::setStatus(char status)
{
    this->status = status;
    if (status == '-')
        isAlive = false;
    else if (status == 'X')
        isAlive = true;
}


int Cell::countNeighbors(Cell ** &board, int row, int col)
{
    int nCount = 0;
    for (int i = 0; i < 3; i++)
    {
        if (board[rowPos - 1][colPos - 1 + i].getStatus() == 'X')
            nCount++;
    }
    for (int i = 0; i < 3; i++)
    {
        if (board[rowPos + 1][colPos - 1 + i].getStatus() == 'X')
            nCount++;
    }
    if (board[rowPos][colPos + 1].getStatus() == 'X')
        nCount++;
    if (board[rowPos][colPos - 1].getStatus() == 'X')
        nCount++;
    
    return nCount;

}

