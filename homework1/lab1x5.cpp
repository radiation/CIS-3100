#include<iostream>
using namespace std;

string noun[3];
string verb[3];
string adjective[3];
string adverb[3];

int main() {
    cout << "I'll ask you for three each of nouns, verbs, adjectives, and adverbs, and then I'll tell you story.  Ready?\n";
    for (int i = 0; i < 3; i++) {
        cout << "Enter a noun: \n";
        cin >> noun[i];
        cout << "Enter a verb: \n";
        cin >> verb[i];
        cout << "Enter an adjective: \n";
        cin >> adjective[i];
        cout << "Enter an adverb: \n";
        cin >> adverb[i];
    }

    cout << "Once upon a time in a " << adjective[0] << " kingdom, there lived a " << noun[0] << " who was known for ";
    cout << adverb[0] << " " << verb[0] << "ing. One day, a " << adjective[1] << " " << noun[1] << " appeared and challenged the ";
    cout << noun[0] << " to a " << adjective[2] << " " << verb[1] << " contest. The " << noun[0] << " accepted the challenge and ";
    cout << adverb[2] << " " << verb[2] << "ed into the " << adjective[0] << " " << noun[2] << ", where they " << adverb[0];
    cout << " " << verb[0] << " with all their " << adjective[0] << " might. The " << noun[0] << " " << adverb[2] << " " << verb[0] << " and ";
    cout << "emerged victorious, earning the title of the " << adjective[2] << " " << noun[0] << " of the kingdom.\n";

    return 0;
}