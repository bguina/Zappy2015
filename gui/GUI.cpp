#include "GUI.hpp"
#include <iostream>
#include "Session.hpp"
#include "GameSession.hpp"
#include "LoadSession.hpp"
#include "Map.hpp"
#include "Player.hpp"

int GUI::run(std::string const& host, int port=default_port)
{
    try
      {
        m_Connection.connect(host, port);
      }
    catch (ErrnoException& e)
      {
	std::cerr << "connection error: " << e.what() << ": " << std::strerror(e.errcode()) << 
	  std::endl;
        return -1;
      }
    initialize();
    while (m_App.IsOpened())
      {
	EventHandler();
	update();
	display();
      }
    unload();
   return 0;
}

void    GUI::initialize()
{
  m_RessourcesName.push_back(std::string("Food"));
  m_RessourcesName.push_back(std::string("LineMate"));
  m_RessourcesName.push_back(std::string("Deraumere"));
  m_RessourcesName.push_back(std::string("Sibur"));
  m_RessourcesName.push_back(std::string("Mendiane"));
  m_RessourcesName.push_back(std::string("Phiras"));
  m_RessourcesName.push_back(std::string("Thystame"));
  m_SpacePressed = false;
  m_TabPressed = false;  
  m_BackPressed = false;
  m_IndispensableParam = false;
  m_MapSizeParam = false;
  m_ContentMapParam = false;
  m_TeamParam = false;
  m_NewPlayerParam = false;
  m_EscapPressed = false;
  m_F1Pressed = false;
  m_F2Pressed = false;
  m_F3Pressed = false;
  m_EndOfGame = false;
  m_Bct = 0;
  m_oss.str("");
  for(int i=0; i < 6; ++i)
    {
      m_EventList.push_back(std::string(""));
    }
  m_App.Create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Zappy XD");
  m_App.SetFramerateLimit(60);
  m_Session = new LoadSession(m_App, m_MapSizeParam, m_ContentMapParam, m_TeamParam,m_NewPlayerParam, m_IndispensableParam);
}

void    GUI::EventHandler()
{
  sf::Event e;
  m_SpacePressed = false;
  m_TabPressed = false;  
  m_BackPressed = false;
  while (m_App.GetEvent(e))
    {
      if (e.Type == sf::Event::Closed)
        m_App.Close();
      if (e.Type == sf::Event::KeyReleased && e.Key.Code == sf::Key::Tab)
	  m_TabPressed = true;
      if (e.Type == sf::Event::KeyReleased && e.Key.Code == sf::Key::Space)
	m_SpacePressed = true;
      if (e.Type == sf::Event::KeyReleased && e.Key.Code == sf::Key::Back)
	m_BackPressed = true;
      if (e.Type == sf::Event::KeyReleased && e.Key.Code == sf::Key::F1)
	m_F1Pressed = false;
      if (e.Type == sf::Event::KeyReleased && e.Key.Code == sf::Key::F2)
	m_F2Pressed = false;
      if (e.Type == sf::Event::KeyReleased && e.Key.Code == sf::Key::F3)
	m_F3Pressed = false;      
    }
}

void	GUI::CheckIndispensableParam()
{
  if (m_MapSizeParam == true &&
      m_ContentMapParam == true &&
      m_TeamParam == true &&
      m_NewPlayerParam == true )
    m_IndispensableParam = true;
}

void    GUI::update()
{
  Session       *old = 0;

  m_Connection.process();  
  CheckIndispensableParam();
  if (!m_Connection.is_connected())
    {
      std::cout << "Server disconnected" << std::endl;
      m_App.Close();
    }
  if (!m_Session)
    m_App.Close();
  else
    {
      old = m_Session;
      try{
	if ((m_Session = m_Session->update(*this)) != old)
	  delete old;
      }
      catch (std::exception& e){
	std::cerr << e.what() << std::endl;
        m_Session = 0;
      }
    }
}

