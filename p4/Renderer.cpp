#include "Renderer.h"

#include <iostream>


Renderer::Renderer()
{
	InitSDL();	
	CreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
	InitDefaultAssets();
}


Renderer::~Renderer()
{
	// On detruit la fenetre si il en existe une
	if (m_window != nullptr)
		SDL_DestroyWindow( m_window );
	
	// On quitte SDL
	SDL_Quit();
}

void Renderer::Clear()
{
	SDL_SetRenderDrawColor(m_renderer, CLEAR_COLOR_DEFAULT.r, CLEAR_COLOR_DEFAULT.g, CLEAR_COLOR_DEFAULT.b, 255);
	SDL_RenderClear(m_renderer);
}

void Renderer::Render()
{	
    SDL_RenderPresent(m_renderer);
}

void Renderer::InitSDL()
{
	// On initialise le subsysteme video de SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
	}
    if (TTF_Init() < 0)
        std::cout << "SDL_TTF could not initialize! SDL_Error: " << TTF_GetError() << std::endl;
	
}

void Renderer::InitDefaultAssets()
{
	// On charge la police par default
    m_defaultFont = TTF_OpenFont("fonts/Roboto.ttf", 72);
	if (m_defaultFont == nullptr)
		std::cout << "ERROR : Cannot load default font (Roboto.ttf) " << TTF_GetError() << std::endl;

    m_defaultTex = LoadTexture("textures/placeholder.bmp");
    if (m_defaultTex == nullptr)
        std::cout << "ERROR : Cannot load default texture (placeholder.bmp)\n";
}

void Renderer::CreateWindow(unsigned int width, unsigned int height)
{
	m_window = SDL_CreateWindow("Puissance 4", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (m_window == NULL) {
		std::cout << "SDL could not create window SDL_Error: " << SDL_GetError() << std::endl;
	}
	else {
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	}
}

// TODO : Ajouter chargement d'autres formats d'images (voir SDL_Image)
SDL_Texture* Renderer::LoadTexture(std::string filePath)
{
    SDL_Texture* outputTex = nullptr;
    SDL_Surface* tmpSurface = nullptr;
	    
    if (m_textureAtlas.count(filePath) == 0) {
        tmpSurface = SDL_LoadBMP(filePath.c_str());
        if (tmpSurface == nullptr) {
            std::cout << "ERROR : Cannot load Image " << filePath << "SDL_Error : " << SDL_GetError() << std::endl;
        }
        else {
            m_textureAtlas[filePath] = SDL_CreateTextureFromSurface(this->m_renderer, tmpSurface);
            if (outputTex == nullptr) {
               std::cout << "ERROR : Cannot convert Surface into Texture SDL_Error :" << filePath << std::endl;
            }
            else {
                SDL_FreeSurface(tmpSurface);
                tmpSurface = nullptr;
            }
        }
    }

    outputTex = m_textureAtlas[filePath];

    if (outputTex == nullptr && m_defaultTex != nullptr)
        return m_defaultTex;
    else
        return outputTex;
}

void Renderer::RenderTexture(SDL_Texture* tex, SDL_Rect* destRect)
{    
    SDL_Texture* texture;
    if (tex == nullptr && m_defaultTex != nullptr)
        texture = m_defaultTex;
    else
        texture = tex;

    if (SDL_RenderCopy(m_renderer,texture,NULL,destRect) < 0) {
        std::cout << "ERROR : Cannot Render Texture SDL_Error: " << SDL_GetError() << std::endl;
        return;
   }
}

void Renderer::RenderFillRect(SDL_Rect * rect, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetRenderDrawColor(m_renderer, r, g, b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(m_renderer, rect);
}

TTF_Font * Renderer::GetDefaultFont() const
{
	return m_defaultFont;
}

SDL_Texture* Renderer::RenderText(std::string text, TTF_Font* font)
{
    if(font == nullptr){
        std::cout << "ERROR : Font used to RenderText is null\n";
        return nullptr;
    }
    else
    {
        SDL_Texture* outputTex = nullptr;
        SDL_Surface* tmpSurface;
        tmpSurface = TTF_RenderText_Blended(font, text.c_str(), FONT_COLOR_DEFAULT);
        if (tmpSurface == nullptr)
            std::cout << "ERROR : Can't RenderText into Surface SDL_Error : " << SDL_GetError() << std::endl;
        else
        {
            outputTex = SDL_CreateTextureFromSurface(this->m_renderer, tmpSurface);
            if (outputTex == nullptr)
                std::cout << "ERROR : Cannot convert Surface into Texture SDL_Error :" << SDL_GetError() << std::endl;
            else {
                SDL_FreeSurface(tmpSurface);
                tmpSurface = nullptr;
            }
        }
        return outputTex;
    }
}
