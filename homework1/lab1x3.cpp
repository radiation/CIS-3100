#include<iostream>
using namespace std;

int numbers[4];

int main() {
    double sum = 0;
    for (int i = 0; i < 4; i++) {
        cout << "Please enter number #" << i + 1 << ": ";
        cin >> numbers[i];
        sum += numbers[i];
    }
    cout << "The sum of the numbers is " << sum << endl;
    cout << "The average of the numbers is " << sum / 4 << endl;
    return 0;
}