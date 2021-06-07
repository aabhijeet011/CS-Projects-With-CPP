#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

using namespace std;
int getUserResponse();

class Board
{
    char positionsSelected[16];
    char winner;

public:
    Board(){
        winner = 'z';
        for(int i=0;i<16;i++){
            positionsSelected[i] = '_';
        }
    }
    char* getPositions(void)
    {//return all the positions on the board
        return positionsSelected;
    }
    int setPosition(int gridNumber, char user)
    {//set a given position to x or o
        {
            if(positionsSelected[gridNumber] == '_')
            {
                positionsSelected[gridNumber] = user;
                return 0;
            }
            else
            {
                //cout<<"That position is taken\n";
                return -1;
            }
        }
        return 0;
    }
    char checkRows()
    {//check the rows for a winner
        int rows = 0;
        int columns = 0;
        int fourInRowX = 0;
        int fourInRowO = 0;

        //Check rows for a winner
        for(int rows = 0; rows<16; rows=rows+4)
        {
            for(int i = 0; i < 4; i++)
            {
                if(positionsSelected[i + rows] == 'x')
                    fourInRowX++;
                if(positionsSelected[i + rows] == 'o')
                    fourInRowO++;
            }
            if(fourInRowX == 4)
            {
                //cout<<"ROWS X won\n";
                winner = 'x';
                return 'x';
            }
            if(fourInRowO == 4)
            {
                //cout<<"ROWS O won\n";
                winner = 'o';
                return 'o';
            }
            fourInRowX = 0;
            fourInRowO = 0;
        }
        return 'z';
    }
    char checkColumns()
    {//check the columns for a winner
        int rows = 0;
        int columns = 0;
        int fourInRowX = 0;
        int fourInRowO = 0;

        //Check columns for a winner
        for(int columns = 0; columns<4; columns++)
        {
            for(int i = 0; i < 16; i= i + 4)
            {
                if(positionsSelected[i + columns] == 'x')
                    fourInRowX++;
                if(positionsSelected[i + columns] == 'o')
                    fourInRowO++;
            }
            if(fourInRowX == 4)
            {
                //cout<<"COLUMNS X won\n";
                winner = 'x';
                return 'x';
            }
            if(fourInRowO == 4)
            {
                //cout<<"COLUMNs O won\n";
                winner = 'o';
                return 'o';
            }
            fourInRowX = 0;
            fourInRowO = 0;
        }
        return 'z';
    }
    char checkDiagonals()
    {//check the diagonals for a winner
        char winner = 'z';
        int fourInRowX = 0;
        int fourInRowO = 0;

        //check left to right diagonal
        for(int i = 0; i < 16; i=i+5)
        {
            if(positionsSelected[i] == 'x')
                fourInRowX++;
            if(positionsSelected[i] == 'o')
                fourInRowO++;
        }

        //check right to left diagonal
        if(fourInRowO != 4 and fourInRowX != 4)
        {
            fourInRowX = 0;
            fourInRowO = 0;
            for(int i = 3; i < 15; i= i+3)
            {
                if(positionsSelected[i] == 'x')
                    fourInRowX++;
                if(positionsSelected[i] == 'o')
                    fourInRowO++;
            }
        }

        if(fourInRowX == 4)
        {
            //cout<<"DIAGONALS X won\n";
            winner = 'x';
            return winner;
        }
        if(fourInRowO == 4)
        {
            //cout<<"DIAGONALS O won\n";
            winner = 'o';
            return winner;
        }
        fourInRowX = 0;
        fourInRowO = 0;
        return winner;
    }
    char determineWinner()
    {//if 4 in a row, then there is a winner
        char winner = 'z';
        winner =  checkRows();
        if(winner == 'z')
            winner = checkColumns();
        if(winner =='z')
            winner = checkDiagonals();
        return winner;
    }

};


void checkResponse(Board &boardIn, char input)
{
    int position;
    int userInput;
    do
    {
        position = getUserResponse();
        userInput = boardIn.setPosition(position, input);
        if(userInput == -1){
            cout<<"That position is taken.";
        }
    }while(userInput == -1);
}
void getUserNames(string &userX,string &userY){
    cout<<"Name of user to be 'x':";
    cin>>userX;
    cout<<"Name of user to be 'o':";
    cin>>userY;
}

void printBlankBoard(){
        for(int i=0;i<16;i++){
            cout<<"|"<<i<<":";
            if(i<=9){
                cout<<" ";
            }
            if(i%4 == 3){
                cout<<"|\n";
            }
        }
        cout<<"\n\n";
}
void printTheBoard(Board boardIn)
{//print the board with player moves
    printBlankBoard();

    for(int i = 0; i <16; i++)
    {
        std::cout<<"|"<<boardIn.getPositions()[i];
        if(i%4 == 3)
        {
            std::cout<<"|\n";
        }
    }
    cout<<"\n\n\n";
}

void writeTheBoard(Board boardIn)
{//print the board with player moves
    cout<<"\n\n";
    for(int i = 0; i <16; i++)
    {
        cout<<"|"<<boardIn.getPositions()[i];
        if(i%4 == 3)
        {
            cout<<"|\n";
        }
    }
    cout<<"\n\n\n";
}
void printUserPrompt(string nameIn, char letter)
{//prompt for user input
    std::cout<<nameIn<<" where would you like to place an "<<letter<<"?: ";
    cout<<"\n\n";
    cout<<" where would you like to place an "<<letter<<"?: ";
}
void printGameWinner(Board boardIn, string nameX, string nameO)
{//print the winner statement
    char winner;
    winner = boardIn.determineWinner();
    if(winner == 'x')
    {
        cout<<"Congrats "<<nameX<<" you won!\n\n";
    }
    if(winner == 'o')
    {
        cout<<"Congrats "<<nameO<<" you won!\n\n";
    }
}
int getUserResponse()
{//get the chosen user position, check that it is an integer
    //check that it is between 0 and 15 inclusive
    int position = -1;
    cout<<"Enter an integer between 0 and 15: ";
    std::cin>>position;

    while(position > 15 or position < 0 or !cin)
    {
        cin.clear();
        //cin.ignore(numeric_limits<streamsize>::max(), '\n');
        std::cout<<"That is not a valid position\n";
        cout<<"Enter an integer between 0 and 15: ";
        cin.clear();
        cin>>position;
    }
    return position;
}



int main(){
  Board gameBoard;
  string nameX;
  string nameO;

  int tieGame = 0;
  char gameWinner = 'z';
  int numTurns = 0;

  // Get Names of Player
  getUserNames(nameX,nameO);
  // no. of turns = 8 maximum
  while(numTurns<8){
    printTheBoard(gameBoard);
    printUserPrompt(nameX,'x');
    checkResponse(gameBoard,'x');
    gameWinner = gameBoard.determineWinner();

    if(gameWinner != 'z'){
        printTheBoard(gameBoard);
        writeTheBoard(gameBoard);
        printGameWinner(gameBoard,nameX,nameO);
        break;

    }

    printTheBoard(gameBoard);
    writeTheBoard(gameBoard);

    printUserPrompt(nameO,'o');
    checkResponse(gameBoard,'o');
    printTheBoard(gameBoard);
    writeTheBoard(gameBoard);
    gameWinner = gameBoard.determineWinner();

    if(gameWinner != 'z'){
        printTheBoard(gameBoard);
        writeTheBoard(gameBoard);
        printGameWinner(gameBoard,nameX,nameO);
        break;
    }
    numTurns++;

  }
  if(numTurns>=8)
    cout<<"Tie Game \n";
  return 0;


}
