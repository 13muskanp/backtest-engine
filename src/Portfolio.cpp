#include "Portfolio.hpp"

bool Portfolio::buy(int day, double price, int shares) {
    if (shares <= 0) return false;

    double cost = price * shares;
    if (cost > cash_) {
        return false;  // not enough cash — reject the order
    }

    cash_ -= cost;
    sharesOwned_ += shares;
    purchasePrice_ = price;  // simple model: one open position at a time
    trades_.push_back(Trade{day, price, shares, "BUY"});
    return true;
}

bool Portfolio::sell(int day, double price) {
    if (sharesOwned_ <= 0) {
        return false;  // nothing to sell
    }

    int shares = sharesOwned_;
    cash_ += price * shares;
    sharesOwned_ = 0;
    purchasePrice_ = 0.0;
    trades_.push_back(Trade{day, price, shares, "SELL"});
    return true;
}
