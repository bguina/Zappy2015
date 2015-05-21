#ifndef __TERMINAL
#define __TERMINAL
# include <vector>
# include <iostream>
# include <SFML/Graphics.hpp>
# include "GraphicsEngine.hpp"

class		Terminal : public GraphicsEngine
{
public:
  Terminal(sf::RenderWindow &App,const std::vector<std::string> &Event);
  void	       Display(unsigned int min,unsigned int max);
  void	       Display();
  void	       Refresh();
  void	       SaveEvent();
protected:
  sf::RenderWindow		&m_App;
  const std::vector<std::string>	&m_EventList;
  float				m_LineY;
  unsigned int			m_min;
  unsigned int			m_max;
  unsigned int			m_LastSize;
  sf::String			m_Text;
  sf::Font			m_MyFont;
};

#endif
