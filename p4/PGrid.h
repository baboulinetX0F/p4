#pragma once
#include "Button.h"

#include <vector>

class PGrid : public UIElement
{
public:
	PGrid();
	~PGrid();

	void Draw(Renderer* renderer);
	void HandleEvents(SDL_Event e);

private:
	class Element : public Button
	{
	public:
		Element(PGrid* grid);
		~Element();
	private:
		PGrid* m_parentGrid;
	};

private:
	std::vector<Element> m_gridElements;

	void InitGrid();
};

