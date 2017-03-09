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

void Button::Draw(Renderer* renderer)
{		
	if (m_buttonTexture == nullptr)
		m_buttonTexture = renderer->LoadTexture("textures/buttonTex.bmp");
	
	if (m_buttonTexture != nullptr)
		renderer->RenderTexture(m_buttonTexture,&m_pos);
}

void Button::HandleEvents(SDL_Event e)
{
	// En cas d'event clic gauche
	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		if (x >= GetX() && x <= (GetX() + GetW()) && y >= GetY() && y <= (GetY() + GetH()))
			std::cout << ("Button Clicked\n");
	}
}
