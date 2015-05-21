#ifndef _TEAM
#define _TEAM
#include <utility>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include "Player.hpp"
#include "Egg.hpp"

class		Team
{
public:
  Team();
  void		AddPlayer(std::string, Player);
  void		AddEgg(int, Egg);
  void		AddTeam(std::string);
  void		Display();  
  void		Action_MovePlayer(Coordonnees, int, int);
  void		Action_LvlUp(int, int);
  void		Action_PlayerBroadcast(int , std::string);
  void		Action_PlayerCastIncantation(int, int, int, std::vector<int>);
  void		Action_PlayerEndIncantation(int, int, int);
  void		Action_PlayerFork(int);
  void		Action_PlayerDropRessources(int, int);
  void		Action_PlayerGetRessources(int, int);
  void		Action_PlayerDie(int);
  void		Action_EggHatch(int);
  void		Action_EggBorn(int);
  void		Action_EggDie(int);
  void		Update_PlayerInv(int Id, std::vector<int> Inv);
  void		Update_PlayerExpulse(int);
  const Player	*GetPlayer(const int id) const;
  int		GetNbTeams() const;
  const int&		GetNbTeam() const;
  const Player &GetLvlMax(std::string name) const;
  const std::map<std::string,   std::pair < std::vector<Player>,std::vector<Egg> > > &GetTeams() const;
private:
  int		m_NewTeam;
  Player	*_GetPlayer(const int id);
  Egg		*_GetEgg(const int id);
  Player        *m_Player;
  Egg		*m_Egg;
  std::map<std::string,   std::pair < std::vector<Player>, std::vector<Egg> > > m_TeamTab;
};

#endif
