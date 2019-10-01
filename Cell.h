#include <iostream>


using namespace std;

class Cell
{
    public:
        bool isAlive;
        char status;
        int rowPos;
        int colPos;
        Cell();
        Cell(char status);
        ~Cell();
        void changeStatusAndLoc(char status, int rowPos, int colPos);
        int countNeighbors(Cell **&board, int row, int col);
        char getStatus();
        void setStatus(char status);
        
};