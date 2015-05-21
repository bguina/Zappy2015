#ifndef ENDSESSION_HPP_
# define ENDSESSION_HPP_
# include "Session.hpp"
# include "GUI.hpp"
#include "GraphicsEngine.hpp"

class EndSession : public Session , public GraphicsEngine
{
public:
  EndSession(sf::RenderWindow &App,const std::string &Winner);
  virtual		~EndSession();
  virtual Session *	update(const GUI &);
  virtual void		draw(const GUI &);
private:
  sf::RenderWindow	&m_App;
  const std::string&    m_Winner;
};

#endif
