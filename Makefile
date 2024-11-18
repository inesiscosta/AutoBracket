CXX = g++
CXXFLAGS = -std=c++11 -O3 -Wall -lm -pg

.PHONY: all run test time clean rm format

TARGET = main
SRCS = main.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

run: $(TARGET)
	@./$(TARGET)
	@$(MAKE) clean

test: $(TARGET)
	@passed_tests=0; \
	total_tests=0; \
	for input in $(wildcard tests/*.in); do \
		((total_tests++)); \
		output=$${input%.in}.out; \
		result=$${input%.in}.result; \
		diff_file=$${input%.in}.diff; \
		./$(TARGET) < $$input > $$result; \
		if diff -q $$result $$output > /dev/null; then \
			printf "."; \
			((passed_tests++)); \
		else \
			echo ""; \
			test_name=$$(basename $$input .in); \
			echo "Failed $$test_name: See file $$diff_file"; \
			diff $$result $$output | tee $$diff_file; \
		fi; \
	done; \
	echo ""; \
	echo "Tests passed $$passed_tests out of $$total_tests"; \
	$(MAKE) clean

time: $(TARGET)
	@for input in $(wildcard tests/*.in); do \
		test_name=$$(basename $$input .in); \
		echo "$$test_name: "; \
		output=$${input%.in}.out; \
		{ time ./$(TARGET) < $$input > /dev/null; } 2>&1 | grep -E 'real|user|sys';\
	done

clean:
	@rm -f $(TARGET)

rm:
	@$(MAKE) clean
	@rm -f tests/*.result tests/*.diff

format:
	@clang-format -i $(SRCS)
