#ifndef MINIMAP_H
#define MINIMAP_H

#include <QPainter>
#include <QWidget>

#include "GraphicsController/Calculations.h"
#include "GraphicsController/IWindowGraphicsController.h"
#include "Map/Cell.h"
#include "Map/Map.h"
#include "../Controllers/Enums.h"


class Minimap : public QWidget
{
  const QPoint pos_corner_map{0,0};

public:
  Minimap(QWidget* win, Map* map, IMiniMapGraphicsController* graphics_controller);

  void set_geometry(QPoint pos, int hexagon_side);
  void draw();

  // ставит прямоугольник изображающий где находиться карта относительно окна
  // прямоугольник - окно
  // coeffx = map_center.x / width_map
  // coeffy = map_center.y / height_map
  // coeff_width = width_win_map / width_map
  // coeff_height = height_win_map / height_map
  void set_win_rect(double coeffx, double coeffy, double coeff_width, double coeff_height);

  bool is_enable() const;

  virtual void show();
  virtual void hide();
private:
  virtual void paintEvent(QPaintEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override {Q_UNUSED(event)}
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override {Q_UNUSED(event)}


  QPoint point_of_cell(Position pos);
  void draw_cell(QPoint bottomright, Cell* cell);
  QColor color(Cell* cell);
  void do_size();

  QRectF win_on_map{};
  IMiniMapGraphicsController* graphics_controller;
  Map* map;
  Calculations calc;
  int width_minimap;
  int height_minimap;

  bool enable = false;
};

#endif // MINIMAP_H
