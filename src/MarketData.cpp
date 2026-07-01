#include "MarketData.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

void MarketData::loadFromCsv(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("MarketData: could not open file: " + path);
    }

    prices_.clear();

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        // Take the last comma-separated field so both "price" and
        // "day,price" layouts work.
        std::string field;
        std::stringstream ls(line);
        std::string cell;
        while (std::getline(ls, cell, ',')) {
            field = cell;
        }

        // Parse the field; skip anything non-numeric (e.g. a header row).
        try {
            std::size_t consumed = 0;
            double price = std::stod(field, &consumed);
            if (consumed == 0) continue;
            prices_.push_back(price);
        } catch (const std::exception&) {
            // Not a number (header/garbage) — skip this line.
            continue;
        }
    }
}
