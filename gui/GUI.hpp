#ifndef HPP_GUI
#define HPP_GUI

#include <vector>
#include <string>
#include <iostream>
#include "ServerCommands/UnrecognizedServerCommand.hpp"
#include "Connection.hpp"
#include "ServerCommands.hpp"
#include <SFML/Graphics.hpp>
#include "GameInfoBar.hpp"
#include "Session.hpp"
#include "GameInfo.hpp"
#include "Terminal.hpp"
#include "ViewInfo.hpp"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

class		Session;

class GUI
{
public:
  static int const default_port=4242;
  GUI()
    : m_Connection(Connection::singleton())
  {
#define REGISTER_HANDLER(command)					\
    m_Connection.register_handler(command::id, *this, &GUI::_handle_##command)
    REGISTER_HANDLER(BroadcastServerCommand);
    REGISTER_HANDLER(UnrecognizedServerCommand);
    REGISTER_HANDLER(ContentServerCommand);
    REGISTER_HANDLER(DieServerCommand);
    REGISTER_HANDLER(DropServerCommand);
    REGISTER_HANDLER(EggBornServerCommand);
    REGISTER_HANDLER(EggDieServerCommand);
    REGISTER_HANDLER(EggHatchServerCommand);
    REGISTER_HANDLER(ExpulsionServerCommand);
    REGISTER_HANDLER(ForkServerCommand);
    REGISTER_HANDLER(GameEndServerCommand);
    REGISTER_HANDLER(GetServerCommand);
    REGISTER_HANDLER(HandshakeServerCommand);
    REGISTER_HANDLER(IncantationCastServerCommand);
    REGISTER_HANDLER(IncantationEndServerCommand);
    REGISTER_HANDLER(InventoryServerCommand);
    REGISTER_HANDLER(LevelServerCommand);
    REGISTER_HANDLER(MapSizeServerCommand);
    REGISTER_HANDLER(MessageServerCommand);
    REGISTER_HANDLER(NewEggServerCommand);
    REGISTER_HANDLER(NewPlayerServerCommand);
    REGISTER_HANDLER(PositionServerCommand);
    REGISTER_HANDLER(TeamNameServerCommand);
    REGISTER_HANDLER(TimeServerCommand);
    REGISTER_HANDLER(UnknownCommandServerCommand);

#undef REGISTER_HANDLER
  }
 
  ~GUI()
  {
    m_Connection.disconnect();
  }

  int run(std::string const& host, int port);
protected:
  void  EventHandler();
  void  display();
  void  update();
  void	initialize();
  void	unload();

  void _handle_BroadcastServerCommand(IServerCommand const& command);
  void _handle_UnrecognizedServerCommand(IServerCommand const& command);
  void _handle_ContentServerCommand(IServerCommand const& command);
  void _handle_DieServerCommand(IServerCommand const& command);
  void _handle_DropServerCommand(IServerCommand const& command);
  void _handle_EggBornServerCommand(IServerCommand const& command);
  void _handle_EggDieServerCommand(IServerCommand const& command);
  void _handle_EggHatchServerCommand(IServerCommand const& command);
  void _handle_ExpulsionServerCommand(IServerCommand const& command);
  void _handle_ForkServerCommand(IServerCommand const& command);
  void _handle_GameEndServerCommand(IServerCommand const& command);
  void _handle_GetServerCommand(IServerCommand const& command);
  void _handle_HandshakeServerCommand(IServerCommand const& command);
  void _handle_IncantationCastServerCommand(IServerCommand const& command);
  void _handle_IncantationEndServerCommand(IServerCommand const& command);
  void _handle_InventoryServerCommand(IServerCommand const& command);
  void _handle_LevelServerCommand(IServerCommand const& command);
  void _handle_MapSizeServerCommand(IServerCommand const& command);
  void _handle_MessageServerCommand(IServerCommand const& command);
  void _handle_NewEggServerCommand(IServerCommand const& command);
  void _handle_NewPlayerServerCommand(IServerCommand const& command);
  void _handle_PositionServerCommand(IServerCommand const& command);
  void _handle_TeamNameServerCommand(IServerCommand const& command);
  void _handle_TimeServerCommand(IServerCommand const& command);
  void _handle_UnknownCommandServerCommand(IServerCommand const& command);
private:
  void			CheckIndispensableParam();
  Connection&		m_Connection;
  sf::RenderWindow      m_App;
  sf::Event		m_Event;
  Session	        *m_Session;
  GameInfo		m_GameInfo;
  std::vector<std::string>	m_EventList;
  std::vector<std::string>	m_RessourcesName;
  int			m_Bct;
  int			m_Time;
  int			m_MaxTime;
  bool			m_TabPressed;
  bool			m_SpacePressed;
  bool			m_BackPressed;
  bool			m_F1Pressed;
  bool			m_F2Pressed;
  bool			m_F3Pressed;
  bool			m_IndispensableParam;
  bool			m_MapSizeParam;
  bool			m_ContentMapParam;
  bool			m_TeamParam;
  bool			m_NewPlayerParam;
  bool			m_EscapPressed;
  bool			m_EndOfGame;
  std::string		m_Winner;
  std::ostringstream	m_oss;
  std::string		m_Result;
  Coordonnees		m_Coo;
public:
  std::vector<std::string>const	&GetEventList() const;
  sf::Event&			GetEvent();
  sf::RenderWindow&		GetApp();
  const bool&				GetTabPressed() const;
  const bool&				GetSpacePressed() const;
  const bool&				GetBackPressed() const;
  const bool&				GetEndOfGame() const;
  const GameInfo&			GetGameInfo()const;
  const Map&				GetMap() const;
  const Team&				GetTeams() const;
  const int&				GetTimeLoad() const;
  const int&				GetMaxTimeLoad() const;
  const std::string&			GetWinnerTeam() const;
};

#endif

