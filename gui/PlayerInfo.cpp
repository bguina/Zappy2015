#include "PlayerInfo.hpp"
#include "Player.hpp"
#include <sstream>

PlayerInfo::PlayerInfo(sf::RenderWindow &App) : GraphicsEngine(App), m_App(App) 
{
  m_resources.resize(7);
  
}


void	PlayerInfo::Display()
{
  // TODO Gerer si le perso meurt pendant sa selection

  DrawText(std::string("Inventory"), sf::Color(0, 0, 0), 590.f, 670.f, 10.f);
  // Inventaire
  DrawText(m_Lvl, sf::Color(255, 255, 255), 505.f, 640.f, 15.f);
  DrawText(m_resources[0], sf::Color(0, 0, 0), 670.f, 705.f, 10.f);
  DrawText(m_resources[1], sf::Color(0, 0, 0), 718.f, 705.f, 10.f);
  DrawText(m_resources[2], sf::Color(0, 0, 0), 765.f, 705.f, 10.f);
  DrawText(m_resources[3], sf::Color(0, 0, 0), 810.f, 705.f, 10.f);
  DrawText(m_resources[4], sf::Color(0, 0, 0), 860.f, 705.f, 10.f);
  DrawText(m_resources[5], sf::Color(0, 0, 0), 905.f, 705.f, 10.f);
  DrawText(m_resources[6], sf::Color(0, 0, 0), 955.f, 705.f, 10.f);
  DrawText(std::string("Player Id : [ ") + m_PlayerId + " ]", sf::Color(0, 0, 0), 650.f, 745.f, 12.f);
  DrawText(std::string("Team : [ ") + m_TeamName + " ]", sf::Color(0, 0, 0), 790.f, 745.f, 12.f); 
}

void	PlayerInfo::SetPlayer(const Player &p)
{
  std::ostringstream oss;

  m_Player = p;

  oss << m_Player.GetLvl();
  m_Lvl = oss.str();
  oss.str("");

  m_tab = m_Player.GetInventory();
  for(int i= 0; i < 7; ++i)
    {
      oss << m_tab[i];
      m_resources[i] = oss.str();
      oss.str("");
    }
  m_TeamName = p.GetTeamName();
  oss << m_Player.GetId();
  m_PlayerId = oss.str();
}

void	PlayerInfo::Refresh()
{

}
