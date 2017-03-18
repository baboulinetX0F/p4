#include "Image.h"

Image::Image(std::string filePath)
{
    m_imagePath = filePath;
}

Image::~Image()
{
}

void Image::Draw(Renderer* renderer)
{
    if (m_imageTexture == nullptr)
        m_imageTexture = renderer->LoadTexture(m_imagePath.c_str());

    if (m_imageTexture != nullptr)
        renderer->RenderTexture(m_imageTexture,&m_pos);
}

void Image::HandleEvents(SDL_Event e)
{
}
