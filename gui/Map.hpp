#ifndef _MAP
#define _MAP
#include <map>
#include <vector>
#include <iostream>

class Coordonnees
{
public:
  int	x;
  int	y;
  Coordonnees(int x_arg=0, int y_arg=0)
    : x(x_arg), y(y_arg)
  {
  }
  bool operator<(Coordonnees const& c) const
  {
    return (x == c.x ?  y == c.y ? false : y < c.y : x < c.x);
  }
  bool operator==(Coordonnees const& c) const
  {
    if(x == c.x && y == c.y)
      return true;
    else
      return false;
  }
};

// TODO Mettre en anglais

class		Map
{
public:
  void		SetSize(int , int);
  void		AddCase(Coordonnees, std::vector<int>);
  void		Display();
  const Coordonnees&	GetSizeMap() const;
  const std::map<Coordonnees ,std::vector<int> >& GetMapCoo() const;
  int GetItems(int x, int y, unsigned int r) const;
  // TODO : deferencer un minumum , faire un get sur Inv ou sur Coo pas les 2
private:
  // TODO: utiliser correctement la convention camelcase
  std::map<Coordonnees ,std::vector<int> >m_MapTab;
  Coordonnees	m_SizeMap;
};

#endif
