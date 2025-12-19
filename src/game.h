#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include <vector>

enum Difficulty { EASY, MEDIUM, HARD };

class Game {
private:
    static const int WIDTH = 40;
    static const int HEIGHT = 20;

    Snake snake;
    Point food;
    std::vector<Point> obstacles;

    int score;
    bool gameOver;
    Difficulty difficulty;
    int speedMs;

    void initCurses();
    void shutdownCurses();

    void generateFood();
    void generateObstacles();
    bool hitsObstacle(const Point& p) const;

    void render();
    void handleInput();

public:
    explicit Game(Difficulty diff = MEDIUM);
    void run();
};

#endif
