#include<iostream>
using namespace std;

int main() {


    int i = 10;

    while (i-- > 0)
        if (i % 2 == 1)
            cout << i << endl;

    return 0;

}