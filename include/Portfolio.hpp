#pragma once

#include <vector>

#include "Trade.hpp"

// The simulated trading account: cash, holdings, and trade history.
// Owns all money/position bookkeeping so no other class touches balances.
class Portfolio {
public:
    explicit Portfolio(double startingCash)
        : initialCash_(startingCash), cash_(startingCash) {}

    // Buy `shares` at `price` on `day`. Returns false (no-op) if there is
    // not enough cash. Records the trade and remembers the purchase price.
    bool buy(int day, double price, int shares);

    // Sell every held share at `price` on `day`. Returns false if flat.
    bool sell(int day, double price);

    bool hasPosition() const { return sharesOwned_ > 0; }

    double cash() const { return cash_; }
    double initialCash() const { return initialCash_; }
    int sharesOwned() const { return sharesOwned_; }
    double purchasePrice() const { return purchasePrice_; }
    const std::vector<Trade>& trades() const { return trades_; }

    // Total account value if remaining shares were marked at `price`.
    double equity(double price) const { return cash_ + sharesOwned_ * price; }

private:
    double initialCash_;
    double cash_;
    int sharesOwned_ = 0;
    double purchasePrice_ = 0.0;  // price the current position was opened at
    std::vector<Trade> trades_;
};
