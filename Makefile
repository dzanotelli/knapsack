# Makefile for the knapsack problem

BIN_DIR=bin
TARGETS=all clean rebuild knapsack_0
DEBUG_FLAG="-ggdb"

usage:
	@echo "Available targets:" $(TARGETS) "\n(doing nothing)"

knapsack_0: bin_dir
	@echo "Building knapsack_0 ..."
	@gcc $(DEBUG_FLAG) knapsack_0.c -o $(BIN_DIR)/knapsack_0

bin_dir:
	@test -d $(BIN_DIR) || \
		(echo "Creating" $(BIN_DIR) "..."; \
		 mkdir $(BIN_DIR))

.PHONY: all clean rebuild
all: knapsack_0
clean:
	@echo "Cleaning all ..."
	@-rm -rf $(BIN_DIR)
rebuild: clean all
