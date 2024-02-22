#include<iostream>
using namespace std;

int main() {

    int counter = 1, daysWorked, startingSalary = 2;

    cout << "How many days have you worked?" << endl;

    cin >> daysWorked;

    while (daysWorked > 0) {
        cout << "You've worked " << counter++ << " days, and you've earned $" << startingSalary << "!" << endl;
        startingSalary *= 2;
        daysWorked--;
    }

    return 0;

}