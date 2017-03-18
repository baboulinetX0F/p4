#include "PGridElem.h"

PGridElem::PGridElem()
{
	
}

PGridElem::~PGridElem()
{
}

// TODO : Mettre le text a la bonne échelle
void PGridElem::Draw(Renderer* renderer)
{
	SetSize(50, 50);
	if (m_emptyTexture == nullptr)
		m_emptyTexture = renderer->LoadTexture("textures/grid_elem_empty.bmp");
	if (m_redTexture == nullptr)
		m_redTexture = renderer->LoadTexture("textures/grid_elem_yellow.bmp");
	if (m_yellowTexture == nullptr)
		m_yellowTexture = renderer->LoadTexture("textures/grid_elem_red.bmp");

	// TODO : Ajouter Rendu dans le cas onClicked
	if (isHovered)
		renderer->RenderTexture(m_buttonHoveredTexture, &m_pos);
	else
	{
		switch (m_state)
		{
		case EMPTY:
			renderer->RenderTexture(m_emptyTexture, &m_pos);
			break;
		case YELLOW:
			renderer->RenderTexture(m_yellowTexture, &m_pos);
			break;
		case RED:
			renderer->RenderTexture(m_redTexture, &m_pos);
			break;
		}
		
	}
}