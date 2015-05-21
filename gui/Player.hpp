#ifndef _PLAYER
#define _PLAYER
#include "Map.hpp"
#include <iostream>
#include <map>

typedef enum state{
  Normal,
  Broadcast,
  SpellCast,
  EndCast,
  Fork,
  Drop,
  Get,
  Up,  
  Die,
}state;

class		Player
{
public:
  Player();
  Player(const Player& p);
  Player& operator=(const Player& p);
  bool operator==(const Player& p) const;

  void			SetLvl(int);
  void			SetId(int);
  void			SetCoo(Coordonnees&,const int&);
  void			MoveTo(Coordonnees&,const int&);
  void			SetTeamName(std::string);
  void			SetState(state s);
  void			SetInventory(std::vector<int> &);
  int			_GetLvl();
  const int&			GetLvl()const;
  const state&		GetState()const;
  const int		&GetId() const;
  const std::string&	GetTeamName() const;
  const Coordonnees&	GetPosition() const;
  const Coordonnees&	GetLastPosition() const;
  const int&		 GetOrientation() const;
  const std::vector<int>& GetInventory() const;
  const std::pair<Coordonnees, Coordonnees>& GetMove() const;
protected:
  state			m_State;
  int			m_Lvl;
  int			m_Id;
  std::string		m_TeamName;
  int			m_Orientation;
  Coordonnees		m_Coo;
  Coordonnees		m_To;
  Coordonnees		m_Last;
  std::vector<int>	m_Inventory;
  std::pair<Coordonnees, Coordonnees> m_Move;
};

#endif
