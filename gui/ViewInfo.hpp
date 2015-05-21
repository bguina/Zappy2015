#ifndef _VIEW_INFO
#define _VIEW_INFO

#include <vector>
#include "GUI.hpp"
#include <SFML/Graphics.hpp>
#include "GraphicsEngine.hpp"
#include "Player.hpp"
#include "Team.hpp"

class GUI;

class		ViewInfo : public GraphicsEngine
{
public:
  ViewInfo(const GUI &gui, sf::RenderWindow &);
  void		Display(int Mode,const std::map<std::string, std::pair < std::vector<Player>,std::vector<Egg> > >::const_iterator &Team);
  void		Refresh();
  void		DisplayMode0();
  void		DisplayMode1(const std::map<std::string, std::pair < std::vector<Player>,std::vector<Egg> > >::const_iterator & Team );
  void		DisplayMode2();
  void		DisplayMode3();
private:
  sf::RenderWindow              &m_App;
  const GameInfo                &m_GameInfo;
  std::map<std::string,   std::pair < std::vector<Player>,std::vector<Egg> > >::const_iterator m_itTeam;
  int				m_mode;
  std::vector<sf::Image>		m_ImagesMode;
  std::vector<sf::Sprite>		m_SpritesMode;
  const Player				*m_Player;
  std::string				m_Lvl;
};

#endif
