#include<iostream>
#include<utility>
#include<vector>
using namespace std;

// function prototypes
void drawBoard(char playerBoard[10][10]);
void placePlayerShip(char[10][10], int);
void computerMove(char[10][10], vector< pair<int, int> >&);
void playerMove(char[10][10], char[10][10]);
bool checkWinner(char[10][10]);
void initializeComputerMoves(vector< pair<int, int> >&);

int main() {

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

    vector< pair<int, int> > availableMoves;
    initializeComputerMoves(availableMoves);

    for (const auto& ship : ships) {

        // Place the player's ships
        drawBoard(playerBoard);
        cout << "Place your " << ship.first << " (" << ship.second << " spaces)" << endl;
        placePlayerShip(playerBoard, ship.second);

        // Place the computer's ships
        // Define orientation and randomize based on limitation
        char orientation = (rand() % 2 == 0) ? 'h' : 'v';
        int row = rand() % ((orientation == 'h') ? 10 : 10 - ship.second);
        int col = rand() % ((orientation == 'v') ? 10 : 10 - ship.second);

        // Place the ship
        if (orientation == 'h')
            for (int j=0; j<ship.second; j++)
                computerBoard[row][col+j] = 'X';
        else
            for (int j=0; j<ship.second; j++)
                computerBoard[row+j][col] = 'X';

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

void playerMove(char board[10][10], char visibleBoard[10][10]) {
    int row, col;
    cout << "Enter your move (row, column): ";
    cin >> row >> col;
    if (board[row][col] == 'X') {
        cout << "You hit a ship!" << endl;
        visibleBoard[row][col] = 'H';
    } else {
        cout << "You missed!" << endl;
        visibleBoard[row][col] = 'M';
    }
}

bool checkWinner(char board[10][10]) {

    int count = 0;
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            if (board[i][j] == 'X')
                count++;
        }
    }
    cout << "Count: " << count << endl;
    cout << "Winner: " << (count == 0) << endl;
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