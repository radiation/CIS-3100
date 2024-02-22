#include<iostream>
using namespace std;

int main() {

    double base, height, area, totalArea = 0;
    int count = 0;

    for (char again = 'y'; again == 'y'; cin >> again) {
        cout << "Please enter the base of triangle #" << ++count << ": ";
        cin >> base;

        cout << "Please enter the height of triangle #" << count << ": ";
        cin >> height;

        area = (base * height) / 2;
        cout << "The area of triangle # " << count << " is " << area << ".\n";

        totalArea += area;

        cout << "Would you like to calculate another triangle? (y/n)";
    }

    cout << "You calculated " << count << " triangles, with an average area of " << totalArea/count << ".\n";

}