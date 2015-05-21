# include "GameSession.hpp"
# include "Map.hpp"
# include <set>
# define MAP_X_ISO 1
# define MAP_Y_ISO -10
# define SPEED 0.05
# include "EndSession.hpp"

GameSession::GameSession(const GUI &gui, sf::RenderWindow &App) : 
  m_App(App), 
  m_Camera(m_App, sf::Vector2f(400, 300), sf::Vector2f(400, 300)), 
  m_InfoBar(gui, App)
{
  if (!m_ImageTile.LoadFromFile("img/tile2.png"))
    std::cout << "Img tile not found " << std::endl;
  
  if (!m_ImagePlayer.LoadFromFile("img/feca_m10.png"))
    std::cout << "Img feca not found " << std::endl;
  
  if (!m_ImageEmoticon.LoadFromFile("img/emoticons.png"))
    std::cout << "Img emoticons not found " << std::endl;
  if (!m_ImageEgg.LoadFromFile("img/egg.png"))
    std::cout << "Img egg not found " << std::endl;
  if (!m_ImageArrow.LoadFromFile("img/fleche.png"))
    std::cout << "Img arrow not found " << std::endl;


  m_SpriteArrow.SetImage(m_ImageArrow);
  m_SpriteEmoticon.SetImage(m_ImageEmoticon);
  m_SpriteEgg.SetImage(m_ImageEgg);

  m_AnimPlayer = new ImgAnim(m_ImagePlayer, 4 , 4 );
  m_ImageRessources.resize(TOTAL_RESOURCES);
  for (int i = 0; i < TOTAL_RESOURCES; ++i)
    {
      std::stringstream ss;
      ss << "img/tile_" << i << ".png";
      m_ImageRessources[i].LoadFromFile(ss.str());
      m_ImageRessources[i].CreateMaskFromColor(sf::Color(255, 0 , 255), 0);
    }
  m_SpriteTile.SetImage(m_ImageTile);
  m_SpriteRessources.resize(TOTAL_RESOURCES);
  for (int i = 0; i < TOTAL_RESOURCES; ++i)
    m_SpriteRessources[i].SetImage(m_ImageRessources[i]);  
  m_TeamsColor.resize(gui.GetTeams().GetNbTeams());
  srand(getpid());
  
  m_SpriteEmo.resize(9);
  m_SpriteEmoticon.SetSubRect(ICONS_NORMAL);  m_SpriteEmo[0] = m_SpriteEmoticon;
  m_SpriteEmoticon.SetSubRect(ICONS_BROADCAST);  m_SpriteEmo[1] = m_SpriteEmoticon;
  m_SpriteEmoticon.SetSubRect(ICONS_SPELLCAST);  m_SpriteEmo[2] = m_SpriteEmoticon;
  m_SpriteEmoticon.SetSubRect(ICONS_ENDCAST);  m_SpriteEmo[3] = m_SpriteEmoticon;
  m_SpriteEmoticon.SetSubRect(ICONS_FORK);  m_SpriteEmo[4] = m_SpriteEmoticon;
  m_SpriteEmoticon.SetSubRect(ICONS_DROP);  m_SpriteEmo[5] = m_SpriteEmoticon;
  m_SpriteEmoticon.SetSubRect(ICONS_GET);  m_SpriteEmo[6] = m_SpriteEmoticon;
  m_SpriteEmoticon.SetSubRect(ICONS_UP);  m_SpriteEmo[7] = m_SpriteEmoticon;
  m_SpriteEmoticon.SetSubRect(ICONS_DIE);  m_SpriteEmo[8] = m_SpriteEmoticon;
  for(unsigned int i = 0; i < m_TeamsColor.size(); ++i)
    {
      std::vector<int> color(3);
      for(int x = 0; x < 3; ++x)
	color[x] = rand() % 256;
      m_TeamsColor[i] = color;
    }
  (void)gui;
}


Session*        GameSession::update(const GUI & gui)
{
  const Coordonnees& map_size(gui.GetMap().GetSizeMap());
  float zoom;

  zoom = map_size.x > map_size.y ? map_size.x : map_size.y;
  m_Camera.EventHandler(zoom);
  m_InfoBar.Refresh();
  if (gui.GetEndOfGame() == true)
    return (new EndSession(m_App, gui.GetWinnerTeam()));
  return this;
}

