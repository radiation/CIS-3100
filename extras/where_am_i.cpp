#include <iostream>
#include <filesystem>
using namespace std;

int main() {
    // Get the current working directory
    filesystem::path currentPath = filesystem::current_path();

    // Output the current working directory
    cout << "Current Path: " << currentPath << endl;

    return 0;
}
