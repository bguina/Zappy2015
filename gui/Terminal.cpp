#include "Terminal.hpp"
#include <iostream>

Terminal::Terminal(sf::RenderWindow &App,const std::vector<std::string> &EventList) : GraphicsEngine(App), m_App(App), m_EventList(EventList)
{
  m_Text.SetPosition(10.f, 400.f);

  m_min = m_EventList.size() - 6;
  m_max = m_EventList.size();
  m_LastSize = m_EventList.size();
}


void	     Terminal::Refresh()
{

}

void	     Terminal::Display()
{
  int i = m_EventList.size() - 6;
  DrawText(m_EventList[i +1], sf::Color(0,0,0), 20.f, 670.f,  10.f);
  DrawText(m_EventList[i +2], sf::Color(0,0,0), 20.f, 690.f , 10.f);
  DrawText(m_EventList[i +3], sf::Color(0,0,0), 20.f, 710.f , 10.f);
  DrawText(m_EventList[i +4], sf::Color(0,0,0), 20.f, 730.f , 10.f);
  DrawText(m_EventList[i +4], sf::Color(0,0,0), 20.f, 750.f , 10.f);
  DrawText(m_EventList[i +5], sf::Color(0,0,0), 20.f, 770.f , 10.f);
}


