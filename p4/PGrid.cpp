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

void PGrid::InitGrid()
{
	Element elem = Element(this);
	elem.SetPos(GetX(), GetY());
	elem.SetSize(50, 50);
	m_gridElements.push_back(elem);
}

PGrid::Element::Element(PGrid * grid)
{
	m_parentGrid = grid;
}

PGrid::Element::~Element()
{
}
