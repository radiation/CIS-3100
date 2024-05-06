#include "board.h"
#include <iostream>
using namespace std;

// Draw the player and computer boards; we have to pass the width and height of the grid because arrays in C++ are annoying
void drawGrid(char grid[3][3], int width, int height) {

    string header="\n+ ", separator="\n| ";
    for (int i=0; i<(width*2-1); i++) {
        header += "- ";
        separator += "- ";
        if (i != (width*2-2)) {
            header += "+ ";
            separator += "- ";
        }
    }
    header += "+\n";
    separator += "\n";

    cout << "\n+ - - - - - +\n";
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