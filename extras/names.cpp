#include<iostream>
#include<chrono>
using namespace std;

int main() {

    // Variables, duh
    string firstName, firstNames, lastName, lastNames;
    int times;

    cout << "Please enter your first name: ";
    cin >> firstName;

    cout << "Please enter your last name: ";
    cin >> lastName;

    cout << "How many times should we run?" << endl;
    cin >> times;

    // Start the first timer
    auto start1 = std::chrono::high_resolution_clock::now();

    /* 
     *  We're doing two loops here, one for the first name and one for the last name.  To keep the test even, 
     *  we're going to add the names to the concatenated strings and then print later so we can compare times,
     *  because printing to the console is expensive in terms of time.  Also note that we don't need to use
     *  curly braces here because we're only doing one thing in each loop.
     */
    for (int i = 0; i < times; i++)
        firstNames += firstName + "\n";

    for (int i = 0; i < times; i++)
        lastNames += lastName + "\n";

    // Printing a million rows would be silly
    if (times < 20) {
        cout << firstNames;
        cout << lastNames;
    }

    // Stop the first timer and calculate the first duration
    auto end1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);

    // Reset the board, so to speak
    firstNames = "";
    lastNames = "";

    // Start the second timer
    auto start2 = std::chrono::high_resolution_clock::now();

    /* 
     * Now let's do the same thing again, but instead of running a loop for each and "printing to the console," 
     * we'll add the names to both strings so we can do it all in a single loop
    */
    for (int i = 0; i < times; i++) {
        firstNames += firstName + "\n";
        lastNames += lastName + "\n";
    }

    if (times < 20) {
        cout << firstNames;
        cout << lastNames;
    }

    auto end2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);

    cout << "Time taken by first method: " << duration1.count() << " microseconds" << endl;
    cout << "Time taken by second method: " << duration2.count() << " microseconds" << endl;

    return 0;
}