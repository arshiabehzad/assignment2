#include <iostream>
#include "cell.h"

using namespace std;

class board{
    public:
        board();
        board(int row, int col, double popDensity);
        board(string filename);
        void createBoardArray();
        void putInBoard(int positions[], int arraySize);
        void printBoard();
        void printNeighbors();
        void nextGeneration();
        bool isEmpty();
        void setGameMode(int gM);
        int getGameMode();
        void makeItADonut();
        void makeItAMirror();
        void printBoardWithBorders();
        ~board();

        Cell **boardArray;
        int row;
        int col;
        int generation;
        
};