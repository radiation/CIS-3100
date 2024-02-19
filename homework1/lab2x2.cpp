/*
    I know I overcomplicated this, but using marginal tax rates was much more interesting than a flat tax.  I opted
    to use a two-dimensional array to store the tax brackets and their respective marginal tax rates; I then iterate
    through the array to calculate the total tax based on the salary.  Using some sort of iterable makes it much 
    easier to add or remove tax brackets, and reducing tech debt is critical in the real world.

    Test data:

     $20,000, 0 deps, no int =  $2,880 (12000*0.06 +  8000*0.27)
     $20,000, 2 deps, no int =  $2,340 (12000*0.06 +  6000*0.27)
     $40,000, 0 deps, no int =  $8,400 (12000*0.06 + 26000*0.27 + 2000*0.33)
     $40,000, 2 deps, no int =  $7,200 (12000*0.06 + 24000*0.27)
     $50,000, 0 deps, no int = $11,700 (12000*0.06 + 26000*0.27 + 12000*0.33)
     $50,000, 2 deps, no int = $10,050 (12000*0.06 + 26000*0.27 +  7000*0.33)
     $80,000, 0 deps, no int = $25,850 (12000*0.06 + 26000*0.27 + 17000*0.33 + 25000*0.50)
     $80,000, 2 deps, no int = $21,850 (12000*0.06 + 26000*0.27 + 16000*0.33 + 25000*0.50)
    $100,000, 0 deps, no int = $35,850 (12000*0.06 + 26000*0.27 + 17000*0.33 + 45000*0.50)
    $100,000, 2 deps, no int = $30,850 (12000*0.06 + 26000*0.27 + 17000*0.33 + 40000*0.50)
 */

#include <iostream>
#include <iomanip> // for std::setprecision
using namespace std;

int main() {

    /*
        Two dimensional array of tax brackets.  The first element is the amount up to which the current marginal rate 
        applies, and the second is the marginal tax rate itself.  I would have used a struct, but we haven't covered
        those yet and I'm already getting pretty aggressive with the logic.
    */
    const double taxBrackets[][2] = {
        {0, 0.06},
        {12000, 0.27},
        {38000, 0.33},
        {55000, 0.50}
    };

    // Pretty wild that there's no simple length function for arrays in C++, but this is the best way to do it
    const int numBrackets = sizeof(taxBrackets)/sizeof(taxBrackets[0]);

    // Variable definitions
    double salary, totalTax = 0.0;
    int dependendents;
    char studentLoanInterestYN;

    // Prompt for and read user inputs
    cout << "Please enter your annual salary: ";
    cin >> salary;

    cout << "And how many dependents do you have? ";
    cin >> dependendents;

    cout << "And did you pay student loan interest? (y/n) ";
    cin >> studentLoanInterestYN;

    // Reduce salary by 5% for each dependent and use this for calculations
    double remainingSalary = salary * (1 - (0.05 * dependendents));

    // If student loan interest was paid, reduce salary by that amount.
    if (studentLoanInterestYN == 'y' || studentLoanInterestYN == 'Y') {
        // No need to declare this if there was no student loan interest so we do it in the if statement
        double studentLoanInterest;
        cout << "How much student loan interest did you pay? ";
        cin >> studentLoanInterest;
        remainingSalary -= studentLoanInterest;
    }

    totalTax = 0;
    int previous = 0;

    // Iterate through all but the last bracket and calculate total tax based on marginal tax rates
    for (int i = 0; i < numBrackets-1; i++) {

        // No need to keep going
        if (remainingSalary <= 0)
            break;

        // We could've used a ternary operator here, but I think this is more readable
        double taxableAmount = std::min(remainingSalary , taxBrackets[i+1][0] - taxBrackets[i][0]);

        // Add tax and reduce remaining taxable salary
        totalTax += taxableAmount * taxBrackets[i][1];
        remainingSalary -= taxableAmount;
    }

    // If there's anything left, add the final tax bracket
    if (remainingSalary > 0)
        totalTax += remainingSalary * taxBrackets[numBrackets-1][1];

    // Make sure we display two decimal places
    std::cout << std::fixed << std::setprecision(2);

    // And final output
    cout << "This year you paid $" << totalTax << " in tax, so your net salary after tax is $" << salary - totalTax << ".\n";

    return 0;
}