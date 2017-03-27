#include "Game.h"

#include <iostream>

Game::Game()
{
	m_renderer = new Renderer();
	m_manager = &GameManager::Instance();
}


Game::~Game()
{
}

void Game::GameLoop()
{
    UISetup();
    while (!m_quit)
    {
        PollEvents();
        m_renderer->Clear();
        m_manager->Update();

        for (unsigned int i = 0; i < m_ui.size(); i++)
            m_ui.at(i)->Draw(m_renderer);

        m_renderer->Render();
    }
}

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

void Game::UISetup()
{
    Button* button = new Button();
    button->SetPos(1280-180, 15);
    button->SetSize(180, 60);
	button->SetText("Restart");
	button->SetActionOnClick(&GameManager::Restart);
    m_ui.push_back(button); 
		
    PGrid* grid = new PGrid(m_manager);
	grid->SetPos(300,50);
	m_ui.push_back(grid);
}
