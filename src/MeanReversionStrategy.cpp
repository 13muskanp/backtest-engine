#include "MeanReversionStrategy.hpp"

Signal MeanReversionStrategy::generateSignal(const MarketContext& ctx) {
    // While holding: sell once we're more than sellRisePct above our entry.
    if (ctx.hasPosition) {
        double rise = (ctx.currentPrice - ctx.purchasePrice) / ctx.purchasePrice;
        if (rise > sellRisePct_) {
            return Signal::Sell;
        }
        return Signal::Hold;
    }

    // While flat: buy after a drop of more than buyDropPct vs. yesterday.
    double drop = (ctx.previousPrice - ctx.currentPrice) / ctx.previousPrice;
    if (drop > buyDropPct_) {
        return Signal::Buy;
    }

    return Signal::Hold;
}
