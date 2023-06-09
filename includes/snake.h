#pragma once

#include <list>
#include "../includes/utils.h"

struct Food
{
    Food() {}
    Food(int n_x, int n_y) : position(n_x, n_y) {}

    Point2d position{ 30, 15 };
};

struct Wall
{
    Wall() {}
    Point2d dimensions{ 120, 30 };
};

class Snake
{
public:
    Snake() {};
    void move();
    void setState(bool state);
    bool isDead() const;
    bool onCollision(const Snake& snake);
    bool onCollision(const Wall& world);
    bool onCollision(const Food& food);
    const std::list<Point2d>& getBody() const;

public:
    Directions SnakeDirection = Directions::LEFT;

private:
    bool m_Dead = false;
    std::list<Point2d> m_Body = { {60, 15}, { 61,15 }, { 62,15 }, { 63,15 }, { 64,15 }, { 65,15 }, { 66,15 }, { 67,15 }, { 68,15 }, { 69,15 } };
};

