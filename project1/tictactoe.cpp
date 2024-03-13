#include <iostream>
#include <ctime>
using namespace std;

// function prototypes
void drawGrid(char grid[3][3]);
char checkWinner(char grid[3][3]);


int main() {

    bool gameOver = false;
    int turn = 1, row, col;
    char player = 'X';

    char grid[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, { ' ', ' ', ' '}};

    cout << "Welcome to Tic Tac Toe!";

    while (!gameOver) {

        if (turn == 10) {
            cout << "It's a draw!" << endl;
            break;
        }

        cout << "Enter player " << player << "'s move (row, column): ";
        cin >> row >> col;

        if (grid[row][col] != ' ' || row < 0 || row > 2 || col < 0 || col > 2)
            cout << "Invalid move! Try again." << endl;
        else{
            // Assign the player's move to the grid
            grid[row][col] = player;

            // Increment turn so we know if the game ends in a draw
            turn++;

            // Display the grid
            drawGrid(grid);

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


void drawGrid(char grid[3][3]) {
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
}

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