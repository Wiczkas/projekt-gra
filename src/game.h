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

    void generateFood();
    void render();
    void handleInput();

public:
    Game();
    void run();
};

#endif
