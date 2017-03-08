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

    while (!m_quit)
    {
        PollEvents();
        m_renderer->Clear();
        m_manager->Update();
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
    }
}
