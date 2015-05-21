#include "Player.hpp"
#include <iostream>

Player::Player()
{
  m_Lvl = 0;
  m_Id   = -1;
  m_TeamName = "Test";
  m_State = Normal;
  m_Orientation = 0;
  m_Coo.x = 0; m_Coo.y = 0;
  m_To.x = 0; m_To.y = 0;
  m_Last.x = 0; m_Last.y = 0;
  m_Inventory.resize(7,0);
}

Player::Player(const Player& p)
{
  m_State = p.GetState();
  m_Lvl = p.GetLvl();
  m_Id = p.GetId();
  m_TeamName = p.GetTeamName();
  m_Orientation = p.GetOrientation();
  m_Coo = p.GetPosition();
  m_Inventory = p.GetInventory();
}

Player& Player::operator=(Player const& p) 
{
  m_State = p.GetState();
  m_Lvl = p.GetLvl();
  m_Id = p.GetId();
  m_TeamName = p.GetTeamName();
  m_Orientation = p.GetOrientation();
  m_Coo = p.GetPosition();
  m_Inventory = p.GetInventory();
  return *this;
}

bool Player::operator==(Player const& p) const
{
  return m_Id == p.m_Id;
}

void		Player::SetLvl(int lvl)
{
  m_Lvl = lvl;
}

void		Player::SetId(int id)
{
  m_Id = id;
}

void		Player::SetCoo(Coordonnees& coo,const int& o)
{
  m_Coo = coo;
  m_Last = coo;
  m_Orientation = o;
  m_Move.first = m_Coo;
  m_Move.second = m_Last;
}

void		Player::SetInventory(std::vector<int> &inv)
{
  m_Inventory = inv;
}

void		Player::MoveTo(Coordonnees& To,const int& o)
{
  m_Last = m_Coo;
  m_Coo = To;
  m_Orientation = o;
  m_Move.first = m_Coo;
  m_Move.second = m_Last;

}

void		Player::SetState(state s)
{
  m_State = s;
}

void		Player::SetTeamName(std::string name)
{
  m_TeamName = name;
}


const std::vector<int>&		Player::GetInventory() const
{
  return m_Inventory;
}

int		Player::_GetLvl()
{
  return m_Lvl;
}

const int&		Player::GetLvl() const
{
  return m_Lvl;
}

const int&		Player::GetId() const
{
  return (m_Id);
}

const std::string&		Player::GetTeamName() const
{
  return m_TeamName;
}

const Coordonnees&		Player::GetPosition() const
{
  return m_Coo;
}

const Coordonnees&		Player::GetLastPosition() const
{
  return m_Last;
}

const int&		Player::GetOrientation() const
{
  return m_Orientation;
}


const std::pair<Coordonnees, Coordonnees>&		Player::GetMove() const
{
  return m_Move;
}

const state&		Player::GetState() const
{
  return m_State;
}
