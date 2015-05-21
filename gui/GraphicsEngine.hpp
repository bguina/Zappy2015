#ifndef _GRAPHICS_ENGINE
#define _GRAPHICS_ENGINE
# include <SFML/Graphics.hpp>


class		GraphicsEngine
{
public:
  GraphicsEngine(sf::RenderWindow &App);
  void          DrawText(std::string const& text, sf::Color const& color, float x, float y, float size, sf::Font const& font = sf::Font::GetDefaultFont());
private:
  sf::RenderWindow              &m_App;
  sf::String                    m_Text;
  sf::Font                      m_MyFont;
};

#endif
