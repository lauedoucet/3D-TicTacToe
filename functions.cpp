/* 
	Assignment 1 for COMP 322
	Laurence Doucet
	260799839
*/

#include <iostream>
#include <string>

using namespace std;

// global bool that tells us whether to start the game or not
bool startGame = 0;

/*  ************************ helper methods ****************************  */

// checks if all the spots are used on the board
bool isFull(char board[])
{
    int n = 0;
    for (int i=0; i<27; i++)
    {
        if (board[i] != '-')
        {
            n++;
        }
    }
    if (n == 27) { return true;}
    else { return false;}
}

// checks for vertical wins
bool verticalWin(char board[])
{
    bool winner = 0;
    for (int i=0; i<27; i++)
    {
        if (board[i] == board[i+3] && board[i] == board[i+6] && board[i] != '-') { winner = 1;}

        if (i == 2 || i == 11 || i == 20) { i = i + 8;}
    }
    return winner;
}

// checks for horizontal wins
bool horizontalWin(char board[])
{
    bool winner = 0;
    for (int i=0; i<27; i = i+3)
    {
        if (board[i] == board[i+1] && board[i] == board[i+2] && board[i] != '-') { winner = 1;}
    }
    return winner;
}

// checks for diagonal wins
bool diagonalWin(char board[])
{
    bool winner = 0;
    // diagonal win towards the right
    for (int i=0; i<27; i = i+9)
    {
        if (board[i] == board[i+4] && board[i] == board[i+8] && board[i] != '-') {winner = 1;}
    }
    // diagonal win towards the left
    for (int i=2; i<27; i = i+9)
    {
        if (board[i] == board[i+2] && board[i] == board[i+4] && board[i] != '-') {winner = 1;}
    }
    return winner;
}

// checks for 3D wins
bool win3D(char board[])
{
    bool winner = 0;
    for (int i=0; i<9; i++)
    {
        // same spot
        if (board[i] == board[i+9] && board[i] == board[i+18] && board[i] != '-') {winner = 1;}
        // 3D horizontal win
        if (i == 0 || i == 3 || i == 6)
        {
            if (board[i] == board[i+10] && board[i] == board[i+20] && board[i] != '-') {winner = 1;}
        }
    }

    // 3D diagonal wins
    if (board[0] == board[13] && board[0] == board[26] && board[0] != '-') { winner = 1;}
    if (board[20] == board[13] && board[20] == board[6] && board[20] != '-') { winner = 1;}

    return winner;
}

// checks if there is a win only (not ties)
bool isWin(char board[])
{
    return (verticalWin(board) || horizontalWin(board) || diagonalWin(board) || win3D(board));
}

/* ********************assignment methods ************************************/

void displayBoard(char board[])
{
    // line format for board
    string line[] {"\t", " | ", " | "};
    // board index
    int i = 0;

    for (int k=0; k<3; k++) 
    {
         for (int j=0; j<3; j++)
        {
            for (string space : line)
            {
                cout << space << board[i];
                i++;
            }
            i = i + 6;
        }
        i = i - 24;
        cout << endl;
    }
}

void greetAndInstruct()
{
    // start by introducing the player to the game
    string intro[] {" Hello and welcome to the Tic-Tac-Toe challenge: Player against Computer.", 
    "   ... 3D Edition!!! ", " The board is numbered from 1 to 27 as per the following: "};

    for (string line : intro)
    {
        cout << line << endl;
    }

    // displaying the board indices
    string line[] {"\t", " | ", " | "};
    int i = 1;

    for (int k=0; k<3; k++) 
    {
         for (int j=0; j<3; j++)
        {
            for (string space : line)
            {
                cout << space << i;
                i++;
            }
            i = i + 6;
        }
        i = i - 24;
        cout << endl;
    }

    //start instructions
    string start[] = {" Player starts first. Simply input the number of the cell you want to occupy.", 
    " Player's move is marked with X. Computer's move is marked with O.", " Start? (y/n): "};

    for (string line : start)
    {
        cout << line << endl;
    }

    // get start input from user
    char answer;
    cin >> answer;
    if (answer == 'y')
    {
        // start the game!
        startGame = true;
    }
    else if (answer == 'n') {
        cout << " You have exited the game." << endl;
        startGame = false;
    }
}

bool checkIfLegal(int cellNbre, char board[])
{
    // checks range of cellNbre and is spot is used
    if ( cellNbre < 1 || cellNbre > 27)
    {
        cout << " Your input is out of range." << endl;
        return false;
    } else if (board[cellNbre-1] != '-') {
        cout << " This spot in the board is already used." << endl;
        return false;
    } else {
        return true;
    }
}

bool checkWinner(char board[])
{
    if (isWin(board)) 
    {
        // checks of every type of win
        return true;
    } else if (isFull(board)) {
        // no win and the board is full implies a tie
        return true;
    } else {
        return false;
    }
}

void computerMove(char board[])
{
    bool moved = 0;
    // check if computer can win
    for (int i=0; i<27; i++)
    {
        // checks all empty spots
        if (board[i] == '-')
        {
            board[i] = 'O';
            if (isWin(board)) { moved = 1; break;}
            else { board[i] = '-'; }
        }
    }
    
    // check if computer can block the player
    if (!moved) 
    {
        // block a win
       for (int i=0; i<27; i++)
        {
            if (board[i] == '-')
            {
                board[i] = 'X';
                if (isWin(board)) { board[i] = 'O'; moved = 1; break; }
                else { board[i] = '-'; }
            }
        } 
    }

    // computer moves randomly if we can't win or block
    while (!moved)
    {
        int i = rand() % 27;
        if (board[i] == '-')
        {
            board[i] = 'O';
            moved = 1;
        }
    }
    
}
