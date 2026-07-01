# Simple Backtesting Engine (C++17)

Replays historical prices, generates buy/sell signals from a pluggable trading
strategy, executes simulated trades on a virtual portfolio, and prints a
performance summary. No real trades are placed.

## Build & run

```sh
make            # builds ./backtest
make run        # runs against data/prices.csv
```

Or directly:

```sh
./backtest [prices.csv] [startingCash] [sharesPerTrade]
# defaults: data/prices.csv  10000  1
```

## Example output

```
========== Backtest Summary ==========
Strategy     : Mean Reversion
Initial Cash : $10000.00
Final Cash   : $10005.00
Shares Owned : 0
Trades:
  Day 3   BUY  1 @ $97.00
  Day 5   SELL 1 @ $102.00
Total Profit : +$5.00
Return       : 0.05%
======================================
```

## Architecture

Each class has a single responsibility (separation of concerns):

| Component      | Responsibility                                            |
| -------------- | --------------------------------------------------------- |
| `MarketData`   | Load historical prices from CSV into `std::vector<double>`|
| `Strategy`     | Abstract decision interface (`generateSignal`)            |
| `MeanReversion`| Example strategy: buy on >2% dip, sell on >3% rise        |
| `Portfolio`    | Cash, holdings, order execution, trade history            |
| `Backtester`   | Drives the loop; contains **no** trading logic            |

Data flow: `MarketData → Backtester → (Strategy → Portfolio) → Report`.

## CSV format

One price per line. Either a single column of prices, or `day,price` rows
(the last numeric field is used). A non-numeric header row is skipped:

```
day,price
1,100
2,99
3,97
```

## Adding a strategy

Subclass `Strategy`, implement `generateSignal(const MarketContext&)` and
`name()`, then construct the `Backtester` with it. The engine needs no changes
(Strategy pattern). `MarketContext` gives you the current/previous price and
whether a position is open and at what price.

## Extensibility

The design leaves room for: multiple assets, transaction costs, position
sizing, stop-loss / take-profit, and richer metrics (Sharpe, drawdown).
