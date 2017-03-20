#include "Button.h"

#include <iostream>

Button::Button()
{	
}


Button::~Button()
{
}

void Button::SetText(std::string newText)
{
	m_text = newText;
}

// TODO : Mettre le text a la bonne échelle
void Button::Draw(Renderer* renderer)
{		
	if (m_buttonTexture == nullptr)
        m_buttonTexture = renderer->LoadTexture("textures/buttonTex.bmp");

	if (m_textTexture == nullptr)
        m_textTexture = renderer->RenderText(m_text, renderer->GetDefaultFont());
	
    // TODO : Ajouter Rendu dans le cas onClicked
    if (isHovered)
        renderer->RenderTexture(m_buttonHoveredTexture,&m_pos);
    else
        renderer->RenderTexture(m_buttonTexture,&m_pos);

    if (m_text.length() > 0) {
        if (m_textTexture != nullptr)
            renderer->RenderTexture(m_textTexture, &m_pos);
    }
}

void Button::HandleEvents(SDL_Event e)
{
    if (isClicked)
        isClicked = false;

    // En cas d'event clic gauche
	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

        if (x >= GetX() && x <= (GetX() + GetW()) && y >= GetY() && y <= (GetY() + GetH())){
            std::cout << ("Button Clicked\n");
            isClicked = true;
        }
	}
    else if (e.type = SDL_MOUSEMOTION)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        if (x >= GetX() && x <= (GetX() + GetW()) && y >= GetY() && y <= (GetY() + GetH()))
        {
            if (!isHovered)
                isHovered = true;
        }
        else {
            if (isHovered)
                isHovered = false;
        }
    }
}
