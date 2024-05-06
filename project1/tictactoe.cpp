/*
As a fun learning opportunity, I moved the function to draw the board to a library file so we can use it for both tic-tac-toe and battleship.
*/
#include "board.h"
#include <iostream>
#include <ctime>
using namespace std;

// function prototypes
void drawGrid(char grid[3][3], int width, int height);
char checkWinner(char grid[3][3]);


int main() {

    bool gameOver = false;
    int turn = 1, row, col;
    char player = 'X';

    char grid[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, { ' ', ' ', ' '}};

    cout << "Welcome to Tic Tac Toe!\n\n";

    while (!gameOver) {

        if (turn == 10) {
            cout << "It's a draw!" << endl;
            break;
        }

        cout << "Enter player " << player << "'s move (row, column): ";
        cin >> row >> col;

        if (grid[row][col] != ' ' || row < 0 || row > 2 || col < 0 || col > 2)
            cout << "Invalid move! Try again." << endl;
        else {

            // Assign the player's move to the grid
            grid[row][col] = player;

            // Increment turn so we know if the game ends in a draw
            turn++;

            // Display the grid
            drawGrid(grid, 3, 3);

            // Check for a winner
            char winner = checkWinner(grid);
            if (winner != ' ') {
                cout << "Player " << winner << " wins!" << endl;
                gameOver = true;
            }

            // Set to next player
            player = player == 'X' ? 'O' : 'X';

        }

    }

    return 0;
}

// Draw the player and computer boards; we have to pass the width and height of the grid because arrays in C++ are annoying
void drawGrid(char grid[3][3], int width, int height) {

    cout <<"\n+ - - - - - +\n";
    for (int i=0; i<height; i++) {
        cout << "| ";
        for (int j=0; j<width; j++) {
            cout << grid[i][j] << " | ";
        }
        if (i != height-1)
            cout << "\n| - + - + - |\n";
        else
            cout << "\n+ - - - - - +\n";
    }

}

// Pass a reference to the grid and return the winner as a char
char checkWinner(char grid[3][3]) {

    // Check rows
    for (int i=0; i<3; i++) {
        if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2])
            return grid[i][0];
    }

    // Check columns
    for (int i=0; i<3; i++) {
        if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i])
            return grid[0][i];
    }

    // Check diagonals
    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
        return grid[0][0];
    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
        return grid[0][2];

    return ' ';
}