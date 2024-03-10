#include<iostream>
using namespace std;

int main() {

    // Declare variables
    double loanAmount, interestRate, monthlyPayment, totalInterestPaid, totalCost;

    // Prompt for and read user inputs
    cout << "Please enter the amount of your student loan: ";
    cin >> loanAmount;

    cout << "Please enter the annual interest rate in percentage: ";
    cin >> interestRate;

    cout << "Please enter the monthly payment amount: ";
    cin >> monthlyPayment;

    int months = 0;

    while (loanAmount > 0) {
        loanAmount += loanAmount * ((interestRate / 12) / 100);
        loanAmount -= monthlyPayment;
        months++;
    }

    cout << "It will take you " << months << " months to pay off your student loan." << endl;

    return 0;

}