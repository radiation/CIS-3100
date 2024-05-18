#include <iostream>
#include <chrono>
#include <typeinfo>
#include <vector>
using namespace std;

class PrimeChecker {
    protected:
        vector<int> primes;
    public:
        PrimeChecker() {
            primes = {2, 3};
        }

        virtual bool is_prime(int n) {return false;}
};

class PrimeCheckerBad : public PrimeChecker {
    bool is_prime(int n) {
        for (int i = 2; i < n; i++) { // This just iterates through everything, which is very inefficient
            if (n % i == 0)
                return false;
        }
        return true;
    }
};

class PrimeCheckerGood : public PrimeChecker {
    bool is_prime(int n) {
        for (int i = 2; i < n/2+1; i++) { // Also standard iteration, but only up to n/2
            if (n % i == 0)
                return false;
        }
        return true;
    }
};

class PrimeCheckerBetter : public PrimeChecker {
    bool is_prime(int n) {
        if (n <= 3) return true;   // 2 and 3 are prime numbers

        if (n % 2 == 0 || n % 3 == 0) return false;  // Eliminate multiples of 2 and 3 early

        for (int i = 5; i * i <= n; i += 6)
            if (n % i == 0 || n % (i + 2) == 0) return false; // Check divisibility by i and i+2

        return true;
    }
};

class PrimeCheckerBest : public PrimeChecker {
    bool is_prime(int n) {
        if (n <= 3) return true;   // 2 and 3 are prime numbers

        if (n % 2 == 0 || n % 3 == 0) return false;  // Eliminate multiples of 2 and 3 early

        // Use previously known primes to check divisibility
        for (int p : primes) {
            if (p * p > n) break;  // No need to check beyond the square root of n
            if (n % p == 0) return false;
        }

        // If no known prime factors found, add to primes list if applicable
        primes.push_back(n);  // Assuming n is prime if it wasn't divisible by earlier primes
        return true;
    }
};

// Function prototypes
void iterate_primes(PrimeChecker& pc, int n);

// Globally scoped vector of primes so we don't have to pass it and can overload the is_prime function without an additional param
vector<int> primes = {2, 3};


int main() {

    int current = 2, counter = 0, sum = 0, max;

    cout << "Enter the number of prime numbers to sum: ";
    cin >> max;

    vector<PrimeChecker*> pcs = {new PrimeCheckerBad(), new PrimeCheckerGood(), new PrimeCheckerBetter(), new PrimeCheckerBest()};

    for (auto pc : pcs) {
        cout << "Using " << typeid(*pc).name() << endl;
        iterate_primes(*pc, max);
    }

    return 0;

}

void iterate_primes(PrimeChecker& pc, int n) {
    int current = 2, counter = 0, sum = 0;
    auto start = chrono::high_resolution_clock::now();

    while (counter < n) {
        if (pc.is_prime(current)) {
            sum += current;
            counter++;
        }
        current++;
    }
    cout << "Sum of the first " << n << " prime numbers: " << sum << endl;    

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "Execution time: " << duration.count() << " ms" << endl;
}