void    GUI::display()
{
  m_App.Clear();
  if (!m_Session)
    m_App.Close();
  else
    {
      m_Session->draw(*this);
      m_App.Display();
    }
}

void    GUI::unload()
{
  delete m_Session;
}

sf::RenderWindow&      GUI::GetApp()
{
  return m_App;
}

const GameInfo&		GUI::GetGameInfo() const
{    
return m_GameInfo;
}

const Map &		GUI::GetMap() const
{
  return m_GameInfo.GetMap();
}

const int&		GUI::GetTimeLoad() const
{
  return (m_Time);
}

const int&		GUI::GetMaxTimeLoad() const
{
  return (m_MaxTime);
}

const std::vector<std::string>	&GUI::GetEventList() const
{
  return m_EventList;
}

Team const&		GUI::GetTeams() const
{
  return m_GameInfo.GetTeams();
}

bool const&		GUI::GetBackPressed() const
{
  return m_BackPressed;
}

bool const&		GUI::GetSpacePressed() const
{
  return m_SpacePressed;
}

bool const&		GUI::GetTabPressed() const
{
  return m_TabPressed;
}

bool const&		GUI::GetEndOfGame() const
{
  return m_EndOfGame;
}

std::string const&		GUI::GetWinnerTeam() const
{
  return m_Winner;
}


void GUI::_handle_BroadcastServerCommand(IServerCommand const& command)
{
  BroadcastServerCommand const& c(dynamic_cast<BroadcastServerCommand const&>(command));

  m_oss << c.player;
  m_Result = m_oss.str();
  
  if (c.message.size() < 100)
    m_EventList.push_back("Player "+ m_Result + " send :" + c.message);
  else
    m_EventList.push_back("Player "+ m_Result + " send a braodcast too long to be shown");
  m_GameInfo.Action_PlayerBroadcast(c.player, c.message);
  (void)command;
  m_oss.str("");
}


void GUI::_handle_UnrecognizedServerCommand(IServerCommand const& command)
{
  UnrecognizedServerCommand const& c(dynamic_cast<UnrecognizedServerCommand const&>(command));
 
  std::cerr << "unknown command: \"" << c.str() << "\"" << std::endl;
  m_EventList.push_back(std::string("Unknown command cach"));
  (void)command;
}

void GUI::_handle_ContentServerCommand(IServerCommand const& command)
{
  ContentServerCommand const& c(dynamic_cast<ContentServerCommand const&>(command));

  m_Coo.x =   c.x;
  m_Coo.y =   c.y;
  

  m_GameInfo.AddCaseMap(m_Coo, c.resources);
  ++m_Time;
  ++m_Bct;
  if ( m_Bct ==  (m_GameInfo.GetMap().GetSizeMap().y * m_GameInfo.GetMap().GetSizeMap().x))
    m_ContentMapParam = true;
  (void)command;
}

void GUI::_handle_DieServerCommand(IServerCommand const& command)
{
  DieServerCommand const& c(dynamic_cast<DieServerCommand const&>(command));
 
  m_oss << c.player;
  m_Result = m_oss.str();

  m_EventList.push_back("Player" + m_Result +" is dead");
  m_GameInfo.Action_PlayerDie(c.player);
  m_oss.str("");
  (void)command;
}

void GUI::_handle_DropServerCommand(IServerCommand const& command)
{
  DropServerCommand const& c(dynamic_cast<DropServerCommand const&>(command));
  m_oss << c.player;
  m_Result = m_oss.str();

  m_EventList.push_back("Player " + m_Result+ " Drop " + m_RessourcesName[c.resource]);
  m_GameInfo.Action_PlayerDropRessources(c.player, c.resource);
  (void)command;
  m_oss.str("");
}

