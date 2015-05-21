#ifndef _GAMESESSION
#define _GAMESESSION
# include <SFML/Graphics.hpp>
# include <map>
# include "Session.hpp"
# include "GUI.hpp"
# include "Player.hpp"
# include "Map.hpp"
# include "Camera.hpp"
# include "GameInfoBar.hpp"
# include "Anim.hpp"
# include "ImgAnim.hpp"
# include "LayerAnim.hpp"
# include "Layer.hpp"
# include "PausableClock.hpp"
# include <SFML/Window.hpp>
# include "Egg.hpp"

#define ICONS_NORMAL sf::IntRect(0, 0, 0, 0)
#define ICONS_BROADCAST sf::IntRect(79, 222, 106, 250)
#define ICONS_SPELLCAST sf::IntRect(192, 132, 218, 159)
#define ICONS_ENDCAST sf::IntRect(335, 72, 362, 100)
#define ICONS_FORK sf::IntRect(192, 102, 219, 128)
#define ICONS_DROP sf::IntRect(194, 15, 219, 38)
#define ICONS_GET sf::IntRect(278, 12, 306, 40)
#define ICONS_UP sf::IntRect(52, 223, 76, 250)
#define ICONS_DIE sf::IntRect(166, 192, 190, 216)
#define HAUTEUR 32
#define LARGEUR 64
#define NB_TILE_Y 10


class GameSession : public Session
{
public:
  GameSession(const GUI &, sf::RenderWindow &App);
  virtual			~GameSession();
  virtual Session		*update(const GUI &gui);
  virtual void			draw(const GUI &gui);
  void				initialize();
private:
  void				DisplayMap(const Map &map);
  void				DisplayPlayer(const Team &team);
  void				DisplayPlayerState(const Coordonnees &coo,const state& s);
  void				DisplayPlayerMove(const Player &player);
  void				DisplayEgg(const Coordonnees &coo,const EggState& s);
  void OrthoToIso(int, int, Coordonnees&) const;
private:
  sf::RenderWindow		&m_App;
  Camera			m_Camera;
  GameInfoBar			m_InfoBar;
  ImgAnim			*m_AnimPlayer;
  sf::Image			m_ImagePlayer;
  sf::Image			m_ImageEmoticon;
  sf::Image			m_ImageEgg;
  sf::Image			m_ImageArrow;
  sf::Sprite			m_SpriteArrow;
  sf::Sprite			m_SpriteEgg;
  sf::Sprite			m_SpriteEmoticon;
  sf::Sprite			m_SpriteTile;
  std::vector<sf::Sprite>	m_SpriteEmo;
  std::vector<sf::Sprite>	m_SpriteRessources;
  std::vector<sf::Image>	m_ImageRessources;
  std::vector<std::vector<int> >m_TeamsColor;
  sf::Image			m_ImageTile;
  sf::String			m_Text;
};


#endif
