#include <iostream>
using namespace std;

int main() {

    // For loops are much better for ops like this
    int odd_sum = 0, even_sum = 0;
    for (int i = 1; i <= 100; i++)
        if (i % 2 == 1) // odd
            odd_sum += i;
        else // even
            even_sum += i;

    // Print output; no need for a separate variable for total sum
    cout << "Sum of all odd integers 1-100: " << odd_sum << endl;
    cout << "Sum of all even integers 1-100: " << even_sum << endl;
    cout << "Sum of all integers 1-100: " << odd_sum + even_sum << endl;

    return 0;
}