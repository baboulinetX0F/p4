#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

const unsigned int DEFAULT_WINDOW_WIDTH = 800;
const unsigned int DEFAULT_WINDOW_HEIGHT = 600;
const SDL_Color DEFAULT_FONT_COLOR = { 255, 255, 255 };


/* Renderer : Gère l'interface graphique et l'affichage de l'application */
class Renderer
{
public:
	Renderer();
	~Renderer();

    void Clear();
	void Render();

    SDL_Texture* LoadTexture(std::string filePath);
    SDL_Texture* RenderText(std::string text, TTF_Font* font);
    void RenderTexture(SDL_Texture* tex, SDL_Rect* destRect);

	TTF_Font* GetDefaultFont();


private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	TTF_Font* m_defaultFont;

	/* Initialise le sous-systeme video de SDL */
	void InitSDL();
	void InitDefaultAssets();

	/* Cree la fenetre principale avec les dimensions passés en paramètres */
	void CreateWindow(unsigned int width, unsigned int height);
};

