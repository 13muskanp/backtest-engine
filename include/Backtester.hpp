#pragma once

#include "MarketData.hpp"
#include "Portfolio.hpp"
#include "Strategy.hpp"

// Coordinates the simulation. It iterates over prices, asks the Strategy for a
// signal, and executes trades through the Portfolio. It contains no trading
// logic of its own.
class Backtester {
public:
    Backtester(const MarketData& data, Strategy& strategy, Portfolio& portfolio,
               int sharesPerTrade = 1)
        : data_(data), strategy_(strategy), portfolio_(portfolio),
          sharesPerTrade_(sharesPerTrade) {}

    // Replay the full price series, executing simulated trades.
    void run();

    // Print the final performance summary to stdout.
    void report() const;

private:
    const MarketData& data_;
    Strategy& strategy_;
    Portfolio& portfolio_;
    int sharesPerTrade_;
};
