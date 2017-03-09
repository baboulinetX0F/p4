#include "Game.h"

#include <iostream>



Game::Game()
{
	m_renderer = new Renderer();
	m_manager = new GameManager();
}


Game::~Game()
{
}

void Game::GameLoop()
{	
	Button button = Button();
	button.SetPos(15, 15);
	button.SetSize(230, 60);
	m_ui.push_back(&button);

	while (!m_quit)
    {
        PollEvents();
        m_renderer->Clear();
        m_manager->Update();
		button.Draw(m_renderer);
        m_renderer->Render();
    }
}

// TODO : Peut etre bouger dans une classe input
void Game::PollEvents()
{
    SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
			m_quit = true;
		else
		{
			for (unsigned int i = 0; i < m_ui.size(); i++)
				m_ui.at(i)->HandleEvents(e);
		}
	}
}
