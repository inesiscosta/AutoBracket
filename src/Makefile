CXX = g++
CXXFLAGS = -std=c++11 -O3 -Wall -lm
SHELL := /bin/bash

.PHONY: all run test time clean rm format

TARGET = main
SRCS = main.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

run: $(TARGET)
	@./$(TARGET)
	@$(MAKE) -s clean

test: $(TARGET)
	@passed_tests=0; \
	total_tests=0; \
	for input in $(wildcard ../tests/*.in); do \
		total_tests=$$((total_tests + 1)); \
		output=$${input%.in}.out; \
		result=$${input%.in}.result; \
		diff_file=$${input%.in}.diff; \
		timeout 90 ./$(TARGET) < $$input > $$result; \
		if [ $$? -eq 124 ]; then \
			echo ""; \
			test_name=$$(basename $$input .in); \
			echo "Failed $$test_name: Time limit exceeded"; \
		elif diff -q $$result $$output > /dev/null; then \
			printf "."; \
			passed_tests=$$((passed_tests + 1)); \
		else \
			echo ""; \
			test_name=$$(basename $$input .in); \
			echo "Failed $$test_name: See file $$diff_file"; \
			diff $$result $$output | tee $$diff_file; \
		fi; \
	done; \
	echo ""; \
	echo "Tests passed $$passed_tests out of $$total_tests"; \
	$(MAKE) -s clean

time: $(TARGET)
	@for input in $(wildcard ../tests/*.in); do \
		test_name=$$(basename $$input .in); \
		echo "$$test_name: "; \
		{ time ./$(TARGET) < $$input > /dev/null; } 2>&1 | grep -E 'real|user|sys';\
	done
	@$(MAKE) -s clean

clean:
	@rm -f $(TARGET)

rm:
	@$(MAKE) -s clean
	@rm -f ../tests/*.result tests/*.diff
	@rm -f ../tests/test_generator

format:
	@clang-format -i $(SRCS)

new_test: ../tests/test_generator.cpp
	@$(CXX) $(CXXFLAGS) -o ../tests/test_generator ../tests/test_generator.cpp
	@../tests/test_generator $(ARGS)
	@$(MAKE) -s rm
