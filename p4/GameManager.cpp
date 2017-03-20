#include "GameManager.h"



GameManager::GameManager()
{
    InitGrid();
}


GameManager::~GameManager()
{
}

void GameManager::Update()
{
    if (!m_playerTurn) {
        PushPiece(RED,1);
        m_playerTurn = true;
    }
    CheckWin();
}

void GameManager::PushPiece(CASE_STATE color, int column)
{
	unsigned int colHeight = GetColHeight(column);

	if (colHeight < NUM_LINES)
	{
		m_grid[column][colHeight] = color;
	}
}

void GameManager::InitGrid()
{
	for (unsigned int x = 0; x < NUM_COL; x++)
	{
		for (unsigned int y = 0; y < NUM_LINES; y++)
		{
			m_grid[x][y] = CASE_STATE::EMPTY;
		}
	}
}

CASE_STATE GameManager::GetGridValAt(int x, int y)
{
    return m_grid[x][y];
}

unsigned int GameManager::GetColHeight(int column)
{
	unsigned int count = 0;
    for (unsigned int y = 0; y < NUM_LINES; y++)
	{
        if (m_grid[column][y] != CASE_STATE::EMPTY)
			count++;
	}
	return count;
}

void GameManager::CheckWin()
{
}
