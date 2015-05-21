#include "GameInfoBar.hpp"

GameInfoBar::GameInfoBar(const GUI &gui, sf::RenderWindow &App)
  : GraphicsEngine(App),
    m_App(App), 
    m_GameInfo(gui.GetGameInfo()), 
    m_EventList(gui.GetEventList()), 
    m_TabPressed(gui.GetTabPressed()),
    m_SpacePressed(gui.GetSpacePressed()),
    m_BackPressed(gui.GetBackPressed()),
    m_Terminal(App, gui.GetEventList()), 
    m_PlayerInfo(App),
    m_NbTeam(m_GameInfo.GetTeams().GetNbTeam())
{
  m_ImageInfoBar.LoadFromFile("img/InfoBar.png");
  m_SpriteInfoBar.SetImage(m_ImageInfoBar);
  m_SpriteInfoBar.SetPosition(0, 618);
  std::ostringstream oss;
  
  oss << m_GameInfo.GetMap().GetSizeMap().x << ", " << m_GameInfo.GetMap().GetSizeMap().y;
  m_SizeMap = oss.str();
  m_PlayerIndent = 0;
  m_itTeam = m_GameInfo.GetTeams().GetTeams().begin();
  m_Mode = -1;
  m_ViewInfo = new ViewInfo(gui, App);
  m_Selected = 0;
}

const int &GameInfoBar::GetPlayerSelected() const
{
  return m_Selected;
}

void	GameInfoBar::EventHandler()
{
  m_Mode = -1 ;
  if (m_App.GetInput().IsKeyDown(sf::Key::F1))
      m_Mode = 0;
  if (m_App.GetInput().IsKeyDown(sf::Key::F2))
      m_Mode = 1;
  if (m_App.GetInput().IsKeyDown(sf::Key::F3))
      m_Mode = 2;
  if (m_App.GetInput().IsKeyDown(sf::Key::LControl))
    m_Mode = 3;
  if ( m_NbTeam  > 1 && m_TabPressed == true )
    {
      m_PlayerIndent = 0;
      ++m_itTeam;
      if (m_itTeam == m_GameInfo.GetTeams().GetTeams().end())
	m_itTeam = m_GameInfo.GetTeams().GetTeams().begin();
    }
  if (m_itTeam->second.first.size() > 1 && m_SpacePressed == true)
    {
      ++m_PlayerIndent;
      if ( m_PlayerIndent == m_itTeam->second.first.size())
	m_PlayerIndent = 0;
    }
}
void	GameInfoBar::Display()
{
  m_App.Draw(m_SpriteInfoBar);
  DrawText(std::string("Size Map : [ ") + m_SizeMap + " ]", sf::Color(255, 255, 255), 10.f, 10.f, 10.f );
  DrawText(std::string("Press Ctrl to View Command Information"), sf::Color(255, 255, 255), 780.f, 10.f, 12.f );
  m_Terminal.Display();
  m_PlayerInfo.Display();
  if (m_Mode != -1)
    {
      m_ViewInfo->Display(m_Mode, m_itTeam);
    }
}


void	GameInfoBar::Refresh()
{
  EventHandler();
  m_Terminal.Refresh();
  if (m_itTeam->second.first.size() > 0)
    {
      /*      std::cout << "Nom de la Team courante : " << m_itTeam->first << std::endl;
      std::cout << "Player indent : " << m_PlayerIndent << std::endl;
      std::cout << "Nombre de player in Vector :" << m_itTeam->second.first.size() << std::endl;
      std::cout << "Player id before set : " << m_itTeam->second.first[m_PlayerIndent].GetId() << std::endl;
      */
      m_Selected = m_itTeam->second.first[m_PlayerIndent].GetId();
      m_PlayerInfo.SetPlayer(m_itTeam->second.first[m_PlayerIndent]);
    }
  m_ViewInfo->Refresh();  
}
