CFLAGS = -std=c++11 -O3 -Wall -lm

main: main.cpp
	g++ $(CFLAGS) main.cpp -o main

clean:
	rm -f *.o main

run: clean main
	./main