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
    Image* img = new Image("textures/background.bmp");
    img->SetPos(0,0);
    img->SetSize(DEFAULT_WINDOW_WIDTH,DEFAULT_WINDOW_HEIGHT);
    m_ui.push_back(img);

    Button* button = new Button();
    button->SetPos(1280-115, 15);
    button->SetSize(115, 30);
    m_ui.push_back(button);

    PGridElem* elem = new PGridElem();
    elem->SetPos(30, 45);
    elem->SetSize(115, 30);
    m_ui.push_back(elem);
}
