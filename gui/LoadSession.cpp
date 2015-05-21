# include "LoadSession.hpp"
# include "GameSession.hpp"

LoadSession::LoadSession(sf::RenderWindow &App, bool&Map, bool&Content, bool&Team, bool &Player, bool& Iparam) :
  GraphicsEngine(App),
  m_App(App),
  m_MapSizeParam(Map),
  m_ContentMapParam(Content),
  m_TeamParam(Team),
  m_NewPlayerParam(Player),
  m_IndispensableParam(Iparam)
{
  // TODO nc all param / default then IA
}

Session*	LoadSession::update(const GUI &gui)
{
  if  (m_IndispensableParam == true)
    {
      return (new GameSession(gui, m_App));
    }  
return this;
}

std::string LoadSession::bool_as_text(bool b)
{
  std::stringstream converter;
  converter << b;
  return converter.str();
}

void		LoadSession::draw(const GUI & gui)
{  
      DrawText(std::string("Enter all Indispensable param to begin"), sf::Color(255, 255, 255), 200.f, 200.f, 30.f );
      DrawText(std::string("Map size Param ") +  bool_as_text(m_MapSizeParam) , sf::Color(255, 255, 255), 200.f, 250.f, 20.f );
      DrawText(std::string("Content Param ") +   bool_as_text(m_ContentMapParam), sf::Color(255, 255, 255), 200.f, 300.f, 20.f );
      DrawText(std::string("Team Param ") +   bool_as_text(m_TeamParam), sf::Color(255, 255, 255), 200.f, 350.f, 20.f );
      DrawText(std::string("Player Param ") +   bool_as_text(m_NewPlayerParam), sf::Color(255, 255, 255), 200.f, 400.f, 20.f );
      //    }
  (void)gui;
}

LoadSession::~LoadSession()
{
}
