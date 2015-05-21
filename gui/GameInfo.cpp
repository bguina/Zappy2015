#include "GameInfo.hpp"


void		GameInfo::SetSizeMap(int x, int y)
{
  m_Map.SetSize(x, y);
}

void		GameInfo::AddCaseMap(Coordonnees coo, std::vector<int> inv)
{
  m_Map.AddCase(coo, inv);
}

void		GameInfo::DisplayMap()
{
  m_Map.Display();
}

void		GameInfo::AddTeam(std::string team)
{
  m_Team.AddTeam(team);
}

void		GameInfo::AddPlayer(std::string team, Player p)
{
  m_Team.AddPlayer(team, p);
}

void		GameInfo::AddEgg(int id, Egg g)
{
  m_Team.AddEgg(id, g);
}

void		GameInfo::DisplayTeam()
{
  m_Team.Display();
}

void		GameInfo::Action_MovePlayer(Coordonnees coo, int o, int id)
{
  m_Team.Action_MovePlayer(coo, o , id);
}

void		GameInfo::Action_LvlUp(int id,int lvl)
{
  m_Team.Action_LvlUp(id, lvl);
}

void		GameInfo::Action_PlayerBroadcast(int player, std::string msg)
{
  (void)player;
  (void)msg;
}
void		GameInfo::Action_PlayerCastIncantation(int x, int y, int lvl, std::vector<int> players)
{
  m_Team.Action_PlayerCastIncantation(x, y, lvl , players);
}
void		GameInfo::Action_PlayerEndIncantation(int x,  int y, int result)
{
  m_Team.Action_PlayerEndIncantation(x, y, result);
}
void		GameInfo::Action_PlayerFork(int player)
{
  m_Team.Action_PlayerFork(player);
}
void		GameInfo::Action_PlayerDropRessources(int player, int ressources)
{
  m_Team.Action_PlayerDropRessources(player, ressources);
}
void		GameInfo::Action_PlayerGetRessources(int player, int ressources)
{
  m_Team.Action_PlayerGetRessources(player, ressources);
}
void		GameInfo::Action_PlayerDie(int player)
{
  m_Team.Action_PlayerDie(player);
}

void		GameInfo::Action_EggBorn(int id)
{
  m_Team.Action_EggBorn(id);
}

void		GameInfo::Action_EggDie(int id)
{
  m_Team.Action_EggDie(id);
}

void		GameInfo::Action_EggHatch(int id)
{
  m_Team.Action_EggHatch(id);
}

void          GameInfo::Update_PlayerInv(int Id, std::vector<int> Inv)
{
  m_Team.Update_PlayerInv(Id, Inv);
}

const Map		&GameInfo::GetMap() const
{
  return (m_Map);
}

const Team		&GameInfo::GetTeams() const
{
  return (m_Team);
}

const int		&GameInfo::GetNbTeam() const
{
  return m_Team.GetNbTeam();
}
