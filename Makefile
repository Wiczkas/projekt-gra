CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -lncurses
TARGET = snake

OBJS = src/main.o src/game.o src/snake.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

src/main.o: src/main.cpp src/game.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o src/main.o

src/game.o: src/game.cpp src/game.h src/snake.h
	$(CXX) $(CXXFLAGS) -c src/game.cpp -o src/game.o

src/snake.o: src/snake.cpp src/snake.h
	$(CXX) $(CXXFLAGS) -c src/snake.cpp -o src/snake.o

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)
