#include <iostream>
using namespace std;

// function prototypes
void pointerBasics();
void pointerArithmetic();
void dynamicMemoryAllocation();
void smartPointers();

int main() {

    // Call the functions to demonstrate pointer basics, pointer arithmetic, dynamic memory allocation, and smart pointers
    cout << "Pointer Basics:" << endl;
    pointerBasics();
    cout << "\nPointer Arithmetic:" << endl;
    pointerArithmetic();
    cout << "\nDynamic Memory Allocation:" << endl;
    dynamicMemoryAllocation();
    cout << "\nSmart Pointers:" << endl;
    smartPointers();

    return 0;
}

void pointerBasics() {
    // Declare an integer, a pointer to an integer, and a pointer to a pointer to an integer
    int num = 10;
    int* ptr = &num;
    int** ptr_ptr = &ptr;

    // Print the value of the integer using both pointers
    cout << "Value of num using ptr: " << *ptr << endl;
    cout << "Value of num using ptr_ptr: " << **ptr_ptr << endl;

    // Explanation:
    // *ptr points to the value of num, which is 10.
    // **ptr_ptr points to the value of the pointer ptr, which in turn points to the value of num, also 10.
}

void pointerArithmetic() {
    // Create an array of five floating-point numbers
    float arr[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
    float* ptr = arr;

    // Use a pointer to traverse the array and increase each element by 1.0 using pointer arithmetic
    for (int i = 0; i < 5; i++) {
        *(ptr + i) += 1.0;
    }

    // Print the updated array using pointer arithmetic
    for (int i = 0; i < 5; i++) {
        cout << *(ptr + i) << " ";
    }
    cout << endl;
}

void dynamicMemoryAllocation() {
    // Dynamically allocate an array of 10 integers
    int* arr = new int[10];

    // Initialize the array with values (1 through 10) using a loop
    for (int i = 0; i < 10; i++) {
        *(arr + i) = i + 1;
    }

    // Calculate and print the sum of the array using a pointer
    int sum = 0;
    for (int i = 0; i < 10; i++) {
        sum += *(arr + i);
    }
    cout << "Sum of the array: " << sum << endl;

    // Properly deallocate the memory and set the pointer to nullptr
    delete[] arr;
    arr = nullptr;
}

void smartPointers() {
    // Rewrite the dynamic memory allocation task using std::unique_ptr
    std::unique_ptr<int[]> arr(new int[10]);

    // Initialize the array with values (1 through 10) using a loop
    for (int i = 0; i < 10; i++) {
        arr[i] = i + 1;
    }

    // Calculate and print the sum of the array using a pointer
    int sum = 0;
    for (int i = 0; i < 10; i++) {
        sum += arr[i];
    }
    cout << "Sum of the array: " << sum << endl;

    // No need to manually deallocate memory, as std::unique_ptr handles it automatically
    // No need to set the pointer to nullptr, as the smart pointer goes out of scope and cleans up
    // Advantages of using std::unique_ptr:
    // - Automatic memory management, preventing memory leaks
    // - Clear ownership semantics, ensuring proper resource management
    // - RAII (Resource Acquisition Is Initialization) guarantees proper cleanup
}