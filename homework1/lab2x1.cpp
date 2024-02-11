#include <iostream>
using namespace std;

int main() {

    // Prompt user for temperature in Farenheit
    cout << "Enter a temperature in Farenheit: ";
    int temperature;
    cin >> temperature;
    if (temperature < 40) {
        cout << "It is very cold today.\n";
    } else if (temperature < 80) {
        cout << "It is a beautiful day outside!\n";
    } else {
        cout << "It is very hot today.\n";
    }

    return 0;
}