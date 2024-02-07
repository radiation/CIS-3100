// Lecture 3, 20240205

#include <iostream>
#include <cmath>
using namespace std;

int main() {

    // Doubles in case our numbers get long
    double x = -3, y, numerator, denominator;

    // Using a decorator so we don't have to rewrite the math in the cout statement
    string decorator;

    while (x <= 4.0) {

        // We should use a function here, but we technically haven't learned that yet
        numerator = ((4 * pow(x,3)) - (12 * pow(x,2)) - (9 * x) + 27);
        denominator = sqrt(5 * pow(x,2) + 2) + (3 * abs(x - 2.5));
        y = numerator / denominator;

        // If there were a lot of conditions, we'd use a switch statement
        if (y == 0) {
            decorator = "ZERO";
        } else if (y < 0) {
            decorator = "NEGATIVE";
        } else {
            decorator = "POSITIVE";
        }

        // And let's print the output
        cout << "x=" << x << ", y = " << y << ", Y IS " << decorator << endl;

        // Infinite loops are bad
        x += 0.5;

    }
    
    return 0;
}