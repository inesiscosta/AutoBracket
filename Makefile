# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -O3 -Wall -lm

.PHONY: all test run clean format remove-tests

# Compile the program
TARGET = main.out
SRCS = mergeAttempt.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Run tests
test: $(TARGET)
	@for input in $(wildcard tests/*_input.txt); do \
		output=$${input%_input.txt}_output.txt; \
		result=$${input%_input.txt}_result.txt; \
		./$(TARGET) < $$input > $$result; \
		if diff -q $$result $$output > /dev/null; then \
			echo "Test $${input##*/} passed"; \
		else \
			echo "Test $${input##*/} failed"; \
			diff $$result $$output; \
		fi; \
	done; \
	$(MAKE) clean

# Run the program and wait for input from stdin
run: $(TARGET)
	@./$(TARGET)
	@$(MAKE) clean

# Clean up generated files
clean:
	@rm -f $(TARGET)

# Remove test result files
remove-tests:
	@rm -f tests/*_result.txt

format:
	clang-format -i $(SRCS)