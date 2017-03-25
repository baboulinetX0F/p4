#pragma once

#include <string>

#include "UIElement.h"

static const char* BUTTON_TEXT_DEFAULT = "Default Text";
static const SDL_Color BUTTON_COLOR_DEFAULT = { 50, 151, 219 };
static const SDL_Color BUTTON_COLOR_HOVERED_DEFAULT = { 41, 127, 184 };

class Button : public UIElement
{
public:
	Button();
	~Button();

	void SetText(std::string newText);

    virtual void Draw(Renderer* renderer);
    virtual void HandleEvents(SDL_Event e);

protected:
    bool isHovered = false;
    bool isClicked = false;

    std::string m_text = BUTTON_TEXT_DEFAULT;  

	bool m_customTexture = false;
    SDL_Texture* m_buttonTexture = nullptr;
    SDL_Texture* m_buttonHoveredTexture = nullptr;
    SDL_Texture* m_buttonClickedTexture = nullptr;

    SDL_Texture* m_textTexture = nullptr;

private:
	SDL_Rect m_textRect;
	bool m_textUpdated = false;

	void UpdateTextRender(Renderer * renderer);
};

