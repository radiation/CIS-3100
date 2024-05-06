#include<iostream>
#include <iomanip> // For printing out the portfolio neatly
#include <algorithm> // For std::transform
#include <cctype>    // For std::toupper
#include <vector>
using namespace std;

/*
The assignment said to use a 2d array to keep track of this stuff, but a vector of objects is much easier to work with.
That way, we can dynamically keep track of the size of the portfolio and not have to worry about resizing the array,
we don't have to worry about converting data types when reading from the array, and we can validate the data types 
as part of object creation.  We can also easily add methods to the object to calculate the value and profit of the stock.
*/

class Stock {
    private:
        string ticker;
        int shares;
        double purchase_price, current_price;
    public:
        Stock(string t, int s, double pur, double cur) {
            setTicker(t); // reuse uppercase logic
            shares = s;
            purchase_price = pur;
            current_price = cur;
        }
        string getTicker() const { return ticker; }
        int getShares() const { return shares; }
        double getPurchasePrice() const { return purchase_price; }
        double getCurrentPrice() const { return current_price; }
        void setTicker(string t) {
            // convert ticker to uppercase
            transform(t.begin(), t.end(), t.begin(), ::toupper);
            ticker = t;
        }
        void setShares(int s) {
            shares = s;
        }
        void setPurchasePrice(double pur) {
            purchase_price = pur;
        }
        void setCurrentPrice(double cur) {
            current_price = cur;
        }
        double calculateValue() const {
            return shares * current_price;
        }
        double calculateProfit() const {
            return (current_price - purchase_price) * shares;
        }
};

// Method prototypes
void addStock(vector<Stock>& portfolio);
void removeStock(vector<Stock>& portfolio);
void displayPortfolio(vector<Stock>& portfolio);

// Main function
int main() {
    int size;
    cout << "Welcome to the portfolio manager!" << endl;
    cout << "How many stocks would you like to add to your portfolio?" << endl;
    cin >> size;

    // Define the variables we'll be using to keep track of the portfolio
    vector<Stock> portfolio;
    portfolio.reserve(size);

    for (int i=0; i<size; i++) {
        addStock(portfolio);
        cout << endl;
    }

    displayPortfolio(portfolio);

    return 0;
}

// Add a stock to the user's portfolio
void addStock(vector<Stock>& portfolio) {

    string ticker;
    int shares;
    double purchase_price, current_price;

    cout << "Please enter the follwing info..." << endl;

    cout << "Ticker: ";
    cin >> ticker;

    cout << "# Shares: ";
    cin >> shares;

    cout << "Purchase price: " << endl;
    cin >> purchase_price;

    cout << "Current price: " << endl;
    cin >> current_price;

    Stock new_stock(ticker, shares, purchase_price, current_price);
    portfolio.push_back(new_stock);
}

void removeStock(vector<Stock>& portfolio) {

    // Prompt for the ticker symbol
    string ticker;
    cout << "Please enter the ticker symbol of the stock you'd like to remove:" << endl;
    cin >> ticker;

    // Search for the stock in the portfolio and remove it if found
    for (int i=0; i<portfolio.size(); i++) {
        if (portfolio[i].getTicker() == ticker) {
            portfolio.erase(portfolio.begin() + i);
            cout << "Stock removed." << endl;
            return;
        }
    }

    cout << "Stock not found." << endl;
}

void displayPortfolio(vector<Stock>& portfolio) {
    double total_value = 0, total_profit = 0;

    cout << "Portfolio:" << endl;
    cout << left << setw(10) << "Ticker" 
         << right << setw(10) << "Shares" 
         << right << setw(10) << "Purchase" 
         << right << setw(10) << "Current" 
         << right << setw(10) << "Value" 
         << right << setw(10) << "Profit" 
         << endl;
    for (const Stock& stock : portfolio) {
        cout << left << setw(10) << stock.getTicker() 
             << right << setw(10) << stock.getShares() 
             << right << setw(10) << stock.getPurchasePrice() 
             << right << setw(10) << stock.getCurrentPrice() 
             << right << setw(10) << stock.calculateValue() 
             << right << setw(10) << stock.calculateProfit() 
             << endl;
        total_value += stock.calculateValue();
        total_profit += stock.calculateProfit();
    }

    cout << right << setw(50) << total_value << right << setw(10) << total_profit << endl;

}

