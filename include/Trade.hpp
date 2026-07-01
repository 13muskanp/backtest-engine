#pragma once

#include <string>

// One completed transaction, appended to the portfolio's trade history.
struct Trade {
    int day;            // 1-indexed day the trade happened
    double price;       // execution price per share
    int shares;         // number of shares transacted
    std::string type;   // "BUY" or "SELL"
};
