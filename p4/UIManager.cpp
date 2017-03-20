#include "UIManager.h"

UIManager UIManager::m_instance = UIManager();

UIManager::UIManager()
{
}


UIManager::~UIManager()
{
}

UIManager & UIManager::Instance()
{
	return m_instance;
}

void UIManager::HandleEvents(SDL_Event event)
{
	for (unsigned int i = 0; i < m_elements.size(); i++)
		m_elements.at(i)->HandleEvents(event);
}

void UIManager::AddElement(UIElement * element)
{
	m_elements.push_back(element);
}

void UIManager::Draw(Renderer * renderer)
{
	for (unsigned int i = 0; i < m_elements.size(); i++)
		m_elements.at(i)->Draw(renderer);
}
