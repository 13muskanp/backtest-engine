#pragma once

#include "Signal.hpp"

// A snapshot of the market state handed to a Strategy each day.
// The strategy decides purely from this context, so the Backtester never
// needs to know *how* a decision is made.
struct MarketContext {
    int day;               // 1-indexed current day
    double currentPrice;   // today's price
    double previousPrice;  // yesterday's price (== currentPrice on day 1)
    bool hasPosition;      // true if shares are currently held
    double purchasePrice;  // price the held shares were bought at (valid if hasPosition)
};

// Abstract decision-making interface. New strategies subclass this without
// requiring any change to the Backtester (Strategy pattern).
class Strategy {
public:
    virtual ~Strategy() = default;
    virtual Signal generateSignal(const MarketContext& ctx) = 0;
    virtual const char* name() const = 0;
};
