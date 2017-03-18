#pragma once

#include "Renderer.h"

class UIElement
{
public:
	UIElement();
	~UIElement();

	void SetPos(int x, int y);
	void SetSize(int w, int h);
    void SetZOrder(int z);
    void SetVisible(bool visibility);

	int GetX();
	int GetY();
	int GetW();
	int GetH();

    bool isVisible();

	virtual void Draw(Renderer* renderer) = 0;
	virtual void HandleEvents(SDL_Event e) = 0;

protected:
	SDL_Rect m_pos;
    int m_zOrder = 0;

    bool m_visibility = true;
};

