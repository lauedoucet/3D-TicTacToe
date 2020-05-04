/*
	Copyright 2020, Laurence Doucet, All rights reserved
*/

#include "functions.cpp"

using namespace std;

int main() 
{
    // initializing board, each board element holds it's index number
    int board[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27};
    
    greetAndInstruct();

    if (startGame) {
        // game loop (mostly checks for ties)
        while (!checkWinner(board))
        {
            // ask player for their input
            cout << " Please input the cell number you would like to play : ";
            int index;
            cin >> index;
            cout << endl;

            if (index == 99) { cout << " You have exited the game. " << endl; break;}

            // check game conditions (legal move) and update board
            if (checkIfLegal(index, board))
            {
                // updates board with player's input
                board[index-1] = 'X';
                displayBoard(board);
                // checks if player's move has changed game status
                if (isWin(board)) { cout << " Congratulations! You have beaten the Computer. " << endl; break;}

                // computer moves
                cout << " It is now the Computer's turn... " << endl;
                computerMove(board);
                displayBoard(board);
                // checks if computer's move has changed game status
                if (isWin(board)) { cout << " The Computer has won! Better luck next time." << endl; break;}
            } else {
                cout << " Illegal input: please enter a number in the range [1,27]." << endl;
            }
        }
    }
    
    // message for a tie
    if (checkWinner(board) && !isWin(board))
    {
        cout << " It's a tie! " << endl;
    }
}