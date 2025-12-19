#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <utility>

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

enum Direction { UP, DOWN, LEFT, RIGHT };

class Snake {
private:
    std::vector<Point> body;
    Direction dir;
    bool growing;

public:
    Snake(int startX, int startY);
    void move();
    void changeDirection(Direction newDir);
    void grow();
    bool checkCollision(int width, int height) const;
    bool checkSelfCollision() const;
    const std::vector<Point>& getBody() const { return body; }
    Point getHead() const { return body.front(); }
};

#endif
