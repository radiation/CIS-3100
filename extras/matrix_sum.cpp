#include <iostream>
using namespace std;

int main() {

    int grid[3][3] = {{2, 6, 1}, {8, 4, 9}, {1, 2, 3}};

    int sum = 0;

    // Loop through the grid and add the diagonal elements to the sum
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (i == j)
                sum += grid[i][j];

    cout << "The sum of the diagonal elements in the grid is " << sum << ".\n";

    // Loop through and the even numbers to the sum
    sum = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i][j] % 2 == 0)
                sum += grid[i][j];

    cout << "The sum of the even elements in the grid is " << sum << ".\n";

    // Set any 4s to 10
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i][j] == 4)
                grid[i][j] = 10;

    // Print the updated grid
    cout << "The updated grid is:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            cout << grid[i][j] << " ";
        cout << endl;
    }

    return 0;
}