void GUI::_handle_EggBornServerCommand(IServerCommand const& command)
{
  EggBornServerCommand const& c(dynamic_cast<EggBornServerCommand const&>(command));

  m_GameInfo.Action_EggBorn(c.egg);
  m_EventList.push_back("An egg is born");
  (void)command;
  (void)c;
}
void GUI::_handle_EggDieServerCommand(IServerCommand const& command)
{
  EggDieServerCommand const& c(dynamic_cast<EggDieServerCommand const&>(command));

  m_GameInfo.Action_EggDie(c.egg);
  m_EventList.push_back("An egg is dead");
  (void)command;
  (void)c;
}
void GUI::_handle_EggHatchServerCommand(IServerCommand const& command)
{
  EggHatchServerCommand const& c(dynamic_cast<EggHatchServerCommand const&>(command));

  m_GameInfo.Action_EggHatch(c.egg);
  m_EventList.push_back("An egg Hatch");
  (void)command;
  (void)c;
}
void GUI::_handle_ExpulsionServerCommand(IServerCommand const& command)
{
  ExpulsionServerCommand const& c(dynamic_cast<ExpulsionServerCommand const&>(command));
  m_oss << c.player;
  m_Result = m_oss.str();

  m_EventList.push_back("Player " + m_Result+ " has been expulse");  
  (void)command;
  (void)c;
  m_oss.str("");
}
void GUI::_handle_ForkServerCommand(IServerCommand const& command)
{
  ForkServerCommand const& c(dynamic_cast<ForkServerCommand const&>(command));
  m_oss << c.player;
  m_Result = m_oss.str();

  m_EventList.push_back("Player " + m_Result+ " Fork !");
  m_GameInfo.Action_PlayerFork(c.player);
  (void)command;
  m_oss.str("");
}
void GUI::_handle_GameEndServerCommand(IServerCommand const& command)
{
  GameEndServerCommand const& c(dynamic_cast<GameEndServerCommand const&>(command));

  m_EventList.push_back("End Of game");
  
  m_EndOfGame = true;
  m_Winner = c.team;
  (void)command;
  (void)c;
}
void GUI::_handle_GetServerCommand(IServerCommand const& command)
{
  GetServerCommand const& c(dynamic_cast<GetServerCommand const&>(command));
  m_oss << c.player;
  m_Result = m_oss.str();

  if (c.resource != 0)
    m_EventList.push_back("Player " + m_Result+ " get " + m_RessourcesName[c.resource]);
  m_GameInfo.Action_PlayerGetRessources(c.player, c.resource);
  m_oss.str("");
  (void)command;
}
void GUI::_handle_HandshakeServerCommand(IServerCommand const& command)
{
  HandshakeServerCommand const& c(dynamic_cast<HandshakeServerCommand const&>(command));
    

  m_EventList.push_back("Welcome");
  m_Connection.send("GRAPHIC\n");
  (void)command;
  (void)c;
}

void GUI::_handle_IncantationCastServerCommand(IServerCommand const& command)
  {
    IncantationCastServerCommand const& c(dynamic_cast<IncantationCastServerCommand const&>(command));
 
    m_GameInfo.Action_PlayerCastIncantation(c.x, c.y, c.level, c.players);
    (void)command;
    (void)c;
}
 
void GUI::_handle_IncantationEndServerCommand(IServerCommand const& command)
{
  IncantationEndServerCommand const& c(dynamic_cast<IncantationEndServerCommand const&>(command));
  /*
  int const x;
  int const y;
  int const m_Result;
  */ 
  //  m_GameInfo.Action_PlayerEndIncantation(c.player, c.resource);
 (void)command;
  (void)c;
}
void GUI::_handle_InventoryServerCommand(IServerCommand const& command)
{
  InventoryServerCommand const& c(dynamic_cast<InventoryServerCommand const&>(command));
  
  m_GameInfo.Update_PlayerInv(c.player, c.resources);
 (void)command;
  (void)c;
}
void GUI::_handle_LevelServerCommand(IServerCommand const& command)
{
  (void)command;
  LevelServerCommand const& c(dynamic_cast<LevelServerCommand const&>(command));
  std::ostringstream oss;
  std::ostringstream oss2;
  oss << c.player;
  oss2 << c.level;
  m_Result = oss.str();
  std::string m_Result2 = oss2.str();

  m_EventList.push_back("Player " + m_Result + " is now level " + m_Result2);
  m_GameInfo.Action_LvlUp(c.player, c.level);
}

