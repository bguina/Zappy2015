#include "EndSession.hpp"

EndSession::EndSession(sf::RenderWindow &App,const std::string& Team) :
  GraphicsEngine(App),
  m_App(App),
  m_Winner(Team)
{
}

Session	*EndSession::update(const GUI &gui)
{
  (void)gui;
  return this;
}

void	EndSession::draw(const GUI& gui)
{
(void)gui;
  DrawText(std::string("The Winner is : Team ") + m_Winner, sf::Color(255, 255, 255), 200.f, 200.f, 12.f );
}

EndSession::~EndSession()
{
}
