#include <thread>
#include "../includes/game.h"

using namespace std::chrono_literals;

// Window init
void Game::init()
{
	// Create Screen Buffer
	m_Screen = new wchar_t[m_Wall.dimensions.x * m_Wall.dimensions.y];
	for (int i = 0; i < m_Wall.dimensions.x * m_Wall.dimensions.y; i++) m_Screen[i] = L' ';
	m_ConsoleHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(m_ConsoleHandle);
}

// Game loop
void Game::run()
{
	// Show initial menu
	showMenu();

	// Wait for the input
	bool keyPressed = false;
	while (!keyPressed) keyPressed = (0x8000 & GetAsyncKeyState((unsigned char)('\x20')));

	while (1)
	{

		while (!m_Snake.isDead())
		{
			// Frame Timing, compensate for aspect ratio of command line
			auto t1 = std::chrono::system_clock::now();
			while ((std::chrono::system_clock::now() - t1) < ((static_cast<int>(m_Snake.SnakeDirection) % 2 == 1) ? 120ms : 200ms))
			{
				// Get Input 
				m_KeyRight = (0x8000 & GetAsyncKeyState((unsigned char)('\x44'))) != 0;
				m_KeyLeft = (0x8000 & GetAsyncKeyState((unsigned char)('\x41'))) != 0;
				m_KeyUp = (0x8000 & GetAsyncKeyState((unsigned char)('\x57'))) != 0;
				m_KeyDown = (0x8000 & GetAsyncKeyState((unsigned char)('\x53'))) != 0;

				if (m_KeyRight)
				{
					m_Snake.SnakeDirection = Directions::RIGHT;
				}
				else if (m_KeyLeft)
				{
					m_Snake.SnakeDirection = Directions::LEFT;
				}
				else if (m_KeyUp)
				{
					m_Snake.SnakeDirection = Directions::UP;
				}
				else if (m_KeyDown)
				{
					m_Snake.SnakeDirection = Directions::DOWN;
				}
			}

			// Update Snake position
			m_Snake.move();

			// Collision Detect Snake V Food
			if (m_Snake.onCollision(m_Food))
			{
				m_Score++;
				while (m_Screen[m_Food.position.y * m_Wall.dimensions.x + m_Food.position.x] != L' ')
				{
					m_Food.position.x = rand() % m_Wall.dimensions.x;
					m_Food.position.y = (rand() % (m_Wall.dimensions.y - 3)) + 3;
				}
			}

			// Collision Detect Snake V World & Snake V Self
			m_GameOver = m_Snake.onCollision(m_Wall) || m_Snake.onCollision(m_Snake);

			draw();
		}

		// Wait for decision
		bool bReplay = false, bQuit = false;
		while (!bReplay && !bQuit)
		{
			bReplay = (0x8000 & GetAsyncKeyState((unsigned char)('\x20')));
			bQuit = (0x8000 & GetAsyncKeyState((unsigned char)('\x0D')));
		}

		if (bReplay) m_Snake = Snake();
		if (bQuit) break;
	}
}

// Drawing loop
void Game::draw()
{
    // Clear Screen
	for (int i = 0; i < m_Wall.dimensions.x * m_Wall.dimensions.y; i++) m_Screen[i] = L' ';

	// Draw Stats & Border
	for (int i = 0; i < m_Wall.dimensions.x; i++)
	{
		m_Screen[i] = L'=';
		m_Screen[2 * m_Wall.dimensions.x + i] = L'=';
	}
	wsprintf(&m_Screen[m_Wall.dimensions.x + 5], L"        SCORE: %d", m_Score);


	// Draw Snake Body
	for (auto s : m_Snake.getBody())
		m_Screen[s.y * m_Wall.dimensions.x + s.x] = m_GameOver ? L'+' : L'O';

	// Draw Snake Head
	m_Screen[m_Snake.getBody().front().y * m_Wall.dimensions.x + m_Snake.getBody().front().x] = m_GameOver ? L'X' : L'@';

	// Draw Food
	m_Screen[m_Food.position.y * m_Wall.dimensions.x + m_Food.position.x] = L'%';

	if (m_GameOver)
	{
		wsprintf(&m_Screen[15 * m_Wall.dimensions.x + 40], L"    REPLAY -- 'SPACE'  \  QUIT -- 'ENTER'    ");
	}

	// Display Frame
	WriteConsoleOutputCharacter(m_ConsoleHandle, m_Screen, m_Wall.dimensions.x * m_Wall.dimensions.y, { 0,0 }, &m_BytesWritten);
}

// Initial menu
void Game::showMenu()
{
	// Clear Screen
	for (int i = 0; i < m_Wall.dimensions.x * m_Wall.dimensions.y; i++) m_Screen[i] = L' ';

	wsprintf(&m_Screen[15 * m_Wall.dimensions.x + 40], L"    CLASSIC CONSOLE SNAKE GAME");
	wsprintf(&m_Screen[18 * m_Wall.dimensions.x + 40], L"    CONTROLS:");
	wsprintf(&m_Screen[19 * m_Wall.dimensions.x + 40], L"    UP    --- W");
	wsprintf(&m_Screen[20 * m_Wall.dimensions.x + 40], L"    DOWN  --- S");
	wsprintf(&m_Screen[21 * m_Wall.dimensions.x + 40], L"    RIGHT --- D");
	wsprintf(&m_Screen[22 * m_Wall.dimensions.x + 40], L"    LEFT  --- A");
	wsprintf(&m_Screen[25 * m_Wall.dimensions.x + 40], L"    PRESS 'SPACE' TO START");

	// Display Frame
	WriteConsoleOutputCharacter(m_ConsoleHandle, m_Screen, m_Wall.dimensions.x * m_Wall.dimensions.y, { 0,0 }, &m_BytesWritten);
}