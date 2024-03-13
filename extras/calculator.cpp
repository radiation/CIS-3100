#include<iostream>
using namespace std;

int main() {

    int num1, num2, result;
    char operation;

    cout << "Welcome to the calculator program.  Please enter the first number: ";
    cin >> num1;

    cout << "Please enter the second number: ";
    cin >> num2;

    cout << "Please enter the operation you would like to perform (+, -, *, /, or %): ";
    cin >> operation;

    switch (operation) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            result = num1 / num2;
            break;
        case '%':
            result = num1 % num2;
            break;
        default:
            cout << "Invalid operation.  Exiting.\n";
            return 1;
    }

    cout << "The result of " << num1 << " " << operation << " " << num2 << " is " << result << ".\n";
}