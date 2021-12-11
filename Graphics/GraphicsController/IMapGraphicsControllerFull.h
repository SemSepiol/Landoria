#ifndef IMAPGRAPHICSCONTROLLERFULL_H
#define IMAPGRAPHICSCONTROLLERFULL_H

#include "IMapGraphicsController.h"
#include "../Map/Map.h"
#include "../Minimap.h"

class IMapGraphicsControllerFull : public IMapGraphicsController, public IMiniMapGraphicsController
{
public:
  virtual void move_map(double coeffx, double coeffy) = 0;
  virtual void move_map(QPoint move_point) = 0;
  virtual void resize_map(double coefficient, QPoint pos_mouse) = 0;
  virtual void no_highlight_unit(class Unit* unit, Position pos) = 0;

  virtual Map* get_map() = 0;
  virtual Minimap* get_minimap() = 0;
};

#endif // IMAPGRAPHICSCONTROLLERFULL_H
