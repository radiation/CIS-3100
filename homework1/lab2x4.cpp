#include <iostream>
using namespace std;

int main() {
    int choice1, choice2, choice3;

    cout << "Welcome to the Forest Adventure!" << endl;
    cout << "You find yourself standing at the entrance of a dark, mysterious forest. Do you:" << endl;
    cout << "1. Enter the forest" << endl;
    cout << "2. Walk around it" << endl;
    cout << "> ";
    cin >> choice1;

    if (choice1 == 1) {
        cout << "You bravely enter the forest. After walking for a while, you come to a fork in the path. Do you:" << endl;
        cout << "1. Take the left path" << endl;
        cout << "2. Take the right path" << endl;
        cout << "> ";
        cin >> choice2;

        if (choice2 == 1) {
            cout << "You take the left path and encounter a talking owl. The owl offers you two choices. Do you:" << endl;
            cout << "1. Ask for wisdom" << endl;
            cout << "2. Ask for directions out of the forest" << endl;
            cout << "> ";
            cin >> choice3;

            if (choice3 == 1) {
                cout << "The owl imparts wisdom upon you, and you feel enlightened. With your new wisdom, you easily find your way out of the forest. Congratulations!" << endl;
            } else {
                cout << "The owl gives you directions, and you quickly find your way out of the forest. Safe travels!" << endl;
            }
        } else {
            cout << "You take the right path and stumble upon a hidden treasure chest. Do you:" << endl;
            cout << "1. Open it" << endl;
            cout << "2. Ignore it and continue" << endl;
            cout << "> ";
            cin >> choice3;

            if (choice3 == 1) {
                cout << "You open the chest to find it filled with gold and jewels! You're rich! Congratulations on your find!" << endl;
            } else {
                cout << "You decide not to let greed guide you and continue your walk. Eventually, you find a peaceful clearing and rest. A peaceful end to your adventure." << endl;
            }
        }
    } else {
        cout << "You decide to walk around the forest. It's a long walk, but safe. You have missed the adventures inside, but sometimes safety is its own adventure. Well done!" << endl;
    }

    return 0;
}