#ifndef STARTMENU_H
#define STARTMENU_H

#include <QMouseEvent>
#include <QWidget>

#include "../../../IObject.h"
#include "../../GraphicsController/IMenuStartGraphicsController.h"

class StartMenu : public QWidget
{
public:
  StartMenu(IMenuStartGraphicsController* graphics_controller);

  void set_geometry(QPoint pos, Size size);

private:
  virtual void paintEvent(QPaintEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override {Q_UNUSED(event)}
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;

  void draw();
  void click(QPoint pos);

  IMenuStartGraphicsController* graphics_controller;

  QPoint mouse_pos_clicked;
};

#endif // STARTMENU_H
