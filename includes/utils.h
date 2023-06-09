#pragma once

struct Point2d
{
	Point2d() {}
	Point2d(int n_x, int n_y) : x(n_x), y(n_y) {}

	int x = 0, y = 0;
};

enum class Directions : int
{
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3
};