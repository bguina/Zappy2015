#include "Camera.hpp"

Camera::Camera(sf::RenderWindow &App, const sf::Vector2f &Center, const sf::Vector2f &HalfSize)
  : m_View(Center, HalfSize) ,  m_App(App)
{
  m_zoom = 0;
  zoom_max = 20;
  zoom_min = -20;
  
}

Camera::~Camera()
{
}

void Camera::EventHandler(float zoom)
{
  if (m_App.GetInput().IsKeyDown(sf::Key::Left))
    m_View.Move(-zoom, -zoom * .50f);
  if (m_App.GetInput().IsKeyDown(sf::Key::Right))
    m_View.Move(zoom, zoom * .50f);
  if (m_App.GetInput().IsKeyDown(sf::Key::Up))
    m_View.Move(zoom, -zoom * .50f);
  if (m_App.GetInput().IsKeyDown(sf::Key::Down))
    m_View.Move(-zoom, zoom * .50f);
  if (m_App.GetInput().IsKeyDown(sf::Key::Add) && m_zoom < zoom_max)
    {
      m_View.Zoom(1.0f + (.001f * zoom));
      m_zoom++;
    }
  if (m_App.GetInput().IsKeyDown(sf::Key::Subtract) && m_zoom > zoom_min)
    {
      m_View.Zoom(1.0f - (.001f * zoom));
      m_zoom--;
    }
}

void Camera::Move(float x, float y)
{
  m_View.Move(x, y);
}

void Camera::SetCamera()
{
  m_App.SetView(m_View);
}

void Camera::SetCenter(float x, float y)
{
  m_View.SetCenter(x, y);
}		     

void Camera::DisplayCamera()
{
  m_App.SetView(m_App.GetDefaultView());
}
