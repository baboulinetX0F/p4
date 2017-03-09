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

int UIElement::GetX()
{
	return m_pos.x;
}

int UIElement::GetY()
{
	return m_pos.y;
}

int UIElement::GetW()
{
	return m_pos.w;
}

int UIElement::GetH()
{
	return m_pos.h;
}

