#pragma once

#include <string>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

const unsigned int DEFAULT_WINDOW_WIDTH = 1280;
const unsigned int DEFAULT_WINDOW_HEIGHT = 720;
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
	void RenderFillRect(SDL_Rect* rect, Uint8 r, Uint8 g, Uint8 b);

	TTF_Font* GetDefaultFont() const;


private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	std::map<std::string, SDL_Texture*> m_textureAtlas;

    // Default Assets
	TTF_Font* m_defaultFont;
    SDL_Texture* m_defaultTex;    

	/* Initialise le sous-systeme video de SDL */
	void InitSDL();
	void InitDefaultAssets();

	/* Cree la fenetre principale avec les dimensions passés en paramètres */
	void CreateWindow(unsigned int width, unsigned int height);
};

