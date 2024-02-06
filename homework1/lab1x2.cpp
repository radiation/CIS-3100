#include<iostream>
using namespace std;

int numbers[4] = {578, 986, 1066, 714};

int main() {
    double sum = 0;
    for (int i = 0; i < 4; i++) {
        sum += numbers[i];
    }
    float average = sum / 4;
    cout << "The sum of the numbers is " << sum << endl;
    cout << "The average of the numbers is " << average << endl;
    return 0;
}