#include "UIElement.h"



UIElement::UIElement()
{
}


UIElement::~UIElement()
{
}

void UIElement::SetPos(int x, int y)
{
	m_pos.x = x;
	m_pos.y = y;
}

void UIElement::SetSize(int w, int h)
{
	m_pos.w = w;
	m_pos.h = h;
}

void UIElement::SetZOrder(int z)
{
    m_zOrder = z;
}

void UIElement::SetVisible(bool visibility)
{
    m_visibility = visibility;
}

int UIElement::GetX() const
{
	return m_pos.x;
}

int UIElement::GetY() const
{
	return m_pos.y;
}

int UIElement::GetW() const
{
	return m_pos.w;
}

int UIElement::GetH() const
{
	return m_pos.h;
}

bool UIElement::isVisible() const
{
    return m_visibility;
}

