#pragma once

// A trading decision produced by a Strategy for the current market state.
// Using an enum class keeps signals type-safe and readable.
enum class Signal {
    Buy,
    Sell,
    Hold
};
