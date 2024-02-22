#include<iostream>
using namespace std;

int main() {

    int countdown;

    cout << "Please enter a number and get ready to count it down:" << endl;

    cin >> countdown;

    for (int i = countdown; i >= 0; i--) {
        cout << "Now we're down to " << i << "!\n";
    }

}