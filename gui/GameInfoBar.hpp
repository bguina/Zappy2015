#ifndef GAME_INFOBAR
#define GAME_INFOBAR
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <set>
#include "GUI.hpp"
#include "Terminal.hpp"
#include "GameInfo.hpp"
#include "PlayerInfo.hpp"
#include "ViewInfo.hpp"
#include "GraphicsEngine.hpp"


class GUI;
class ViewInfo;

class		GameInfoBar : public GraphicsEngine
{
public:
  GameInfoBar(const GUI &gui, sf::RenderWindow &);
  void					Display();
  void					Refresh();
  void					EventHandler();
  const int&				GetPlayerSelected() const;
private:
  sf::RenderWindow			&m_App;
  const GameInfo			&m_GameInfo;
  const std::vector<std::string>	&m_EventList;
  std::map<std::string,   std::pair < std::vector<Player>,std::vector<Egg> > >::const_iterator m_itTeam;
  const	std::vector<Player>*		m_Pl;
  const bool&				m_TabPressed;
  const bool&				m_SpacePressed;
  const bool&				m_BackPressed;
  Terminal				m_Terminal;
  PlayerInfo				m_PlayerInfo;
  const int&				m_NbTeam;

  // non reference
  ViewInfo				*m_ViewInfo;
  int					m_TeamId;
  unsigned int				m_PlayerIndent;
  int					m_SizeTeam;
  sf::Sprite				m_SpriteInfoBar;
  sf::Image				m_ImageInfoBar;
  std::string				m_SizeMap;
  std::string				m_CurrentTeam;
  int					m_Mode;
  int					m_Selected;
};

#endif
