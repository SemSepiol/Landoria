#ifndef MENUTYPEMAP_H
#define MENUTYPEMAP_H

#include <QMouseEvent>
#include <QWidget>

#include "../../GraphicsController/IMenuGraphicsController.h"
#include "../../Map/IMap.h"


class MenuTypeMap : public QWidget
{
public:
  MenuTypeMap(IMenuInWindowGraphicsController* graphics_controller, IMap* map);

  void set_geometry(QPoint pos, Size size);

private:
  virtual void paintEvent(QPaintEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override {Q_UNUSED(event)}
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;

  void draw();
  void click(QPoint pos);

  QRect text_overlay() const;
  QRect wid_overlay() const;
  QRect text_icons() const;
  QRect wid_icons() const;
  QRect text_notvisible() const;
  QRect wid_notvisible() const;
  int rad_wid_notvisible() const;
  QRect text_other_landscapes() const;
  QRect wid_other_landscapes() const;
  int rad_wid_other_landscapes() const;

  IMenuInWindowGraphicsController* graphics_controller;
  IMap* map;
  QPoint mouse_pos_clicked;
};

#endif // MENUTYPEMAP_H
