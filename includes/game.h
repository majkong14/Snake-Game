#pragma once

#include <iostream>
#include <windows.h>
#include "../includes/utils.h"
#include "../includes/snake.h"

class Game
{
public:
    Game() {}
    void init();
    void run();

private:
    void draw();
    void showMenu();

private:
    Snake m_Snake;
    Wall m_Wall;
    Food m_Food;

    int m_Score = 0;
    bool m_GameOver = 0;

    wchar_t* m_Screen = nullptr;
    HANDLE m_ConsoleHandle = nullptr;
    DWORD m_BytesWritten = 0;

    bool m_KeyLeft = false, m_KeyRight = false, m_KeyUp = false, m_KeyDown = false;
};