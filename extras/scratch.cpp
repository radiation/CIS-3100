#include <iostream>
using namespace std;


class Base {
    public:
        Base() { cout << "Base constructor"; }
};

class Derived : public Base {
    public:
        Derived() { cout << "Derived constructor"; }
};

int main() {
    Derived d;

    return 0;
}