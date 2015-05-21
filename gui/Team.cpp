#include "Team.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Egg.hpp"

Team::Team()
{
  m_NewTeam = 0;
}

void		Team::AddPlayer(std::string name, Player p)
{
  m_Player = _GetPlayer(p.GetId());
  if (m_Player == NULL)
    {
      m_TeamTab[name].first.push_back(p);
    }
}

void		Team::AddEgg(int id, Egg g)
{
  m_Player = _GetPlayer(id);
  if (m_Player != NULL)
    m_TeamTab[m_Player->GetTeamName()].second.push_back(g);
}

void		Team::AddTeam(std::string name)
{
  std::pair <std::vector <Player>, std::vector <Egg> > N;

  if (m_TeamTab.find(name) ==  m_TeamTab.end())
    {
      m_TeamTab[name] = N;
      ++m_NewTeam;
    }
}

void		Team::Display()
{
}

void		Team::Action_MovePlayer(Coordonnees coo, int o, int id)
{
  m_Player = _GetPlayer(id);
  if (m_Player != NULL)
    m_Player->MoveTo(coo, o);
}

void		Team::Action_LvlUp(int id, int lvl)
{
  m_Player = _GetPlayer(id);
  if (m_Player != NULL)
    m_Player->SetLvl(lvl);
}

void		Team::Action_PlayerBroadcast(int id, std::string msg)
{
  m_Player = _GetPlayer(id);
  if (m_Player != NULL)    
  m_Player->SetState(Broadcast);
  (void)msg;
}

void		Team::Action_PlayerCastIncantation(int x, int y, int lvl, std::vector<int> id)
{
  (void)x;
  (void)y;
  (void)lvl;
  for(unsigned int i = 0; i < id.size(); ++i)
    {
      m_Player = _GetPlayer(id[i]);
      if (m_Player != NULL)
	m_Player->SetState(SpellCast);
    }
}

void		Team::Action_PlayerEndIncantation(int x, int y, int result)
{
  (void)x;
  (void)y;
  (void)result;
}

void		Team::Action_PlayerFork(int id)
{
  m_Player = _GetPlayer(id);
  if (m_Player != NULL)
    m_Player->SetState(Fork);
}

void		Team::Action_PlayerDropRessources(int id, int resources)
{
  (void)resources;
  m_Player = _GetPlayer(id);
  if (m_Player != NULL)
    m_Player->SetState(Drop);
}

void		Team::Action_PlayerGetRessources(int id, int resources)
{
  (void)resources;
  m_Player = _GetPlayer(id);
  if (m_Player != NULL)
    m_Player->SetState(Get);
}


void		Team::Action_PlayerDie(int id)
{
  m_Player = _GetPlayer(id);
  if (m_Player != NULL)
    m_Player->SetState(Die);
}

void          Team::Action_EggHatch(int id)
{
  m_Egg = _GetEgg(id);
  if (m_Egg != NULL)
    m_Egg->SetState(Hatch);
}
void          Team::Action_EggBorn(int id)
{
  m_Egg = _GetEgg(id);
  if (m_Egg != NULL)
    m_Egg->SetState(Born);
}
void          Team::Action_EggDie(int id)
{
  m_Egg = _GetEgg(id);
  if (m_Egg != NULL)
    m_Egg->SetState(Dead);
}

void          Team::Update_PlayerInv(int id, std::vector<int> Inv)
{
  m_Player = _GetPlayer(id);
  if (m_Player != NULL)
    m_Player->SetInventory(Inv);
}


Egg		*Team::_GetEgg(const int id)
{
  std::vector<Egg>::iterator                         it2;
  std::map<std::string,   std::pair < std::vector<Player>,std::vector<Egg> > >::iterator it;

  for ( it = m_TeamTab.begin() ; it != m_TeamTab.end(); ++it)
    {
      for (it2 = (*it).second.second.begin() ; it2 != (*it).second.second.end(); ++it2)
        {
          if ((*it2).GetId() == id)
	    return &(*it2);
        }
    }
  return NULL;
}

Player		*Team::_GetPlayer(const int id)
{
  std::vector<Player>::iterator                         it2;
  std::map<std::string,   std::pair < std::vector<Player>,std::vector<Egg> > >::iterator it;

  for ( it = m_TeamTab.begin() ; it != m_TeamTab.end(); ++it)
    {
      for (it2 = (*it).second.first.begin() ; it2 != (*it).second.first.end(); ++it2)
        {
          if ((*it2).GetId() == id)
	    return &(*it2);
        }
    }
  return NULL;
}

const Player* Team::GetPlayer(int id) const
{
  std::vector<Player>::const_iterator                         it2;
  std::map<std::string,   std::pair < std::vector<Player>,std::vector<Egg> > >::const_iterator it;

  for ( it = m_TeamTab.begin() ; it != m_TeamTab.end(); ++it )
    {
      for (it2 = (*it).second.first.begin() ; it2 != (*it).second.first.end(); ++it2 )
        {
          if ((*it2).GetId() == id)
	    return &(*it2);
        }
    }
  return NULL;
}

int		Team::GetNbTeams() const
{
  return m_TeamTab.size();
}

const std::map<std::string,   std::pair < std::vector<Player>,std::vector<Egg> > > &Team::GetTeams() const
{
  return m_TeamTab;
}

const int&		Team::GetNbTeam() const
{
  return m_NewTeam;
}


const Player&		Team::GetLvlMax(std::string name) const
{
  std::vector<Player>::const_iterator                         it2;
  int		max = 0;
  int		id = 0;
  
  for (it2 = m_TeamTab.find(name)->second.first.begin() ; it2 != m_TeamTab.find(name)->second.first.end(); ++it2 )
    {
      if ((*it2).GetLvl() > max)
	{
	  max = (*it2).GetLvl();
	  id  = (*it2).GetId();
	}
    }
  return *GetPlayer(id);
}
