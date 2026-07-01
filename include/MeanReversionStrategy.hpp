#pragma once

#include "Strategy.hpp"

// Mean Reversion:
//   * Buy  if today's price is more than `buyDropPct` below yesterday's
//          (and we are not already holding a position).
//   * Sell if the current price is more than `sellRisePct` above the price
//          the position was bought at.
//   * Otherwise Hold.
class MeanReversionStrategy : public Strategy {
public:
    explicit MeanReversionStrategy(double buyDropPct = 0.02, double sellRisePct = 0.03)
        : buyDropPct_(buyDropPct), sellRisePct_(sellRisePct) {}

    Signal generateSignal(const MarketContext& ctx) override;
    const char* name() const override { return "Mean Reversion"; }

private:
    double buyDropPct_;   // e.g. 0.02 == 2%
    double sellRisePct_;  // e.g. 0.03 == 3%
};
