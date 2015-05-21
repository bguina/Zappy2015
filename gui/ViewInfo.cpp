#include "ViewInfo.hpp"
#include "GUI.hpp"
#include <SFML/Graphics.hpp>
#include "GraphicsEngine.hpp"
#include <sstream>
#include "Player.hpp"

ViewInfo::ViewInfo(const GUI &gui, sf::RenderWindow &App)
:
  GraphicsEngine(App),
  m_App(App),
  m_GameInfo(gui.GetGameInfo())
{
  m_itTeam = m_GameInfo.GetTeams().GetTeams().begin();
  m_ImagesMode.resize(4);
  m_SpritesMode.resize(4);
  for (int i = 0; i < 4; ++i)
    {
      std::stringstream ss;
      ss << "img/mode_" << i << ".png";
      m_ImagesMode[i].LoadFromFile(ss.str());
      m_SpritesMode[i].SetImage(m_ImagesMode[i]);
      m_SpritesMode[i].SetPosition( 200.f, 50.f);
      m_SpritesMode[i].SetColor(sf::Color(255, 255, 255, 200));
    }
  m_SpritesMode[3].SetPosition( 300.f, 50.f);
  m_mode = 0;
  m_Lvl = "";
}

void		ViewInfo::Display(int mode, const std::map<std::string,   std::pair < std::vector<Player>,std::vector<Egg> > >::const_iterator & Team)
{
  m_mode = mode;
  if (mode == 0)
    {
      DisplayMode0();
    }
  else if (mode == 1)
    {
      DisplayMode1(Team);
    }
  else if (mode == 2)
    {
      DisplayMode2();
    }
  else
    DisplayMode3();
}

void		ViewInfo::Refresh()
{
  
}


void		ViewInfo::DisplayMode0()
{
  int		i=0;
  std::ostringstream oss;
  
  m_App.Draw(m_SpritesMode[0]);
  DrawText("Teams", sf::Color(255, 255, 255), 505.f , 132.f , 13.f);
  DrawText("Players", sf::Color(255 ,255, 255), 380.f , 132.f , 13.f);
  DrawText("Top 10", sf::Color(0, 0 , 0), 260.f , 132.f , 13.f);
  DrawText("Team Name", sf::Color(0 ,0, 0), 380.f , 160.f , 13.f);
  DrawText("Id", sf::Color(0, 0, 0), 530.f , 160.f , 13.f);
  for (m_itTeam = m_GameInfo.GetTeams().GetTeams().begin(); m_itTeam != m_GameInfo.GetTeams().GetTeams().end(); ++m_itTeam )
    {
      if(i < 10)
	{
	  oss << i + 1;
	  m_Lvl = oss.str();
	  DrawText(m_itTeam->first, sf::Color(0, 0, 0), 300.f , 185.f + (i*25), 13.f);
	  DrawText(m_Lvl, sf::Color(0, 0, 0), 535.f , 185.f + (i*25), 13.f);
	  DrawText("XXXXXXXXX", sf::Color(0, 0, 0), 595.f , 185.f + (i*25), 13.f);
	  oss.str("");
	}
      ++i;
    }
}

void		ViewInfo::DisplayMode1(const std::map<std::string, std::pair < std::vector<Player>,std::vector<Egg> > >::const_iterator &Team)
{
  int		i=0;
  std::vector<Player>::const_iterator                         it2;
  std::ostringstream oss;

 
  
  m_App.Draw(m_SpritesMode[1]);
  DrawText("Teams", sf::Color(255, 255, 255), 505.f , 132.f , 13.f);
  DrawText("Players", sf::Color(0 ,0, 0), 380.f , 132.f , 13.f);
  DrawText("Top 10", sf::Color(255, 255, 255), 260.f , 132.f , 13.f);
  DrawText("Lvl", sf::Color(0, 0, 0), 478.f , 160.f , 13.f);
  DrawText("Id", sf::Color(0 ,0, 0), 380.f , 160.f , 13.f);
  DrawText("Coordinate", sf::Color(0, 0, 0), 530.f , 160.f , 13.f);
  for (it2 = Team->second.first.begin() ; it2 != Team->second.first.end(); ++it2)
    {
      DrawText(it2->GetTeamName(), sf::Color(0, 0, 0), 635.f , 92.f , 20.f);
      if(i < 10)
	{
	  oss << it2->GetId();
	  m_Lvl = oss.str();
	  DrawText(std::string("Player ") + m_Lvl, sf::Color(0, 0, 0), 340.f , 185.f + (i*25), 13.f);
	  oss.str("");
	  oss << it2->GetLvl();
	  m_Lvl = oss.str();
	  oss.str("");
	  DrawText(m_Lvl, sf::Color(0, 0, 0), 482.f , 185.f + (i*25), 13.f);
	  oss << it2->GetPosition().x << " ,  " << it2->GetPosition().y;
	  m_Lvl = oss.str();
	  oss.str("");	  
	  DrawText(std::string("[ ") + m_Lvl + " ]", sf::Color(0, 0, 0), 550.f , 185.f + (i*25), 13.f);
	}
      ++i;
    }
}

void		ViewInfo::DisplayMode2()
{
  //  int		i=0;
  m_App.Draw(m_SpritesMode[2]);
  DrawText("Teams", sf::Color(255, 255, 255), 505.f , 132.f , 13.f);
  DrawText("Players", sf::Color(255 ,255, 255), 380.f , 132.f , 13.f);
  DrawText("Top 10", sf::Color(0, 0, 0), 260.f , 132.f , 13.f);
  /*  DrawText("Lvl", sf::Color(0, 0, 0), 478.f , 160.f , 13.f);
  DrawText("Id", sf::Color(0 ,0, 0), 380.f , 160.f , 13.f);
  DrawText("Coordinate", sf::Color(0, 0, 0), 530.f , 160.f , 13.f);
  */
}


void		ViewInfo::DisplayMode3()
{
  m_App.Draw(m_SpritesMode[3]);
  DrawText("Player Information", sf::Color(255, 255, 255), 470.f , 100.f , 20.f);
  DrawText("Player Get resource", sf::Color(0, 0, 0), 410.f , 170.f , 11.f);
  DrawText("Player Drop resource", sf::Color(0, 0, 0), 410.f , 192.f , 11.f);
  DrawText("Player Fork", sf::Color(0, 0, 0), 410.f , 214.f , 11.f);
  DrawText("Player Incantation", sf::Color(0, 0, 0), 410.f , 236.f , 11.f);
  DrawText("Player Level up", sf::Color(0, 0, 0), 410.f , 258.f , 11.f);
  DrawText("Player is Born", sf::Color(0, 0, 0), 410.f , 280.f , 11.f);
  DrawText("Player is Dead", sf::Color(0, 0, 0), 410.f , 302.f , 11.f);
  DrawText("+/-     :    Press + or - to zoom/dezoom", sf::Color(0, 0, 0), 380.f , 390.f , 11.f);
  DrawText("F1      :    Press F1 to view All Team name ", sf::Color(0, 0, 0), 380.f , 412.f , 11.f);
  DrawText("F2      :    Press F2 to view All Player name in a team", sf::Color(0, 0, 0), 380.f , 434.f , 11.f);
  DrawText("TAB     :    Press TAB to change the current Team", sf::Color(0, 0, 0), 380.f , 456.f , 11.f);
  DrawText("SPACE :    Press SPACE to change the current Player", sf::Color(0, 0, 0), 380.f , 478.f , 11.f);
}
