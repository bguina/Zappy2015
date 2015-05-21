#ifndef _TEAM_INFO_BAR
#define _TEAM_INFO_BAR

#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include "GraphicsEngine.hpp"

class		TeamInfoBar : public GraphicsEngine
{
public:
  TeamInfoBar(sf::RenderWindow &App, std::string &,std::vector<Player> &p);
  void		Display();
  void		Refresh();
private:
  sf::RenderWindow		&m_App;
  std::vector<Player>		&m_Players;
  std::string			&m_TeamName;
  //  sf::String                    m_Text;
  //  sf::Font                      m_MyFont;
};

#endif
