#ifndef UPPERMENU_H
#define UPPERMENU_H

#include <memory>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
//#include <QStyleOptionButton>

#include "IMenu.h"
#include "../GraphicsController/IGraphicsController.h"

class UpperMenu : public QWidget
{
public:
  explicit UpperMenu(IGraphicsForUpperMenu* graphic_controller);
  virtual ~UpperMenu();
  void set_size();
  virtual void paintEvent(QPaintEvent* event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;

public slots:
  void click_exit();

private:
  void draw();

  QRect exit_butt() const;

  bool point_in_rect(QRectF rect, QPoint point);

  int width_menu;
  int height_menu;
  IGraphicsForUpperMenu* graphic_controller;
};

#endif // UPPERMENU_H
