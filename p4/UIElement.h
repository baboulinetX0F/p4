#pragma once

#include "Renderer.h"
#include "GameManager.h"


// Classe Virtuelle servant de base a définir un objet de l'interface utilisateur
class UIElement
{
public:
	UIElement();
	~UIElement();

	void SetPos(int x, int y);
	void SetSize(int w, int h);
    void SetZOrder(int z);
    void SetVisible(bool visibility);

	int GetX() const;
	int GetY() const;
	int GetW() const;
	int GetH() const;

    bool isVisible() const;

	virtual void Draw(Renderer* renderer) = 0;
	virtual void HandleEvents(SDL_Event e) = 0;

protected:
	SDL_Rect m_pos;
    int m_zOrder = 0;

    bool m_visibility = true;
};

