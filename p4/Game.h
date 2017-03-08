#pragma once

#include "Renderer.h"
#include "GameManager.h"

class Game
{
public:
	Game();
	~Game();

	/* Boucle principale qui mets a jour la logique du jeu et l'affichage a chaque cycle CPU */
	void GameLoop();

private:
	Renderer* m_renderer;
	GameManager* m_manager;

    bool m_quit = false;
    void PollEvents();
};

