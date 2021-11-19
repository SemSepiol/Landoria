#ifndef STARTMOVEINFORM_H
#define STARTMOVEINFORM_H

#include <QKeyEvent>
#include <QMouseEvent>
#include <QWidget>

#include "../../Controllers/IGame.h"


class StartMoveInform : public QWidget
{
public:
  StartMoveInform(IGameForWidget* game, QString string, QPoint point);
  void set_geometry(QPoint pos, Size size);

private:
  virtual void paintEvent(QPaintEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override {Q_UNUSED(event)}
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;

  void draw();
  QRect rect_butt() const;
  int indentation_butt() const;
  bool point_in_rect(QRectF rect, QPoint point);

  IGameForWidget* game_controller;
  QString string;
  QPoint point;
  bool resized = false;
  QPoint mouse_pos_clicked{-1,-1};
};

#endif // STARTMOVEINFORM_H
