#ifndef GAME_INFO
#define GAME_INFO
#include "Map.hpp"
#include "Team.hpp"
#include "Player.hpp"
#include "Egg.hpp"
#include <vector>

class		GameInfo
{
public:

  // Map Function
  void		SetSizeMap(int x, int y);
  void		AddCaseMap(Coordonnees Coo, std::vector<int> Ressources);
  void		DisplayMap();
  // Team Function  
  void		AddTeam(std::string TeamName);
  void		AddPlayer(std::string TeamName, Player P);
  void		AddEgg(int Id, Egg E);
  void		DisplayTeam();
  // ----------- Action / Animation -------------
  void		Action_MovePlayer(Coordonnees C, int Orientation, int Id);
  void		Action_LvlUp(int Id, int Lvl);
  void          Action_PlayerBroadcast(int Id, std::string Msg);
  void          Action_PlayerCastIncantation(int x, int y, int Lvl, std::vector<int> Id);
  void          Action_PlayerEndIncantation(int x, int y, int result);
  void          Action_PlayerFork(int Id);
  void          Action_PlayerDropRessources(int Id, int Ressources);
  void          Action_PlayerGetRessources(int Id, int Ressources);
  void          Action_PlayerDie(int Id);
  void          Action_EggHatch(int);
  void          Action_EggBorn(int);
  void          Action_EggDie(int);
  // Other Function
  void          Update_PlayerInv(int Id, std::vector<int> Inv);
  void          Update_PlayerExpulse(int Id);
  void          Update_NewEgg(int, int, int, int);
  // System Function 
  void		ServerMsg(std::string Msg);
  void		GetTimeServer();
  void		ModifyTimeServer();
  void		GameEnd();
  // Getters Info
  Coordonnees	GetMapDimension();  
  const   Map	&GetMap() const;
  const   Team	&GetTeams() const;
  const   int	&GetNbTeam() const;
protected:
  Map		m_Map;
  Team		m_Team;
};

#endif
