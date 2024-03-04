#include<iostream>
using namespace std;

int main() {

    char letter;

    cout << "Enter a letter: ";
    cin >> letter;

    cout << "First switch statement: ";

    switch (letter) {
        case 'a':
            cout << letter << " is a vowel\n";
            break;
        case 'e':
            cout << letter << " is a vowel\n";
            break;
        case 'i':
            cout << letter << " is a vowel\n";
            break;
        case 'o':
            cout << letter << " is a vowel\n";
            break;
        case 'u':
            cout << letter << " is a vowel\n";
            break;
        default:
            cout << letter << " is a consonant\n";
    }

    cout << "Second switch statement:";

    switch (letter) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            cout << letter << " is a vowel\n";
            break;
        default:
            cout << letter << " is a consonant\n";
    }

    return 0;
}