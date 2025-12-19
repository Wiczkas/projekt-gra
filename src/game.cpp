#include "game.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <ncurses.h>

Game::Game(Difficulty diff)
    : snake(WIDTH / 2, HEIGHT / 2),
      score(0),
      gameOver(false),
      difficulty(diff) {

    switch (difficulty) {
        case EASY:   speedMs = 200; break;
        case MEDIUM: speedMs = 120; break;
        case HARD:   speedMs = 70;  break;
    }

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    generateObstacles();
    generateFood();
}

void Game::initCurses() {
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
}

void Game::shutdownCurses() {
    nodelay(stdscr, FALSE);
    echo();
    noraw();
    endwin();
}

void Game::generateObstacles() {
    obstacles.clear();

    for (int x = 10; x < 30; x++) {
        obstacles.push_back(Point(x, 8));
        obstacles.push_back(Point(x, 12));
    }
}

bool Game::hitsObstacle(const Point& p) const {
    return std::find(obstacles.begin(), obstacles.end(), p) != obstacles.end();
}

void Game::generateFood() {
    do {
        food.x = std::rand() % WIDTH;
        food.y = std::rand() % HEIGHT;
    } while (
        hitsObstacle(food) ||
        std::find(snake.getBody().begin(), snake.getBody().end(), food)
            != snake.getBody().end()
    );
}

void Game::render() {
    clear();

    for (int x = 0; x < WIDTH + 2; x++) mvaddch(0, x, '#');
    for (int y = 0; y < HEIGHT; y++) {
        mvaddch(y + 1, 0, '#');
        mvaddch(y + 1, WIDTH + 1, '#');

        for (int x = 0; x < WIDTH; x++) {
            Point p(x, y);

            if (p == snake.getHead()) mvaddch(y + 1, x + 1, 'O');
            else if (std::find(snake.getBody().begin(), snake.getBody().end(), p)
                     != snake.getBody().end())
                mvaddch(y + 1, x + 1, 'o');
            else if (p == food) mvaddch(y + 1, x + 1, '*');
            else if (hitsObstacle(p)) mvaddch(y + 1, x + 1, '#');
            else mvaddch(y + 1, x + 1, ' ');
        }
    }

    for (int x = 0; x < WIDTH + 2; x++) mvaddch(HEIGHT + 1, x, '#');

    mvprintw(HEIGHT + 3, 0,
             "Wynik: %d | WASD | Q-wyjscie | Przeszkody aktywne",
             score);

    refresh();
}

void Game::handleInput() {
    int ch;
    while ((ch = getch()) != ERR) {
        switch (ch) {
            case 'w': case 'W': snake.changeDirection(UP); break;
            case 's': case 'S': snake.changeDirection(DOWN); break;
            case 'a': case 'A': snake.changeDirection(LEFT); break;
            case 'd': case 'D': snake.changeDirection(RIGHT); break;
            case 'q': case 'Q': gameOver = true; break;
        }
    }
}

void Game::run() {
    initCurses();

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
            snake.checkSelfCollision() ||
            hitsObstacle(snake.getHead())) {
            gameOver = true;
        }

        usleep(speedMs * 1000);
    }

    shutdownCurses();
    printf("\n=== GAME OVER ===\nWynik: %d\n", score);
}
