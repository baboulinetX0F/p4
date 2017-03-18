#pragma once

#include <string>

#include "UIElement.h"

class Image : public UIElement
{
public:
    Image(std::string filePath);
	~Image();

	void Draw(Renderer* renderer);

	void HandleEvents(SDL_Event e);

private:
    std::string m_imagePath;

    SDL_Texture* m_imageTexture = nullptr;
};
