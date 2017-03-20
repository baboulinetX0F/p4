#pragma once

#include <vector>

#include "UIElement.h"

class UIManager
{
public:
	static UIManager& Instance();

	void HandleEvents(SDL_Event event);
	void AddElement(UIElement* element);
	void Draw(Renderer* renderer);

private:
	UIManager& operator= (const UIManager&) {}
	UIManager(const UIManager&) {}
	
	static UIManager m_instance;

	UIManager();
	~UIManager();
	
	std::vector<UIElement*> m_elements;
};

