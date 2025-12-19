#include "game.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <unistd.h>     // usleep
#include <ncurses.h>    // ncurses

Game::Game(Difficulty diff)
    : snake(WIDTH / 2, HEIGHT / 2),
      score(0),
      gameOver(false),
      difficulty(diff),
      speedMs(120) {

    switch (difficulty) {
        case EASY:   speedMs = 200; break;
        case MEDIUM: speedMs = 120; break;
        case HARD:   speedMs = 60;  break;
    }

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    generateFood();
}

void Game::initCurses() {
    initscr();
    raw();                 // stabilniejsze niż cbreak przy grach
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE); // getch() nie blokuje
    timeout(0);            // dodatkowo: natychmiastowy zwrot z getch()
    curs_set(0);           // ukryj kursor
}

void Game::shutdownCurses() {
    nodelay(stdscr, FALSE);
    echo();
    noraw();
    endwin();
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

    // górna ramka
    for (int x = 0; x < WIDTH + 2; x++) {
        mvaddch(0, x, '#');
    }

    // plansza
    for (int y = 0; y < HEIGHT; y++) {
        mvaddch(y + 1, 0, '#');
        mvaddch(y + 1, WIDTH + 1, '#');

        for (int x = 0; x < WIDTH; x++) {
            Point current(x, y);

            if (current == snake.getHead()) {
                mvaddch(y + 1, x + 1, 'O');
            } else if (std::find(snake.getBody().begin(),
                                 snake.getBody().end(),
                                 current) != snake.getBody().end()) {
                mvaddch(y + 1, x + 1, 'o');
            } else if (current == food) {
                mvaddch(y + 1, x + 1, '*');
            } else {
                mvaddch(y + 1, x + 1, ' ');
            }
        }
    }

    // dolna ramka
    for (int x = 0; x < WIDTH + 2; x++) {
        mvaddch(HEIGHT + 1, x, '#');
    }

    mvprintw(HEIGHT + 3, 0,
             "Wynik: %d | Sterowanie: WASD | Q - wyjscie | Poziom: %s",
             score,
             (difficulty == EASY ? "EASY" : (difficulty == MEDIUM ? "MEDIUM" : "HARD")));

    refresh();
}

void Game::handleInput() {
    // Czytamy WSZYSTKIE znaki z bufora w tej klatce
    // i reagujemy na ostatni sensowny klawisz.
    int ch;
    while ((ch = getch()) != ERR) {
        switch (ch) {
            case 'w': case 'W': snake.changeDirection(UP); break;
            case 's': case 'S': snake.changeDirection(DOWN); break;
            case 'a': case 'A': snake.changeDirection(LEFT); break;
            case 'd': case 'D': snake.changeDirection(RIGHT); break;
            case 'q': case 'Q': gameOver = true; break;
            default: break;
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

        if (snake.checkCollision(WIDTH, HEIGHT) || snake.checkSelfCollision()) {
            gameOver = true;
        }

        usleep(speedMs * 1000);
    }

    shutdownCurses();

    printf("\n=== GAME OVER ===\n");
    printf("Koncowy wynik: %d\n", score);
}
