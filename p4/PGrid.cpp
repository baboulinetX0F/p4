#include "PGrid.h"


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

    SDL_Rect contourRect = m_pos;
    contourRect.x -= 3;
    contourRect.y -= 3;
    contourRect.w += 6;
    contourRect.h += 6;

	// Affichage fond de la grille	
	
	if (m_gameManager->GetGameState() == 2)
		renderer->RenderFillRect(&contourRect, 0, 255, 0);
	else if (m_gameManager->GetGameState() == 1)
		renderer->RenderFillRect(&contourRect, 255, 0, 0);
	else
		renderer->RenderFillRect(&contourRect, 255, 255, 255);
   

    // Affichage les cases
    for (unsigned int i = 0; i < m_gridElements.size(); i++)
        m_gridElements.at(i).Draw(renderer);

    if (m_gameManager->GetGameState() > 0) {
        SDL_Rect textRect = m_pos;
        textRect.x = textRect.x + (textRect.w / 2);
        textRect.y = textRect.y + (textRect.h / 2);
        TTF_SizeText(renderer->GetDefaultFont(),"Victoire",&textRect.w, &textRect.h);
        textRect.x -= (textRect.w / 2);
        textRect.y -= (textRect.h / 2);

        if (m_gameManager->GetGameState() == 2)
        {
            renderer->RenderTexture(renderer->RenderText("Victoire", renderer->GetDefaultFont()), &textRect);
        }
        else if (m_gameManager->GetGameState() == 1)
        {
            renderer->RenderTexture(renderer->RenderText("Defaite", renderer->GetDefaultFont()), &textRect);
        }
    }
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

void PGrid::SetSize(int x, int y) { }

void PGrid::InitGrid()
{
    Element* elem;
    for (int y = 0; y < NUM_LINES; y++) {
        for (int x = 0; x < NUM_COL; x++) {
                    elem = new Element(this);
                    elem->SetGridPos(x,y);
                    elem->SetSize(CASE_SIZE_DEFAULT, CASE_SIZE_DEFAULT);
                    m_gridElements.push_back(*elem);
        }
    }
    UIElement::SetSize(NUM_COL * CASE_SIZE_DEFAULT, NUM_LINES * CASE_SIZE_DEFAULT);
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
        m_gameManager->Jouer(COUL_JOUEUR,e->GetGridX());
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

void PGrid::Element::OnClick()
{
    m_parentGrid->OnGridElemClicked(this);
}

void PGrid::Element::Draw(Renderer * renderer)
{        
        SetPos(m_parentGrid->GetX() + (m_gridX * CASE_SIZE_DEFAULT), ((NUM_LINES-1) - m_gridY) * CASE_SIZE_DEFAULT + m_parentGrid->GetY());
        switch(m_state)
        {
            case EMPTY:
                if (isHovered())
                    m_buttonTexture = renderer->LoadTexture("textures/grid_elem_empty_highlighted.bmp");
                else if (m_parentGrid->IsColumnHovered(m_gridX))
                    m_buttonTexture = renderer->LoadTexture("textures/grid_elem_empty_hovered.bmp");
                else
                    m_buttonTexture = renderer->LoadTexture("textures/grid_elem_empty.bmp");
                renderer->RenderTexture(m_buttonTexture, &m_pos);
            break;
            case YELLOW:
                if (isHovered())
                    m_buttonTexture = renderer->LoadTexture("textures/grid_elem_yellow_highlighted.bmp");
                else if (m_parentGrid->IsColumnHovered(m_gridX))
                    m_buttonTexture = renderer->LoadTexture("textures/grid_elem_yellow_hovered.bmp");
                else
                    m_buttonTexture = renderer->LoadTexture("textures/grid_elem_yellow.bmp");
                renderer->RenderTexture(m_buttonTexture, &m_pos);
            break;
            case RED:
                if (isHovered())
                    m_buttonTexture = renderer->LoadTexture("textures/grid_elem_red_highlighted.bmp");
                else if (m_parentGrid->IsColumnHovered(m_gridX))
                    m_buttonTexture = renderer->LoadTexture("textures/grid_elem_red_hovered.bmp");
                else
                    m_buttonTexture = renderer->LoadTexture("textures/grid_elem_red.bmp");
                renderer->RenderTexture(m_buttonTexture, &m_pos);
            break;
        }
}

bool PGrid::IsColumnHovered(int column)
{
    for(unsigned int i = 0; i < m_gridElements.size(); i++)
    {
        if (m_gridElements.at(i).GetGridX() == column && m_gridElements.at(i).isHovered())
            return true;
    }
    return false;
}
