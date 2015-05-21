#include "Map.hpp"
#include <iostream>
#include <sstream>

void		Map::SetSize(int x, int y)
{
  m_SizeMap.x = x;
  m_SizeMap.y = y;
}

void		Map::AddCase(Coordonnees coo, std::vector<int> inv)
{
  m_MapTab[coo] = inv;
}

void		Map::Display()
{
  std::map<Coordonnees, std::vector<int> >::iterator it; 
}

const std::map<Coordonnees, std::vector<int> >&		Map::GetMapCoo() const
{
  return (m_MapTab);
}

const Coordonnees&	Map::GetSizeMap() const
{
  return m_SizeMap;
}


int			Map::GetItems(int x, int y, unsigned int r) const
{
    std::map<Coordonnees, std::vector<int> >::const_iterator it(m_MapTab.find(Coordonnees(x, y)));

    if (it == m_MapTab.end())
        return 0;
    return it->second[r];
}
