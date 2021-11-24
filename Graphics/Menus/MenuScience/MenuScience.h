#ifndef MENUSCIENCE_H
#define MENUSCIENCE_H

#include <QMouseEvent>
#include <QWidget>

#include "WidgetKnowledge.h"
#include "../../GraphicsController/IMenuGraphicsController.h"
#include "../../../Controllers/Player/PlayerScience.h"
#include "../../../Controllers/Science.h"

class MenuScience : public QWidget
{
  size_t n = 10;
  size_t m = 5;

public:
  MenuScience(IMenuInWindowGraphicsController* graphics_controller,
              PlayerScience* player_science);

  void set_geometry(QPoint pos, Size size);

private:
  virtual void paintEvent(QPaintEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override {Q_UNUSED(event)}
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;
  virtual void wheelEvent(QWheelEvent *event) override;

  void update_information();
  void draw();
  void draw_scroll();
  void click(QPoint pos);
  void set_geometry_widgets();

  int end_widgets();
  QRect rect_but_close() const;
  bool point_in_rect(QRectF rect, QPoint point);

  IMenuInWindowGraphicsController* graphics_controller;
  PlayerScience* player_science;

  std::vector<std::vector<std::unique_ptr<WidgetKnowledge>>> knowledges;

  QPoint mouse_pos_clicked;

  int init_space_x;
  int init_space_y;
  int space_x;
  int space_y;
  Size size_block;
  int indent_x = 0;
  int scroll_height;
};


#endif // MENUSCIENCE_H
