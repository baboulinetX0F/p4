#pragma once

#include <string>


#include "UIElement.h"


class Button : public UIElement
{
public:
	Button();
	~Button();

	void SetText(std::string newText);
	void Draw(Renderer* renderer);

	void HandleEvents(SDL_Event e);

private:
	std::string m_text;

	SDL_Texture* m_buttonTexture;
	SDL_Texture* m_textTexture;
};

