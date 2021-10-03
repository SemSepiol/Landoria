#ifndef AMENUFORUNIT_H
#define AMENUFORUNIT_H

#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QPainter>

#include "../Units/Unit.h"
//#include "../../Controllers/IPlayer.h"
#include "../GraphicsController/EventsStructures.h"
#include "../GraphicsController/IGraphicsController.h"
#include "../Factories/FactoryPixmap.h"
#include "../Cell.h"

class AMenuForUnit : public QWidget
{
public:
  AMenuForUnit(QWidget* widget, IGraphicsControllerMenuForUnit* graphics_controller,
               class Unit* unit, Cell* cell);
  virtual void set_geometry(QPoint pos, int side_square);
  virtual void draw();

  virtual void paintEvent(QPaintEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override {Q_UNUSED(event)}
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;
  virtual int count_button() const;
protected:
  virtual void click_butt(size_t num_butt);

  int side_square;
  QPoint mouse_pos_clicked;
  IGraphicsControllerMenuForUnit* graphics_controller;
  class Unit* unit;
  Cell* cell;
  std::vector<Event*> buttons;
private:
  bool point_in_rect(QRectF rect, QPoint point);
  // начиная сверху, относительно левого верхнего угла
  QRectF rect_butt(size_t i);
};

#endif // AMENUFORUNIT_H
