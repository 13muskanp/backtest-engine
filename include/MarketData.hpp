#pragma once

#include <string>
#include <vector>

// Loads and stores historical prices, keeping market data separate from
// trading logic. Provides sequential/random access over a contiguous vector.
class MarketData {
public:
    // Load one price per line from a CSV file.
    // Accepts either a single column of prices or "day,price" rows
    // (the last numeric field on each line is used as the price).
    // Blank lines and a leading non-numeric header row are skipped.
    // Throws std::runtime_error if the file cannot be opened.
    void loadFromCsv(const std::string& path);

    const std::vector<double>& prices() const { return prices_; }
    std::size_t size() const { return prices_.size(); }
    bool empty() const { return prices_.empty(); }
    double operator[](std::size_t i) const { return prices_[i]; }

private:
    std::vector<double> prices_;
};
