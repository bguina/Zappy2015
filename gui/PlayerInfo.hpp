#ifndef _PLAYERINFO
#define _PLAYERINFO
#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include "GraphicsEngine.hpp"


class		PlayerInfo : public GraphicsEngine
{
public:
  PlayerInfo(sf::RenderWindow &App);
  void		SetPlayer(const Player &p);
  void		Display();
  void		Refresh();
private:
  sf::RenderWindow		&m_App;
  Player			m_Player;
  std::string                    m_Lvl;
  std::string			 m_TeamName;
  std::string                    m_PlayerId;
  std::vector<std::string>      m_resources;
  std::vector<int>		m_tab;
  sf::Font                      m_MyFont;
};

#endif
