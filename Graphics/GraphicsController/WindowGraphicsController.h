#ifndef WINDOWGRAPHICSCONTROLLER_H
#define WINDOWGRAPHICSCONTROLLER_H

#include "IGraphicsController.h"
#include "IWindowGraphicsController.h"


class WindowGraphicsController : public IWindowGraphicsControllerFull
{
public:
  WindowGraphicsController(IGraphicsController* graphics_controller);

  virtual Size size_win() const override;

  virtual void draw_elements() override;
  virtual void move_map(QPoint move_point) override;
  virtual void resize_map(double coefficient, QPoint pos_mouse) override;
  virtual void click(QPoint pos) override;
  virtual void start_check_move_unit() override;
  virtual void stop_check_move_unit(QPoint mouse_pos) override;
  virtual void move_mouse(QPoint new_pos) override;
  virtual void press_enter() override;
  virtual void press_escape() override;

  virtual int map_upper_edge() const override;
  virtual int map_bottom_edge() const override;

  virtual void start_check_move_unit(class Unit* unit) override;
  virtual void stop_check_move_unit() override;

  void set_win_settings();
  GameWindow* get_window();
  void do_window();

private:
  Map* map();

  void unit_moved_to_cell(Cell* cell);
  Size& _size_win();
  IGameForGraphic* game_controller() const;
  DrawWay* drawway() const;
  std::unique_ptr<GameWindow> game_window;

  IGraphicsController* graphics_controller;
};

#endif // WINDOWGRAPHICSCONTROLLER_H
