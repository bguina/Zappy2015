#include "GraphicsEngine.hpp"
#include <iostream>

GraphicsEngine::GraphicsEngine(sf::RenderWindow &App) : m_App(App)
{

}

void		GraphicsEngine::DrawText(std::string const& text, sf::Color const& color, float x, float y , float size, sf::Font const& MyFont)
{
  m_Text.SetText(text);
  m_Text.SetFont(MyFont);
  m_Text.SetColor(color);
  m_Text.SetPosition(x, y);
  m_Text.SetSize(size);
  m_App.Draw(m_Text);
}
