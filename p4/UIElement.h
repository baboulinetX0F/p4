#pragma once

#include "Renderer.h"

class UIElement
{
public:
	UIElement();
	~UIElement();

	void SetPos(int x, int y);
	void SetSize(int w, int h);

	int GetX();
	int GetY();
	int GetW();
	int GetH();

	virtual void Draw(Renderer* renderer) = 0;
	virtual void HandleEvents(SDL_Event e) = 0;

protected:
	SDL_Rect m_pos;

};

