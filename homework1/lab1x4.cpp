#include<iostream>
using namespace std;

int numbers[4];

int main() {
    int num_shares;
    double purchase_price, current_price;
    cout << "Enter the number of shares: \n";
    cin >> num_shares;
    cout << "Enter the purchase price: \n";
    cin >> purchase_price;
    cout << "Enter the current price: \n";
    cin >> current_price;
    double profit = (current_price - purchase_price) * num_shares;
    cout << "The profit is " << profit << endl;
    cout << "You have made a profit of $" << profit << " dollars since you bought " << num_shares << " shares of this stock.\n";
}