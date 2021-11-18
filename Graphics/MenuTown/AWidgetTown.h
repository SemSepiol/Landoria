#ifndef AWIDGETTOWN_H
#define AWIDGETTOWN_H

#include <QMouseEvent>
#include <QWidget>
#include <QPainter>

#include "../Factories/FactoryPixmap.h"

class AWidgetTown : public QWidget
{
public:
  enum TypeWidget{
    ForUnit,
    ForBuilding
  };

  enum TypeWork{
    Build,
    InQueue,
    AlreadyBuild
  };

  AWidgetTown(QWidget* win, TypeWork type_widget);
  virtual TypeWidget who_i() const = 0;

protected:
  virtual void draw_butt();
  void draw_enable();
  QRect rect_butt_del();
  QRect rect_butt_up();
  QRect rect_butt_down();
  QRect rect_pic();
  bool point_in_rect(QRectF rect, QPoint point) const;

  virtual size_t num_from_queue() = 0;
  virtual size_t count_from_queue() = 0;

  TypeWork type_widget;
  bool enable = true;
};

#endif // AWIDGETTOWN_H
