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

class AMenuForUnit : public QWidget
{
public:
  AMenuForUnit(QWidget* widget, IGraphicsControllerMenuForUnit* graphics_controller, class Unit* unit);
  virtual void set_geometry(QPoint pos, int side_square);
  virtual void draw();
  virtual int count_button() const = 0;

  virtual void paintEvent(QPaintEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override {Q_UNUSED(event)}
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;

protected:
  virtual Event* what_butt(int num_butt) = 0;
  virtual void click_butt(int num_butt);

  int side_square;
  QPoint mouse_pos_clicked;
  IGraphicsControllerMenuForUnit* graphics_controller;
  class Unit* unit;
private:
  bool point_in_rect(QRectF rect, QPoint point);

  // начиная сверху, относительно левого верхнего угла
  QRectF rect_butt(int i);
};

#endif // AMENUFORUNIT_H
