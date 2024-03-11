#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

int main () {

    // This is absolutely not the best way to do this, but it's definitely the funniest
    for (char again = 'y'; again == 'y' || again == 'Y'; cin >> again) {

        // These need to be constants so we can use them to define the size of the array
        const int gridWidth=30, gridHeight=30;

        // Store map in two-dimensional array
        string mapVisual[gridWidth][gridHeight];

        // Populate the map grid
        for (int i=0; i<gridWidth; i++) // X axis
            for (int j=0; j<gridHeight; j++) // Y axis
                if (i==0 || i==gridWidth-1)
                    mapVisual[i][j] = " -";  // Draw the top and bottom borders
                else if (j==0 || j==gridHeight-1)
                    mapVisual[i][j] = " |"; // Draw the left and right borders
                else
                    mapVisual[i][j] = "  "; // Add an empty space

        int x=15,y=15; // Starting coordinates
        int x1,y1; // Treasure coordinates
        int moves=0; // How long did it take you?
        char direction; // Where to move
        float distance; // How far away from the treasure
        bool treasure=false; // Have you found the treasure?

        mapVisual[y][x] = " X"; // Show the starting position

        // It'd be a pretty boring game if you knew where the treasure was every time
        srand(time(0));
        x1=rand() % gridWidth + 1;
        y1=rand() % gridHeight + 1;

        // Welcome message
        cout << "\nWelcome to Treasure Hunter!  You are currently at (" << x << "," << y << ")." << endl;

        while (!treasure) {

            // Let's show them where they are and where they've been
            for (int i=0; i<gridWidth; i++) {
                for (int j=0; j<gridHeight; j++) {
                    cout << mapVisual[i][j];
                }
                cout << endl;
            }

            // Show us where we've already been
            mapVisual[y][x] = " .";

            // Prompt for input
            cout << "\nYou are currently at (" << x << "," << y << ")." << endl;
            cout << "Enter the direction you want to move (N, S, E, W) or Q to quit: ";
            cin >> direction;

            // Increment the move counter
            moves++;

            // Move the treasure hunter
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
                case 'Q':
                case 'q':
                    cout << "You have quit the game." << endl;
                    return 0;
                default:
                    cout << "Invalid direction.  Please try again." << endl;
                    continue;
            }

            mapVisual[y][x] = " X";

            // Give them the distance to the treasure
            distance = sqrt(static_cast<double>(pow(x1-x,2) + pow(y1-y,2)));

            // Check if they found the treasure
            if (distance == 0) {
                cout << "\nCongratulations! You found the treasure in "<< moves << " moves!" << endl;
                treasure = true;
            } else {
                cout << "\nYou are now " << distance << " units away from the treasure." << endl;
            }
        }

        cout << "Would you like to play again? (y/n) ";

    }
    return 0;

}