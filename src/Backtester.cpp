#include "Backtester.hpp"

#include <iomanip>
#include <iostream>

void Backtester::run() {
    const auto& prices = data_.prices();

    for (std::size_t i = 0; i < prices.size(); ++i) {
        MarketContext ctx{};
        ctx.day = static_cast<int>(i) + 1;              // 1-indexed
        ctx.currentPrice = prices[i];
        ctx.previousPrice = (i == 0) ? prices[i] : prices[i - 1];
        ctx.hasPosition = portfolio_.hasPosition();
        ctx.purchasePrice = portfolio_.purchasePrice();

        switch (strategy_.generateSignal(ctx)) {
            case Signal::Buy:
                if (!portfolio_.hasPosition()) {
                    portfolio_.buy(ctx.day, ctx.currentPrice, sharesPerTrade_);
                }
                break;
            case Signal::Sell:
                if (portfolio_.hasPosition()) {
                    portfolio_.sell(ctx.day, ctx.currentPrice);
                }
                break;
            case Signal::Hold:
                break;
        }
    }
}

void Backtester::report() const {
    const auto& prices = data_.prices();
    double lastPrice = prices.empty() ? 0.0 : prices.back();

    double finalEquity = portfolio_.equity(lastPrice);
    double profit = finalEquity - portfolio_.initialCash();
    double returnPct = portfolio_.initialCash() > 0.0
                           ? (profit / portfolio_.initialCash()) * 100.0
                           : 0.0;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "========== Backtest Summary ==========\n";
    std::cout << "Strategy     : " << strategy_.name() << "\n";
    std::cout << "Initial Cash : $" << portfolio_.initialCash() << "\n";
    std::cout << "Final Cash   : $" << portfolio_.cash() << "\n";
    std::cout << "Shares Owned : " << portfolio_.sharesOwned() << "\n";

    std::cout << "Trades:\n";
    if (portfolio_.trades().empty()) {
        std::cout << "  (none)\n";
    } else {
        for (const Trade& t : portfolio_.trades()) {
            std::cout << "  Day " << std::setw(3) << std::left << t.day
                      << " " << std::setw(4) << t.type
                      << " " << t.shares << " @ $" << t.price << "\n";
        }
    }

    std::cout << (profit >= 0 ? "Total Profit : +$" : "Total Profit : -$")
              << std::abs(profit) << "\n";
    std::cout << "Return       : " << returnPct << "%\n";
    std::cout << "======================================\n";
}
