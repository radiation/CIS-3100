#include <iostream>
#include <cctype> // For tolower and toalpha, from https://cplusplus.com/reference/cctype/
using namespace std;

int main() {

    char c1, c2, c3;

    cout << "Input character #1" << endl;
    cin >> c1;

    cout << "Input character #2" << endl;
    cin >> c2;

    cout << "Input character #3" << endl;
    cin >> c3;

    // Not sure if this matters or not, but it was mentioned in the assignment
    if(!(std::isalpha(c1) && std::isalpha(c2) && std::isalpha(c3)))
        cout << "Not all characters are letters; those will appear first." << endl;

    // This block covers all cases.  In the real world, we'd use a library function for this.
    if (tolower(c1) < tolower(c2))
        if (tolower(c2) < tolower(c3))
            cout << c1 << ", " << c2 << ", " << c3 << endl;
        else if (tolower(c1) < tolower(c3))
            cout << c1 << ", " << c3 << ", " << c2 << endl;
        else
            cout << c3 << ", " << c1 << ", " << c2 << endl;
    else
        if (tolower(c1) < tolower(c3))
            cout << c2 << ", " << c1 << ", " << c3 << endl;
        else if (tolower(c2) < tolower(c3))
            cout << c2 << ", " << c3 << ", " << c1 << endl;
        else
            cout << c3 << ", " << c2 << ", " << c1 << endl;

    return 0;
}