void            GameSession::draw(const GUI & gui)
{
  (void)gui;

  m_Camera.SetCamera();
  DisplayMap(gui.GetMap());
  DisplayPlayer(gui.GetTeams());
  m_Camera.DisplayCamera();
  m_InfoBar.Display(); 
}

void            GameSession::DisplayPlayer(const Team &team)
{
  std::map<std::string,   std::pair < std::vector<Player>,std::vector<Egg> > >::const_iterator it;
  std::vector<Player>::const_iterator it2; 
  std::vector<Egg>::const_iterator it3; 
  Coordonnees	c;
  Coordonnees	d;
  int x = 0;
  
  for( it = team.GetTeams().begin() ; it != team.GetTeams().end() ; ++it)
    {
      for(it3 = it->second.second.begin(); it3 != it->second.second.end(); ++it3)
	{
	  OrthoToIso(it3->GetPosition().x + MAP_X_ISO ,it3->GetPosition().y + MAP_Y_ISO, c);
	  c.x += (32) / 2 + 10;
	  DisplayEgg(c, it3->GetState());
	}
      for(it2 = it->second.first.begin();  it2 != it->second.first.end(); ++it2)
	{
	  if(it2->GetState() != Die)
	    {
	      m_AnimPlayer->setAnimRow(it2->GetOrientation() - 1);
	      m_AnimPlayer->stop();
	      OrthoToIso(it2->GetPosition().x + MAP_X_ISO ,it2->GetPosition().y + MAP_Y_ISO, c);
	      m_AnimPlayer->SetPosition(c.x + (32) / 2, c.y - 35);
	      m_AnimPlayer->SetColor(sf::Color(m_TeamsColor[x][0], m_TeamsColor[x][1], m_TeamsColor[x][2], 255));
	      if (m_InfoBar.GetPlayerSelected() == it2->GetId())
		{
		  m_SpriteArrow.SetPosition(c.x + 10 , c.y - 5) ;
		  m_App.Draw(m_SpriteArrow);
		}
	      m_App.Draw(*m_AnimPlayer);
	      c.x += (32) / 2 + 10;c.y -= 65;
	      DisplayPlayerState(c, it2->GetState());
	    }
	}
      x++;
    }
}

void            GameSession::DisplayPlayerState(const Coordonnees &c, const state& s)
{
  m_SpriteEmo[s].SetPosition(c.x, c.y);
  m_App.Draw(m_SpriteEmo[s]);
}

void		GameSession::DisplayEgg(const Coordonnees &c, const EggState& s)
{
  if (s == New)
    {
      m_SpriteEgg.SetPosition(c.x, c.y);
      m_App.Draw(m_SpriteEgg);
    }
  else if (s == Hatch)
    {
      m_AnimPlayer->setAnimRow(0);
      m_AnimPlayer->stop();
      m_AnimPlayer->SetPosition(c.x, c.y - 35);
      m_SpriteEmoticon.SetPosition(c.x, c.y - 65);
      m_SpriteEmoticon.SetSubRect(sf::IntRect(222, 133, 250, 160));
      m_App.Draw(m_SpriteEmoticon);
      m_App.Draw(*m_AnimPlayer);
    }
}

void            GameSession::DisplayPlayerMove(const Player &player)
{
  (void)player;
}

void            GameSession::DisplayMap(const Map &map)
{
    int w(map.GetSizeMap().x);
    int h(map.GetSizeMap().y);

    for (int x = 0; x < w; ++x)
    {
        for (int y = 0; y < h; ++y)
        {
            int x_ortho(x + MAP_X_ISO);
            int y_ortho(y + MAP_Y_ISO);
            Coordonnees	iso;

            OrthoToIso(x_ortho, y_ortho, iso);
            m_SpriteTile.SetPosition(iso.x, iso.y);
            m_App.Draw(m_SpriteTile);
            for (unsigned int type = 0; type < TOTAL_RESOURCES; ++type)
            {
                int nItems(map.GetItems(x, y, type));

                if (nItems > 0)
                {
                    m_SpriteRessources[type].SetPosition(iso.x, iso.y);
                    m_App.Draw(m_SpriteRessources[type]);
                }
            }
        }
    }
}

void GameSession::OrthoToIso(int x, int y, Coordonnees& retour) const
{
  retour.x = NB_TILE_Y * LARGEUR / 2 + x * LARGEUR / 2 + y * LARGEUR / 2;
  retour.y = x * HAUTEUR / 2 + y * -HAUTEUR / 2;
}

GameSession::~GameSession()
{
}

