#ifndef LOADSESSION_HPP_
# define LOADSESSION_HPP_
# include "Session.hpp"
# include "GUI.hpp"

class LoadSession : public Session , public GraphicsEngine
{
public:
  LoadSession(sf::RenderWindow &App, bool&Map, bool&Content, bool&Team, bool &Player, bool &Iparam);
  virtual ~LoadSession();
  virtual Session *update(const GUI &);
  virtual void draw(const GUI &);
  std::string bool_as_text(bool b);
private:
  sf::RenderWindow &m_App;
  const bool&		m_MapSizeParam;
  const bool&		m_ContentMapParam;
  const bool&		m_TeamParam;
  const bool&		m_NewPlayerParam;
  const bool&		m_IndispensableParam;
};

#endif
