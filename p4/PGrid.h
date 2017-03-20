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

	void SetPos(int x, int y);

private:
	class Element : public Button
	{
	public:
		Element(PGrid* grid);
		~Element();

		void SetGridPos(int x, int y);
		void Draw(Renderer* renderer);
	private:
		PGrid* m_parentGrid;
		int m_gridX, m_gridY;
	};

private:
	std::vector<Element> m_gridElements;

	void InitGrid();
};

