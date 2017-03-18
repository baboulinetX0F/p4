#pragma once

#include <string>

#include "UIElement.h"

static const int DEFAULT_BUTTON_TEXT_MARGIN = 10;
static const char* DEFAULT_TEXT_BUTTON = "Default Text";

class Button : public UIElement
{
public:
	Button();
	~Button();

	void SetText(std::string newText);
    virtual void Draw(Renderer* renderer);

    virtual void HandleEvents(SDL_Event e);

private:
    bool isHovered = false;
    bool isClicked = false;

    std::string m_text = DEFAULT_TEXT_BUTTON;

    SDL_Texture* m_buttonTexture = nullptr;
    SDL_Texture* m_buttonHoveredTexture = nullptr;
    SDL_Texture* m_buttonClickedTexture = nullptr;

    SDL_Texture* m_textTexture = nullptr;
};

