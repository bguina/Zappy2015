#include "Egg.hpp"
#include "Map.hpp"

Egg::Egg()
{

}

Egg::Egg(Coordonnees coo, int id)
{
  m_Coo = coo;
  m_Id = id;
  m_State = New;
}

void	Egg::SetId(int id)
{
  m_Id = id;
} 

void	Egg::SetState(EggState s)
{
  m_State = s;
}

const EggState& Egg::GetState() const
{
  return m_State;
}

const int&	Egg::GetId() const
{
  return m_Id;
}

const Coordonnees&	Egg::GetPosition() const
{
  return m_Coo;
}
