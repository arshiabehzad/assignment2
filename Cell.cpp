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

/*changes the status of the cell (dead or alive)(- or X) and gives the 
location of it in the array*/
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

//changes the status of the cell (dead or alive) (- or X)
void Cell::setStatus(char status)
{
    this->status = status;
    if (status == '-')
        isAlive = false;
    else if (status == 'X')
        isAlive = true;
}

//counts the neighbors next to the cell 
int Cell::countNeighbors(Cell ** &board, int row, int col)
{
    int nCount = 0;
    //checks 3 positions above
    for (int i = 0; i < 3; i++)
    {
        if (board[rowPos - 1][colPos - 1 + i].getStatus() == 'X')
            nCount++;
    }
    //checks 3 positions below
    for (int i = 0; i < 3; i++)
    {
        if (board[rowPos + 1][colPos - 1 + i].getStatus() == 'X')
            nCount++;
    }
    //checks position to the right
    if (board[rowPos][colPos + 1].getStatus() == 'X')
        nCount++;
    //checks position to the left
    if (board[rowPos][colPos - 1].getStatus() == 'X')
        nCount++;
    
    return nCount;

}

