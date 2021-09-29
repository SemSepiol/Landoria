#ifndef UPPERMENU_H
#define UPPERMENU_H

#include <memory>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
//#include <QStyleOptionButton>

#include "AMenu.h"
#include "../GraphicsController/IGraphicsController.h"

class UpperMenu : public QWidget
{
public:
  explicit UpperMenu(IGraphicsControllerForUpperMenu* graphic_controller);
  virtual ~UpperMenu() override;
  virtual void set_geometry(QPoint pos, int width, int height);
  virtual void paintEvent(QPaintEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override {Q_UNUSED(event)}
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;
  virtual void draw();

private:
  QRect exit_butt() const;

  bool point_in_rect(QRectF rect, QPoint point);

  int width_menu;
  int height_menu;
  QPoint pos;
  IGraphicsControllerForUpperMenu* graphic_controller;

  QPoint mouse_pos_clicked;
};

#endif // UPPERMENU_H
