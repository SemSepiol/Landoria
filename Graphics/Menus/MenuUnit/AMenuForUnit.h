#ifndef AMENUFORUNIT_H
#define AMENUFORUNIT_H

#include <memory>

#include <QMouseEvent>
#include <QPainter>
#include <QPoint>
#include <QWidget>

#include "../../Factories/FactoryPixmap.h"
#include "../../GraphicsController/EventsStructures.h"
#include "../../GraphicsController/IMenuGraphicsController.h"
#include "../../GraphicsController/IPlayerGraphicsController.h"
#include "../../Map/Cell.h"
#include "../../Units/Unit.h"
#include "../../../Controllers/Player/IPlayer.h"


struct MyButton
{
  std::unique_ptr<Event> event;
  bool is_enable = true;
  MyButton(Event* _event)
    :event{_event} {}
};

class AMenuForUnit : public QWidget
{
public:
  AMenuForUnit(QWidget* win, IUnitMenuGraphicsController* graphics_controller,
               PlayerUnit* unit, Cell* cell);
  virtual void set_geometry(QPoint pos, int side_square);
  virtual void draw();

  virtual void paintEvent(QPaintEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override {Q_UNUSED(event)}
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;
  virtual int count_button() const;
protected:
  virtual void click_butt(size_t num_butt);
  virtual void draw_butt(size_t num_butt);
  virtual QRectF rect_butt(size_t i);
  virtual void set_buttons();

  int side_square;
  QPoint pos_menu;
  QPoint mouse_pos_clicked;
  IUnitMenuGraphicsController* graphics_controller;
  PlayerUnit* unit;
  Cell* cell;
  std::vector<MyButton> buttons;
  QWidget* win;

  bool has_move_event = false;
private:
  bool point_in_rect(QRectF rect, QPoint point);
  // начиная сверху, относительно левого верхнего угла

};

#endif // AMENUFORUNIT_H
