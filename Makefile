CXX      := c++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -Iinclude
BIN      := backtest
SRC      := $(wildcard src/*.cpp)
OBJ      := $(SRC:.cpp=.o)

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(BIN)
	./$(BIN) data/prices.csv

clean:
	rm -f $(OBJ) $(BIN)

.PHONY: all run clean
