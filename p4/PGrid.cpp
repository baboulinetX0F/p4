#include "PGrid.h"

#include <iostream>

PGrid::PGrid(GameManager* gameManager)
{
        m_gameManager = gameManager;
        InitGrid();
}


PGrid::~PGrid()
{
}

void PGrid::Draw(Renderer * renderer)
{
        UpdateGrid();

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

        for (int y = 0; y < NUM_LINES; y++)
	{
                for (int x = 0; x < NUM_COL; x++)
		{
                    elem = new Element(this);
                    elem->SetGridPos(x,y);
                    elem->SetSize(CASE_DEFAULT_SIZE, CASE_DEFAULT_SIZE);
                    m_gridElements.push_back(*elem);
		}
	}
        UpdateGrid();
}

void PGrid::UpdateGrid()
{
    for(unsigned int i = 0; i<m_gridElements.size(); i++)
    {
        Element* currentElem = &m_gridElements.at(i);
        currentElem->SetState(m_gameManager->GetGridValAt(currentElem->GetGridX(),currentElem->GetGridY()));
    }
}

void PGrid::OnGridElemClicked(Element* e)
{
    if (e != nullptr && m_gameManager != nullptr && m_gameManager->m_playerTurn) {
        m_gameManager->PushPiece(YELLOW,e->GetGridX());
        m_gameManager->m_playerTurn = false;
        UpdateGrid();
    }
}

PGrid::Element::Element(PGrid * grid)
{
	m_parentGrid = grid;
}

PGrid::Element::~Element()
{
}

void PGrid::Element::SetState(CASE_STATE state)
{
    m_state = state;
}

void PGrid::Element::HandleEvents(SDL_Event e)
{
    Button::HandleEvents(e);

    if (isClicked){
        m_parentGrid->OnGridElemClicked(this);
    }
}

int PGrid::Element::GetGridX() const
{
    return m_gridX;
}

int PGrid::Element::GetGridY() const
{
    return m_gridY;
}

void PGrid::Element::SetGridPos(int x, int y)
{
	m_gridX = x;
	m_gridY = y;
}

void PGrid::Element::Draw(Renderer * renderer)
{        
        SetPos(m_parentGrid->GetX() + (m_gridX * CASE_DEFAULT_SIZE), ((NUM_LINES-1) - m_gridY) * CASE_DEFAULT_SIZE + m_parentGrid->GetY());
        switch(m_state)
        {
            case EMPTY:
                if (isHovered)
                    m_buttonTexture = renderer->LoadTexture("textures/grid_elem_empty_hovered.bmp");
                else
                    m_buttonTexture = renderer->LoadTexture("textures/grid_elem_empty.bmp");
                renderer->RenderTexture(m_buttonTexture, &m_pos);
            break;
            case YELLOW:
                if (isHovered)
                    m_buttonTexture = renderer->LoadTexture("textures/grid_elem_yellow_hovered.bmp");
                else
                    m_buttonTexture = renderer->LoadTexture("textures/grid_elem_yellow.bmp");
                renderer->RenderTexture(m_buttonTexture, &m_pos);
            break;
            case RED:
                if (isHovered)
                    m_buttonTexture = renderer->LoadTexture("textures/grid_elem_red_hovered.bmp");
                else
                    m_buttonTexture = renderer->LoadTexture("textures/grid_elem_red.bmp");
                renderer->RenderTexture(m_buttonTexture, &m_pos);
            break;
        }
}
