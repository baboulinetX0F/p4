#include "Game.h"

#include <iostream>

Game::Game()
{
	m_renderer = new Renderer();
	m_manager = &GameManager::Instance();
}


Game::~Game()
{
	delete m_renderer;
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
	Button* restart = new Button();
	restart->SetPos(1280-180, 15);
	restart->SetSize(180, 60);
	restart->SetText("Restart");
	restart->SetActionOnClick(&GameManager::Restart);
	m_ui.push_back(restart);

	Button* Diff1 = new Button();
	Diff1->SetPos(1280 - 180, 90);
	Diff1->SetSize(180, 60);
	Diff1->SetText("Facile");
	Diff1->SetActionOnClick(&GameManager::DifficulteUn);
	m_ui.push_back(Diff1);

	Button* Diff2 = new Button();
	Diff2->SetPos(1280 - 180, 165);
	Diff2->SetSize(180, 60);
	Diff2->SetText("Moyen");
	Diff2->SetActionOnClick(&GameManager::DifficulteDeux);
	m_ui.push_back(Diff2);

	Button* Diff3 = new Button();
	Diff3->SetPos(1280 - 180, 240);
	Diff3->SetSize(180, 60);
	Diff3->SetText("Difficile");
	Diff3->SetActionOnClick(&GameManager::DifficulteTrois);
	m_ui.push_back(Diff3);

	Button* Diff4 = new Button();
	Diff4->SetPos(1280 - 180, 315);
	Diff4->SetSize(180, 60);
	Diff4->SetText("Hardcore");
	Diff4->SetActionOnClick(&GameManager::DifficulteQuatre);
	m_ui.push_back(Diff4);

	PGrid* grid = new PGrid(m_manager);
	grid->SetPos(300,50);
	m_ui.push_back(grid);
}
