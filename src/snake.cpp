#include "../includes/snake.h"

// Update Snake position, place a new head at the front of the list in
// the right direction
void Snake::move()
{
	switch (SnakeDirection)
	{
	case Directions::UP:
		m_Body.push_front({ m_Body.front().x, m_Body.front().y - 1 });
		break;
	case Directions::RIGHT:
		m_Body.push_front({ m_Body.front().x + 1, m_Body.front().y });
		break;
	case Directions::DOWN:
		m_Body.push_front({ m_Body.front().x, m_Body.front().y + 1 });
		break;
	case Directions::LEFT:
		m_Body.push_front({ m_Body.front().x - 1, m_Body.front().y });
		break;
	}

	// Chop off Snakes tail
	m_Body.pop_back();
}

void Snake::setState(bool state)
{
	m_Dead = state;
}

bool Snake::isDead() const
{
	return m_Dead;
}

// Collision with itself -> death
bool Snake::onCollision(const Snake& snake)
{
	for (std::list<Point2d>::const_iterator i = m_Body.begin(); i != m_Body.end(); i++)
		if (i != m_Body.begin() && i->x == m_Body.front().x && i->y == m_Body.front().y)
			m_Dead = true;

	return m_Dead;
}

// Collision with wall (vertical / horizontal bounds overrun) -> death
bool Snake::onCollision(const Wall& wall)
{
	bool collision = false;

	if (m_Body.front().x < 0 || m_Body.front().x >= wall.dimensions.x)
		m_Dead = collision = true;
	if (m_Body.front().y < 3 || m_Body.front().y >= wall.dimensions.y)
		m_Dead = collision = true;

	return collision;
}

// Collision with food -> add a node to the body
bool Snake::onCollision(const Food& food)
{
	bool collision = m_Body.front().x == food.position.x && m_Body.front().y == food.position.y;
	if (collision)
	{
		for (int i = 0; i < 5; i++)
			m_Body.push_back({ m_Body.back().x, m_Body.back().y });
	}

	return collision;
}

const std::list<Point2d>& Snake::getBody() const
{
	return m_Body;
}