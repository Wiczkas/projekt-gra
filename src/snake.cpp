#include "snake.h"
#include <cstddef>

Snake::Snake(int startX, int startY) : dir(RIGHT), growing(false) {
    body.push_back(Point(startX, startY));
    body.push_back(Point(startX - 1, startY));
    body.push_back(Point(startX - 2, startY));
}

void Snake::move() {
    Point newHead = body.front();

    switch (dir) {
        case UP:    newHead.y--; break;
        case DOWN:  newHead.y++; break;
        case LEFT:  newHead.x--; break;
        case RIGHT: newHead.x++; break;
    }

    body.insert(body.begin(), newHead);

    if (!growing) {
        body.pop_back();
    } else {
        growing = false;
    }
}

void Snake::changeDirection(Direction newDir) {
    // zapobiegaj ruchowi o 180 stopni
    if ((dir == UP && newDir == DOWN) ||
        (dir == DOWN && newDir == UP) ||
        (dir == LEFT && newDir == RIGHT) ||
        (dir == RIGHT && newDir == LEFT)) {
        return;
    }
    dir = newDir;
}

void Snake::grow() {
    growing = true;
}

bool Snake::checkCollision(int width, int height) const {
    Point head = body.front();
    return head.x < 0 || head.x >= width ||
           head.y < 0 || head.y >= height;
}

bool Snake::checkSelfCollision() const {
    Point head = body.front();
    for (std::size_t i = 1; i < body.size(); i++) {
        if (body[i] == head) return true;
    }
    return false;
}
