#ifndef MAPGRAPHICSCONTROLLER_H
#define MAPGRAPHICSCONTROLLER_H

#include "CreateMap.h"
#include "IGraphicsController.h"
#include "IMapGraphicsControllerFull.h"


class MapGraphicsController : public IMapGraphicsControllerFull
{
public:
  MapGraphicsController(IGraphicsController* graphics_controller);

  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;

  virtual size_t count_cell_x() const override;
  virtual size_t count_cell_y() const override;

  virtual Size size_map() const override;
  virtual Size size_win_map() const  override;
  virtual QPoint win_map_center() const override;
  virtual QPoint map_center() const override;

  virtual void move_map(double coeffx, double coeffy) override;

  // Возвращает центр кары относительно центра окна карты
  QPoint map_center_in_win_map();

  void control_pos_map();
  void set_win_rect_minimap();

  virtual void move_map(QPoint move_point) override;
  virtual void resize_map(double coefficient, QPoint pos_mouse) override;
  void do_size_map();

  void create_map();
  void create_minimap();
  virtual void no_highlight_unit(class Unit* unit, Position pos) override;
  virtual Map* get_map() override;
  virtual Minimap* get_minimap() override;
private:
  Size size_win() const;

  Size& _size_map();
  Size& _size_win_map();
  QPoint& _win_map_center();
  QPoint& _map_center();

  std::unique_ptr<Calculations> calc;
  std::unique_ptr<Map> map;
  std::unique_ptr<Minimap> minimap;

  IGraphicsController* graphics_controller;
};


#endif // MAPGRAPHICSCONTROLLER_H
