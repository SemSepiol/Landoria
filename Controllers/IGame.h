#ifndef IGAME_H
#define IGAME_H

#include "../IObject.h"
#include "../Graphics/GraphicsController/IWindowGraphicsController.h"
#include "../Graphics/GraphicsController/IPlayerGraphicsController.h"
#include "Player/IPlayer.h"

class IGameForWidget : public IObject
{
public:
  virtual void start_move() = 0;
  virtual QWidget* window() const = 0;
};

class IGameForGraphic : public IObject
{
public:
  virtual size_t count_cell_x() const = 0;
  virtual size_t count_cell_y() const = 0;
  virtual int width_win() const = 0;
  virtual int height_win() const = 0;
  virtual void exit() = 0;
  virtual void next_move() = 0;
  virtual IPlayer* current_player() const = 0;
  virtual IGameForWidget* igame_for_widget() = 0;
  virtual void start_move() = 0;
};

class IGameForPlayer : public IObject
{
public:
  virtual IPlayerGraphicsController* graphics_controller() const = 0;
  virtual size_t count_cell_x() const = 0;
  virtual size_t count_cell_y() const = 0;
};

#endif // IGAME_H
