CFLAGS = -std=c++11 -O3 -Wall -lm
.PHONY: clean format

main: clean main.cpp
	g++ $(CFLAGS) main.cpp -o main.out

clean:
	rm -f *.o main.out

run: main
	./main.out
	$(MAKE) clean

format:
  clang-format -i main.cpp