void GUI::_handle_MapSizeServerCommand(IServerCommand const& command)
{
  MapSizeServerCommand const& c(dynamic_cast<MapSizeServerCommand const&>(command));
  std::ostringstream oss;
  std::ostringstream oss2;
  
  oss << c.x;
  oss2 << c.y;
  m_Result = oss.str();
  std::string m_Result2 = oss2.str();
  
  if(m_IndispensableParam != true)
    {
      std::string f= "Creation of Map [ " + m_Result + ", ";
      m_GameInfo.SetSizeMap(c.x, c.y);
      m_EventList.push_back(f + m_Result2 + " ] ");
      m_Time = 0;
      m_MaxTime = c.x * c.y;
    }
  else
    m_EventList.push_back(" Map Size already entered ");
  m_MapSizeParam = true;
  (void)command;
}
void GUI::_handle_MessageServerCommand(IServerCommand const& command)
{
  MessageServerCommand const& c(dynamic_cast<MessageServerCommand const&>(command));

  (void)command;
  (void)c;
}

void GUI::_handle_NewEggServerCommand(IServerCommand const& command)
{
  NewEggServerCommand const& c(dynamic_cast<NewEggServerCommand const&>(command));
  m_Coo.x = c.x;
  m_Coo.y = c.y;
  Egg			New(m_Coo, c.egg);

  m_GameInfo.AddEgg(c.player, New);
  (void)command;
  (void)c;
}
void GUI::_handle_NewPlayerServerCommand(IServerCommand const& command)
{
  NewPlayerServerCommand const& c(dynamic_cast<NewPlayerServerCommand const&>(command));

  Player		New;
  std::ostringstream	oss;
  m_oss << c.team;
  m_Result = m_oss.str();

  m_Coo.x = c.x;
  m_Coo.y = c.y;
  New.SetLvl(c.level);
  New.SetId(c.player);
  New.SetCoo(m_Coo, c.orientation);
  New.SetTeamName(c.team);
  New.SetState(Normal);
  m_GameInfo.AddPlayer(c.team, New);
  m_EventList.push_back("A New Player joined the " + m_Result + " Team");
  m_NewPlayerParam = true;  
  (void)command;
  m_oss.str("");
}

void GUI::_handle_PositionServerCommand(IServerCommand const& command)
{
  PositionServerCommand const& c(dynamic_cast<PositionServerCommand const&>(command));

  m_Coo.x = c.x;
  m_Coo.y = c.y;

  m_GameInfo.Action_MovePlayer(m_Coo, c.orientation, c.player);
  (void)command;
}

void GUI::_handle_TeamNameServerCommand(IServerCommand const& command)
{
  TeamNameServerCommand const& c(dynamic_cast<TeamNameServerCommand const&>(command));
  m_oss << c.team;
  m_Result = m_oss.str();


  if(m_IndispensableParam != true)
    {
      m_GameInfo.AddTeam(c.team);
      m_GameInfo.DisplayTeam();  
      m_EventList.push_back("Creation of Team " + m_Result);
    }
  else
    {
      m_EventList.push_back("All Team are already created ");
    }
  m_TeamParam = true;
  (void)command;
  m_oss.str("");
}
void GUI::_handle_TimeServerCommand(IServerCommand const& command)
{
  TimeServerCommand const& c(dynamic_cast<TimeServerCommand const&>(command));
  m_oss << c.time;
  m_Result = m_oss.str();
  m_EventList.push_back("The server time has been changed to " + m_Result);
  
  (void)command;
  (void)c;
  m_oss.str("");
}
void GUI::_handle_UnknownCommandServerCommand(IServerCommand const& command)
{
  (void)command;
  
}
