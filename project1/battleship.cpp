#include<iostream>
#include<utility>
#include<vector>
using namespace std;

// function prototypes
void drawBoard(char[10][10]);
void placePlayerShip(char[10][10], int);
void computerMove(char[10][10], vector< pair<int, int> >&);
bool isPlacementValid(char[10][10], int, int, char, int);
void playerMove(char[10][10], char[10][10]);
bool checkWinner(char[10][10]);
void initializeComputerMoves(vector< pair<int, int> >&);

int main() {

    // Seed the random number generator
    srand(time(0));

    bool gameOver = false;

    // We're using a vector of pairs to store the ships and their lengths because they're different data types
    vector< pair<string, int> > ships;
    ships.push_back(make_pair("Battleship", 4));
    ships.push_back(make_pair("Carrier", 5));
    ships.push_back(make_pair("Destroyer", 3));
    ships.push_back(make_pair("Patrol Boat", 2));
    ships.push_back(make_pair("Submarine", 3));

    // Define and initialize boards
    char playerBoard[10][10], computerBoard[10][10], visibleComputerBoard[10][10];
    for (int i = 0; i < 10; i++) {
        for (int j=0; j<10; j++) {
            playerBoard[i][j] = ' ';
            computerBoard[i][j] = ' ';
            visibleComputerBoard[i][j] = ' ';
        }
    }

    // We're also using vectors of pairs to keep track of moves and hits. By using a vector, when we're in hunt mode 
    // we can randomly select a move without worrying about repeating moves or having to "reroll" a move
    vector< pair<int, int> > availableMoves, hitList;
    initializeComputerMoves(availableMoves);

    for (const auto& ship : ships) {

        // Place the player's ships
        drawBoard(playerBoard);
        cout << "Place your " << ship.first << " (" << ship.second << " spaces)" << endl;
        placePlayerShip(playerBoard, ship.second);
        // Place the computer's ships
        // Define orientation and randomize based on limitation
        bool placed = false;
        while (!placed) {
            char orientation = (rand() % 2 == 0) ? 'h' : 'v';
            int row = rand() % ((orientation == 'h') ? 10 : 10 - ship.second);
            int col = rand() % ((orientation == 'v') ? 10 : 10 - ship.second);
            cout << "Computer trying to place " << ship.first << " at (" << row << ", " << col << ") " << orientation << endl;

            // Check if placement is valid
            if (isPlacementValid(computerBoard, row, col, orientation, ship.second)) {
                cout << "Computer placed " << ship.first << " at (" << row << ", " << col << ") " << orientation << endl;

                // Place the ship
                if (orientation == 'h') {
                    for (int j = 0; j < ship.second; j++) {
                        computerBoard[row][col + j] = 'X';
                    }
                } else { // Vertical orientation
                    for (int j = 0; j < ship.second; j++) {
                        computerBoard[row + j][col] = 'X';
                    }
                }
                placed = true;
            }
        }
    }

    // Let's play the game
    while (!checkWinner(playerBoard) && !checkWinner(computerBoard)) {

        cout << "\nPlayer Board" << endl;
        drawBoard(playerBoard);

        cout << "\nComputer Board" << endl;
        drawBoard(visibleComputerBoard);

        // Player move
        playerMove(computerBoard, visibleComputerBoard);

        // Computer move
        computerMove(playerBoard, availableMoves);

    }

    if (checkWinner(playerBoard)) {
        cout << "You win!" << endl;
    } else {
        cout << "You lose!" << endl;
    }
    return 0;
}

// We'll create a list of all possible moves for the computer to make so we don't repeat moves
void initializeComputerMoves(vector< pair<int, int> >& moves) {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            moves.push_back(make_pair(i, j));
        }
    }
}

// Function to remove a move from the list of available moves
void removeMove(vector< pair<int, int> >& availableMoves, pair<int, int> move) {
    auto it = lower_bound(availableMoves.begin(), availableMoves.end(), move);
    if (it != availableMoves.end() && *it == move) {
        availableMoves.erase(it);
    }
}

// Function to make a move for the computer
void computerMove(char board[10][10], vector< pair<int, int> >& moves) {

    int index = rand() % moves.size();
    int row = moves[index].first;
    int col = moves[index].second;

    if (board[row][col] == 'X') {
        cout << "The computer hit your ship!" << endl;
        board[row][col] = 'H';
    } else {
        cout << "The computer missed!" << endl;
        board[row][col] = 'M';
    }

    // Remove the selected move
    moves.erase(moves.begin() + index);

}

// Function to check if placing a ship at a given position and orientation conflicts with existing ships
bool isPlacementValid(char board[10][10], int row, int col, char orientation, int shipSize) {
    if (orientation == 'h') {
        // Check horizontally for conflicts
        for (int j = col; j < col + shipSize; j++) {
            if (j >= 10 || board[row][j] != ' ') {
                return false; // Conflict detected
            }
        }
    } else { // Vertical orientation
        // Check vertically for conflicts
        for (int i = row; i < row + shipSize; i++) {
            if (i >= 10 || board[i][col] != ' ') {
                return false; // Conflict detected
            }
        }
    }
    return true; // No conflict detected
}

// Function to place a ship on the board
void playerMove(char board[10][10], char visibleBoard[10][10]) {
    int row, col;
    cout << "Enter your move (row, column): ";
    cin >> row >> col;
    if (board[row][col] == 'X') {
        cout << "You hit a ship!" << endl;
        board[row][col] = 'H';
        visibleBoard[row][col] = 'H';
    } else {
        cout << "You missed!" << endl;
        visibleBoard[row][col] = '*';
    }
}

// Function to check if the player or computer has won
bool checkWinner(char board[10][10]) {

    int count = 0;
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            if (board[i][j] == 'X')
                count++;
        }
    }
    return (count == 0);

}

// Draw the player and computer boards
void drawBoard(char playerBoard[10][10]) {

    cout <<"+ - - - - - - - - - - - - - - - - - - - +\n";
    for (int i=0; i<10; i++) {
        cout << "| ";
        for (int j=0; j<10; j++) {
            cout << playerBoard[i][j] << " | ";
        }
        if (i != 9)
            cout << "\n| - + - + - + - + - + - + - + - + - + - |\n";
        else
            cout << "\n+ - - - - - - - - - - - - - - - - - - - +\n";
    }

}

// Function to place a ship on the board
void placePlayerShip(char board[10][10], int shipLength) {
    bool valid = false;
    while (!valid) {
        int row, col;
        char orientation;
        cout << "Should the ship be placed horizontally (h) or vertically (v)? ";
        cin >> orientation;
        cout << "Where would you like to place your ship? (row, column): ";
        cin >> row >> col;

        // Check if the ship can be placed
        if (orientation == 'h')
            if (board[row][col+shipLength] != ' ')
                cout << "Invalid move! Try again." << endl;
            else
                for (int i=0; i<shipLength; i++) {
                    valid = true;
                    board[row][col+i] = 'X';
                }
        else
            if (board[row+shipLength][col] != ' ')
                cout << "Invalid move! Try again." << endl;
            else
                for (int i=0; i<shipLength; i++) {
                    valid = true;
                    board[row+i][col] = 'X';
                }
    }
}