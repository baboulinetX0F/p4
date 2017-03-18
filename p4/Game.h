#pragma once

#include <vector>

#include "Renderer.h"
#include "GameManager.h"
#include "Button.h"
#include "Image.h"
#include "PGridElem.h"

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
	std::vector<UIElement*> m_ui;

    bool m_quit = false;
    void PollEvents();

    void UISetup();
};

