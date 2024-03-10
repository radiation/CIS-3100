#include <iostream>
#include <cstdlib> // For system()
using namespace std;

int main() {

    // Read user choice
    int choice;
    cout << "Select a game to play:\n";
    cout << "1. Choose Your Own Adventure\n";
    cout << "2. The Maddest Of Madlibs\n";
    cin >> choice;

    // I would never actually call a separate file in the real world, but it works for our purposes
    switch (choice) {
        case 1:
            system("../run.sh lab2x4");
            break;
        case 2:
            system("../run.sh lab1x5");
            break;
        default:
            cout << "Invalid choice. Exiting.\n";
    }

    return 0;
}
