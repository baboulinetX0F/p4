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
	m_textUpdated = false;
}

void Button::Draw(Renderer* renderer)
{	
	if (!m_customTexture)
	{
		// TODO : Ajout cas OnClicked
		if (isHovered)
			renderer->RenderFillRect(&m_pos,
				BUTTON_COLOR_HOVERED_DEFAULT.r, BUTTON_COLOR_HOVERED_DEFAULT.g, BUTTON_COLOR_HOVERED_DEFAULT.b);
		else
			renderer->RenderFillRect(&m_pos, BUTTON_COLOR_DEFAULT.r, BUTTON_COLOR_DEFAULT.g, BUTTON_COLOR_DEFAULT.b);
	}
	else
	{
		if (isClicked)
			renderer->RenderTexture(m_buttonClickedTexture, &m_pos);
		else if (isHovered)
			renderer->RenderTexture(m_buttonHoveredTexture, &m_pos);
		else
			renderer->RenderTexture(m_buttonTexture, &m_pos);
	}

	// Text Rendering	
    if (m_text.length() > 0) {
		
		if (!m_textUpdated)
			UpdateTextRender(renderer);
			
        if (m_textTexture != nullptr)
            renderer->RenderTexture(m_textTexture, &m_textRect);
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

void Button::UpdateTextRender(Renderer * renderer)
{
	m_textTexture = renderer->RenderText(m_text, renderer->GetDefaultFont());	
	m_textRect = m_pos;
	m_textRect.w -= 20;
	m_textRect.x += 10;
	int textW, textH;
	TTF_SizeText(renderer->GetDefaultFont(), m_text.c_str(), &textW, &textH);
	float ratio = static_cast<float>(m_textRect.w) / static_cast<float>(textW);
	m_textRect.h = static_cast<int>(textH * ratio);
	m_textRect.y += (m_pos.h - m_textRect.h) / 2;
	m_textUpdated = true;
}
