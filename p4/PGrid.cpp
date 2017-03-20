#include "PGrid.h"



PGrid::PGrid()
{
	InitGrid();
}


PGrid::~PGrid()
{
}

void PGrid::Draw(Renderer * renderer)
{
	// Affichage fond de la grille
	renderer->RenderFillRect(&m_pos, 255, 0, 0);

	// Affichage les cases
	for (unsigned int i = 0; i < m_gridElements.size(); i++)
		m_gridElements.at(i).Draw(renderer);
}

void PGrid::HandleEvents(SDL_Event e)
{
	for (unsigned int i = 0; i < m_gridElements.size(); i++)
		m_gridElements.at(i).HandleEvents(e);
}

void PGrid::SetPos(int x, int y)
{
	m_pos.x = x;
	m_pos.y = y;
}

void PGrid::InitGrid()
{
	Element* elem; 

	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			elem = new Element(this);
			elem->SetGridPos(x,y);
			elem->SetSize(50, 50);
			m_gridElements.push_back(*elem);
		}
	}
}

PGrid::Element::Element(PGrid * grid)
{
	m_parentGrid = grid;
}

PGrid::Element::~Element()
{
}

void PGrid::Element::SetGridPos(int x, int y)
{
	m_gridX = x;
	m_gridY = y;
}

void PGrid::Element::Draw(Renderer * renderer)
{
	if (m_buttonTexture == nullptr)
		m_buttonTexture = renderer->LoadTexture("textures/grid_elem_empty_hovered.bmp");

	SetPos(m_parentGrid->GetX() + m_gridX * 50, m_parentGrid->GetY() + m_gridY * 50);
	if (isHovered)
		renderer->RenderTexture(m_buttonHoveredTexture, &m_pos);
	else
		renderer->RenderTexture(m_buttonTexture, &m_pos);
}
