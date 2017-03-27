#pragma once

#include <string>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

const unsigned int DEFAULT_WINDOW_WIDTH = 1280;
const unsigned int DEFAULT_WINDOW_HEIGHT = 720;
const SDL_Color FONT_COLOR_DEFAULT = { 255, 255, 255 };
const SDL_Color CLEAR_COLOR_DEFAULT = { 38, 38, 38 };


/* Renderer : Gère l'interface graphique et l'affichage de l'application */
class Renderer
{
public:
	Renderer();
	~Renderer();

	// Nettoie le buffer d'affichage (a utiliser a chaque debut de frame)
    void Clear();

	// Mets a jour l'affichage (a utiliser a chaque fin de frame)
	void Render();

	// Charge une texture en mémoire
    SDL_Texture* LoadTexture(std::string filePath);

	// Crée une texture texte a partir de la police et du texte donné 
    SDL_Texture* RenderText(std::string text, TTF_Font* font);

	// Affiche une texture a l'écran
    void RenderTexture(SDL_Texture* tex, SDL_Rect* destRect);

	// Affiche un rectangle rempli
	void RenderFillRect(SDL_Rect* rect, Uint8 r, Uint8 g, Uint8 b);

	// Retourne la police par defaut
	TTF_Font* GetDefaultFont() const;


private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	// Contient toutes les textures chargés en memoire
	std::map<std::string, SDL_Texture*> m_textureAtlas;

    // Default assets
	TTF_Font* m_defaultFont;
    SDL_Texture* m_defaultTex;    

	/* Initialise le sous-systeme video de SDL */
	void InitSDL();

	// Charge les assets par defaut
	void InitDefaultAssets();

	/* Cree la fenetre principale avec les dimensions passés en paramètres */
	void CreateWindow(unsigned int width, unsigned int height);
};

