#ifndef LAYERANIM_H
#define LAYERANIM_H
 
#include "Anim.hpp"
#include "Layer.hpp"
 
/*
 *Animation où chaque frame est repésenter par une couche de Layer.
 */
class LayerAnim :
public Anim, public Layer
{
 public:
  LayerAnim(void);
 
  //!Retourne le nombre de frame de l'animation
  virtual unsigned int getSize() const;
 
 protected:
  virtual void Render(sf::RenderTarget& Target) const;
};
 
#endif
