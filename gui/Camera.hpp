#ifndef __CAMERA__
# define __CAMERA__

#include <iostream>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Camera
{
private:
  sf::View		m_View;
  sf::RenderWindow	&m_App;
  int			m_zoom;
  int			zoom_max;
  int			zoom_min;

public:
  Camera(sf::RenderWindow & ,const sf::Vector2f &, const sf::Vector2f &);
  ~Camera();
  
  /* positionne la camera */
public:
  void			Move(float, float);
  void			SetCenter(float, float);
  void			SetHalfSize(float, float);
  void			EventHandler(float zoom);

  /* set up et refresh */
public:
  void			SetCamera();
  void			DisplayCamera();
};

#endif 
