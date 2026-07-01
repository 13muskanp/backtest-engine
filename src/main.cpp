#include <iostream>
#include <string>

#include "Backtester.hpp"
#include "MarketData.hpp"
#include "MeanReversionStrategy.hpp"
#include "Portfolio.hpp"

int main(int argc, char** argv) {
    // Usage: backtest [prices.csv] [startingCash] [sharesPerTrade]
    std::string csvPath = (argc > 1) ? argv[1] : "data/prices.csv";
    double startingCash = (argc > 2) ? std::stod(argv[2]) : 10000.0;
    int sharesPerTrade = (argc > 3) ? std::stoi(argv[3]) : 1;

    MarketData data;
    try {
        data.loadFromCsv(csvPath);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    if (data.empty()) {
        std::cerr << "Error: no prices loaded from " << csvPath << "\n";
        return 1;
    }

    MeanReversionStrategy strategy;         // 2% buy dip / 3% sell rise
    Portfolio portfolio(startingCash);
    Backtester engine(data, strategy, portfolio, sharesPerTrade);

    engine.run();
    engine.report();
    return 0;
}
