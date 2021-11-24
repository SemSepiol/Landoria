#ifndef WIDGETKNOWLEDGE_H
#define WIDGETKNOWLEDGE_H

#include <QMouseEvent>
#include <QWidget>

#include "../../GraphicsController/IMenuGraphicsController.h"
#include "../../../Controllers/Player/PlayerScience.h"
#include "../../../Controllers/Science.h"


class WidgetKnowledge : public QWidget
{
public:
  WidgetKnowledge(IMenuInWindowGraphicsController* graphics_controller,
                  Knowledge* knowledge, PlayerScience* player_sience);

  void set_geometry(QPoint pos, Size size);

private:
  virtual void paintEvent(QPaintEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override {Q_UNUSED(event)}
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;
  void draw();
  void click(QPoint pos);

  IMenuInWindowGraphicsController* graphics_controller;
  Knowledge* knowledge;
  PlayerScience* player_sience;

  QPoint mouse_pos_clicked;
};

#endif // WIDGETKNOWLEDGE_H
