#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

int gridWidth=30, gridHeight=30;

void drawMap(int curX, int curY) {

    // For readability
    cout << endl;

    // X axis
    for (int i=0; i<gridWidth; i++) {

        // Y axis
        for (int j=0; j<gridHeight; j++) {

            if (i==curY && j==curX) {
                // Draw the explorer
                cout << " X";
            } else if (i==0 || i==gridWidth-1) {
                // Draw the top and bottom borders
                cout << " -";
            } else if (j==0 || j==gridHeight-1) {
                // Draw the left and right borders
                cout << " |";
            } else {
                // Add an empty space
                cout << "  ";
            }

        }
        cout << endl;

    }

}

int main () {

    int x=15,y=15; // Explorer’s coordinates
    int x1,y1; // Treasure’s coordinates
    int moves=0; // Keep track of your bet score

    char direction;
    float distance;
    bool treasure=false;

    srand(time(0));
    x1=rand() % gridWidth + 1;
    y1=rand() % gridHeight + 1;

    while (!treasure) {

        // I find visual aids are helpful
        drawMap(x, y);

        // Prompt for input
        cout << "You are currently at (" << x << "," << y << ")." << endl;
        cout << "Enter the direction you want to move (N, S, E, W): ";
        cin >> direction;

        // Increment the move counter
        moves++;

        // Move the explorer
        switch (direction) {
            case 'N':
            case 'n':
                y--;
                break;
            case 'S':
            case 's':
                y++;
                break;
            case 'E':
            case 'e':
                x++;
                break;
            case 'W':
            case 'w':
                x--;
                break;
            default:
                cout << "Invalid direction.  Please try again." << endl;
                continue;
        }

        // Give them the distance to the treasure
        distance = sqrt(static_cast<double>(pow(x1-x,2) + pow(y1-y,2)));

        // Check if they found the treasure
        if (distance == 0) {
            cout << "Congratulations! You found the treasure in "<< moves << " moves!" << endl;
            treasure = true;
        } else {
            cout << "You are now " << distance << " units away from the treasure." << endl;
        }
    }

    return 0;
}