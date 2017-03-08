#include "GameManager.h"



GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::Update()
{
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

unsigned int GameManager::GetColHeight(int column)
{
	unsigned int count = 0;
	for (unsigned int y = NUM_LINES; y >= 0; y--)
	{
		if (m_grid[y][column] != CASE_STATE::EMPTY)
			count++;
	}
	return count;
}

void GameManager::CheckWin()
{
}
