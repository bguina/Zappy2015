#ifndef _EGG
#define _EGG
#include "Map.hpp"

typedef enum Eggstate{
  New,
  Hatch,
  Born,
  Dead
}EggState;


class		Egg
{
public:
  Egg();
  Egg(Coordonnees coo, int id);
  void			SetId(int id);
  void			SetState(Eggstate s);
  const int&		GetId() const;
  const Coordonnees&	GetPosition() const;
  const EggState&	GetState()const;
private:
  EggState		m_State;
  Coordonnees		m_Coo;
  int			m_Id;
};


#endif
