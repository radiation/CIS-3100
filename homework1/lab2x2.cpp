#include <iostream>
#include <map>
using namespace std;

/*
    I know I overcomplicated this, but using marginal tax rates was much more interesting than a flat tax.  I opted to 
    use maps for the key/value storage, and because iterating makes it much easier to do add or change tax brackets in the future.
    I used https://favtutor.com/blogs/iterate-through-map-cpp and https://www.programiz.com/cpp-programming/map to get the syntax correct.
 */
int main() {

    double tax_brackets[4][2] = {
        {0, 0.06},
        {12000, 0.27},
        {38000, 0.33},
        {50000, 0.50}
    };

    double salary, tax;
    int dependendents;

    // Prompt user for annual salary
    cout << "Please enter your annual salary: ";
    cin >> salary;

    // And dependents
    cout << "And how many dependents do you have? ";
    cin >> dependendents;

    tax = 0;
    int previous = 0;

    // Iterate through brackets and calculate total tax based on marginal tax rates
    for (int i = 0; i < 4; i++) {
        if (salary > tax_brackets[i][0]) {
            tax += (tax_brackets[i][0] - tax_brackets[i-1][0]) * tax_brackets[i][1];
            previous = tax_brackets[i][0];
        } else {
            tax += (salary - previous) * tax_brackets[i][1];
            break;
        }
    }

    cout << "Your total tax is " << tax << endl;

    return 0;
}