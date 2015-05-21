
#ifndef SESSION_HPP_
# define SESSION_HPP_
#include <unistd.h>
# include "GUI.hpp"

class GUI;

class Session
{
public:
  virtual ~Session();
  virtual Session *update(const GUI &) = 0;
  virtual void draw(const GUI &) = 0;
protected:
  sf::String	m_Text;
};

#endif
