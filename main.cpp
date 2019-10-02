#include <iostream>
#include <string.h>
#include <fstream>
#include <time.h>
#include "board.h"

using namespace std;

int main(int argc, char **argv)
{
    srand(time(NULL));
    board *b1;
    int outputDecision;
    int input;
    string sInput;

    cout << "1) Read map file \n2) Generate random board" << endl;
    cin >> input;
    if (input == 1)
    {
        string filename;
        cout << "what is the name of the file?" << endl;
        cin >> filename;
        b1 = new board(filename);
    }
    else
    {
        string input = "";
        double input2 = 0;
        cout << "what are the dimensions of the board? (ex. 5x5)" << endl;
        cin >> input;
        cout << "what is the population density? (between 0 and 1)" << endl;
        cin >> input2;
        int delimPos = input.find("x");
        int row = stoi(input.substr(0,delimPos));
        int column = stoi(input.substr(delimPos + 1));
        b1 = new board(row, column, input2);
    }
    cout << "What game mode? 1) Classic 2)Doughnut 3)Mirror" << endl;
    cin >> input;
    b1->setGameMode(input);
    cout << "Print to 1) console or 2) outfile?" << endl;
    cin >> outputDecision;
    if(outputDecision == 1)
    {
        cout << "Would you like to pause between each generation? y or n?" << endl;
        cin >> sInput;
    }

    if (outputDecision == 1)
        b1->printBoard();
    else if (outputDecision == 2)
        b1->printBoardToFile();
    //cout<<endl;
    if (b1->getGameMode() == 2)
        b1->makeItADonut();
    else if (b1->getGameMode() == 3)
        b1->makeItAMirror();
    if (sInput == "y")
        system("read -p 'Press Enter to continue...' var");
        //cout <<endl;
        //b1->printBoardWithBorders();
    int counter = 0;
    while(!b1->isEmpty() && !b1->isStable())
    {
        counter++;
        //cout << endl;
        //b1->printNeighbors();
        //cout << endl;
        if (b1->getGenNum() > 0)
            b1->storePreviousGen();
        if (b1->getGenNum() > 1)
            b1->store2GensBack();
        b1->nextGeneration();
        //cout << endl;
        if (b1->getGameMode() == 2)
            b1->makeItADonut();
        else if (b1->getGameMode() == 3)
            b1->makeItAMirror();
        if (outputDecision == 1)
            b1->printBoard();
        else if (outputDecision == 2)
            b1->printBoardToFile();
        if (sInput == "y")
            system("read -p 'Press Enter to continue...' var");
    }
}