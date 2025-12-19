#include "game.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <unistd.h>

Game::Game()
    : snake(WIDTH / 2, HEIGHT / 2), score(0), gameOver(false)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    generateFood();

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
}

void Game::generateFood() {
    do {
        food.x = std::rand() % WIDTH;
        food.y = std::rand() % HEIGHT;
    } while (std::find(snake.getBody().begin(),
                       snake.getBody().end(),
                       food) != snake.getBody().end());
}

void Game::render() {
    clear();

    for (int i = 0; i < WIDTH + 2; ++i) addch('#');
    addch('\n');

    for (int y = 0; y < HEIGHT; ++y) {
        addch('#');
        for (int x = 0; x < WIDTH; ++x) {
            Point p(x, y);
            if (p == snake.getHead())
                addch('O');
            else if (std::find(snake.getBody().begin(),
                               snake.getBody().end(),
                               p) != snake.getBody().end())
                addch('o');
            else if (p == food)
                addch('*');
            else
                addch(' ');
        }
        addch('#');
        addch('\n');
    }

    for (int i = 0; i < WIDTH + 2; ++i) addch('#');
    addch('\n');

    printw("Wynik: %d | WASD / strzalki | Q - wyjscie\n", score);
    refresh();
}

void Game::handleInput() {
    int ch = getch();
    switch (ch) {
        case 'w': case 'W': case KEY_UP:    snake.changeDirection(UP); break;
        case 's': case 'S': case KEY_DOWN:  snake.changeDirection(DOWN); break;
        case 'a': case 'A': case KEY_LEFT:  snake.changeDirection(LEFT); break;
        case 'd': case 'D': case KEY_RIGHT: snake.changeDirection(RIGHT); break;
        case 'q': case 'Q': gameOver = true; break;
        default: break;
    }
}

void Game::run() {
    while (!gameOver) {
        render();
        handleInput();
        snake.move();

        if (snake.getHead() == food) {
            snake.grow();
            score += 10;
            generateFood();
        }

        if (snake.checkCollision(WIDTH, HEIGHT) ||
            snake.checkSelfCollision()) {
            gameOver = true;
        }

        usleep(100000);
    }

    endwin();
    printf("\nGAME OVER\nWynik koncowy: %d\n", score);
}
