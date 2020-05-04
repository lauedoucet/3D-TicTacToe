/* 
	Copyright 2020, Laurence Doucet, All rights reserved
*/

#include <iostream>
#include <string>

using namespace std;

// global bool that tells us whether to start the game or not
bool startGame = 0;

/*  ************************ helper methods ****************************  */

// checks if all the spots are used on the board
bool isFull(int board[])
{
    int n = 0;
    for (int i=0; i<27; i++)
    {
        if (board[i] == 'X' || board[i] == 'O') 
        {
            n++;
        }
    }
    if (n == 27) { return true;}
    else { return false;}
}

// checks for vertical wins
bool verticalWin(int board[])
{
    bool winner = 0;
    for (int i=0; i<27; i++)
    {
        if (board[i] == board[i+3] && board[i] == board[i+6]) { winner = 1;}

        if (i == 2 || i == 11 || i == 20) { i = i + 8;}
    }
    return winner;
}

// checks for horizontal wins
bool horizontalWin(int board[])
{
    bool winner = 0;
    for (int i=0; i<27; i = i+3)
    {
        if (board[i] == board[i+1] && board[i] == board[i+2]) { winner = 1;}
    }
    return winner;
}

// checks for diagonal wins
bool diagonalWin(int board[])
{
    bool winner = 0;
    // diagonal win towards the right
    for (int i=0; i<27; i = i+9)
    {
        if (board[i] == board[i+4] && board[i] == board[i+8]) {winner = 1;}
    }
    // diagonal win towards the left
    for (int i=2; i<27; i = i+9)
    {
        if (board[i] == board[i+2] && board[i] == board[i+4]) {winner = 1;}
    }
    return winner;
}

// checks for 3D wins
// TODO: missing some winning cases (vertical accross 3D)
bool win3D(int board[])
{
    bool winner = 0;
    for (int i=0; i<9; i++)
    {
        // same spot
        if (board[i] == board[i+9] && board[i] == board[i+18]) {winner = 1;}
        // 3D horizontal win
        if (i == 0 || i == 3 || i == 6)
        {
            if (board[i] == board[i+10] && board[i] == board[i+20]) {winner = 1;}
        }
        // 3D vertical win
        if (i == 0 || i == 1 || i == 2)
        {
            if (board[i] == board[i+12] && board[i] == board[i+24]) {winner = 1;}
        }
    }

    // 3D diagonal wins
    if (board[0] == board[13] && board[0] == board[26]) { winner = 1;}
    if (board[20] == board[13] && board[20] == board[6]) { winner = 1;}

    return winner;
}

// checks if there is a win only (not ties)
bool isWin(int board[])
{
    return (verticalWin(board) || horizontalWin(board) || diagonalWin(board) || win3D(board));
}

// checks if one of the neighbouring cells has a certain symbol and changes cell i accordingly
bool checkNeighbours(int i, int board[], char symbol)
{
    bool moved = 0;
    switch(i) {
        case 0:
        case 9:
        case 18:
            if (board[i+1] == symbol || board[i+3] == symbol || board[i+4] == symbol) {  board[i] == 'O'; moved = 1;   }
            break;
        case 1:
        case 10:
        case 19:
            if (board[i-1] == symbol || board[i+1] == symbol || board[i+2] == symbol || board[i+3] == symbol 
                || board[i+4] == symbol) {  board[i] == 'O'; moved = 1;   }
            break;
        case 2:
        case 11:
        case 20:
            if (board[i-1] == symbol || board[i+2] == symbol || board[i+3] == symbol) {  board[i] == 'O'; moved = 1;   }
            break;
        case 3:
        case 12:
        case 21:
            if (board[i-3] == symbol || board[i-2] == symbol || board[i+1] == symbol || board[i+3] == symbol
                || board[i+4] == symbol) {  board[i] == 'O'; moved = 1;   } 
            break;
        case 4:
        case 13:
        case 22:
            if (board[i-4] == symbol || board[i-3] == symbol || board[i-2] == symbol || board[i-1] == symbol 
                || board[i+1] == symbol || board[i+2] == symbol || board[i+3] == symbol || board[i+4] == symbol )
                {     board[i] == 'O'; moved = 1;   } 
            break;
        case 5:
        case 14:
        case 23:
            if (board[i-4] == symbol || board[i-3] == symbol || board[i-1] == symbol || board[i+2] == symbol || board[i+3] == symbol)
                {     board[i] == 'O'; moved = 1;   } 
            break;
        case 6:
        case 15:
        case 24:
            if (board[i-3] == symbol || board[i-2] == symbol || board[i+1] == symbol ) {     board[i] == 'O'; moved = 1;   } 
            break;
        case 7: 
        case 16:
        case 25:
            if (board[i-4] == symbol || board[i-3] == symbol || board[i-2] == symbol || board[i-1] == symbol 
                || board[i+1] == symbol) {     board[i] == 'O'; moved = 1;   } 
            break;
        case 8: 
        case 17: 
        case 26:
            if (board[i-4] == symbol || board[i-3] == symbol || board[i-1] == symbol) {     board[i] == 'O'; moved = 1;   } 
            break;
    }
    return moved;
}

/* ********************assignment methods ************************************/

void displayBoard(int board[])
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
                if ( board[i] == 'X' || board[i] == 'O')
                {
                    char c = (char) board[i];
                    cout << space << c;
                } else {
                    int c = board[i];
                    cout << space << c;
                }
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

bool checkIfLegal(int cellNbre, int board[])
{
    // checks range of cellNbre and is spot is used
    if ( cellNbre < 1 || cellNbre > 27)
    {
        cout << " Your input is out of range." << endl;
        return false;
    } else if ((board[cellNbre-1] == 'X' || board[cellNbre-1] == 'O')) {
        cout << " This spot in the board is already used." << endl;
        return false;
    } else {
        return true;
    }
}

bool checkWinner(int board[])
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

void computerMove(int board[])
{
    bool moved = 0;
    for (int i=0; i<27; i++)
    {
        // check all empty cells
        if ((board[i] != 'X' || board[i] != 'O'))
        {
            int cell = board[i];
            // check if computer can win
            board[i] = 'O';
            if (isWin(board)) { moved = 1; break;}
            else { board[i] = cell; }
        }
    }

    if (!moved)
    {
        for (int i=0; i<27; i++)
        {
            // check all empty cells
            if ((board[i] != 'X' || board[i] != 'O'))
            {
                int cell = board[i];
                // check if computer can block player
                board[i] = 'X';
                if (isWin(board)) { board[i] = 'O'; moved = 1; break;}
                else { board[i] = cell; }
            }
        }
    }
    
    if (!moved)
    {
        for (int i=0; i<27; i++)
        {
            // move next to 'O' if there is one on the board
            if ((board[i] != 'X' || board[i] != 'O'))
            {
                if (checkNeighbours(i, board, 'O')) { board[i] = 'O'; moved = 1; break;}
            }
        }
    }

    if (!moved)
    {
        for (int i=0; i<27; i++)
        {
            // move next to 'X' if there is one on the board
            if ((board[i] != 'X' || board[i] != 'O'))
            {
                if (checkNeighbours(i, board, 'X')) { board[i] = 'O'; moved = 1; break;}
            }
        }
    }
}
    