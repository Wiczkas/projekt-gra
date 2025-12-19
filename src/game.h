#ifndef GAME_H
#define GAME_H

#include "snake.h"

enum Difficulty { EASY, MEDIUM, HARD };

class Game {
private:
    static const int WIDTH = 40;
    static const int HEIGHT = 20;

    Snake snake;
    Point food;
    int score;
    bool gameOver;

    Difficulty difficulty;
    int speedMs;

    void initCurses();
    void shutdownCurses();

    void generateFood();
    void render();
    void handleInput();

public:
    explicit Game(Difficulty diff = MEDIUM);
    void run();
    int getScore() const { return score; }
};

#endif

