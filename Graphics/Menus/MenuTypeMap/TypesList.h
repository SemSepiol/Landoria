#ifndef TYPESLIST_H
#define TYPESLIST_H

#include <QMouseEvent>
#include <QPainter>
#include <QWidget>

#include "IMenuTypeMap.h"
#include "../../../IObject.h"


class TypesList : public QWidget
{
public:
  TypesList(IMenuTypeMap* menu_type_map);

  void set_text(std::vector<QString> text);
  void set_geometry(QPoint pos, Size size_block);

private:
  virtual void paintEvent(QPaintEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override {Q_UNUSED(event)}
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;

  void draw();
  void click(QPoint pos);

  QRect rect_str(int i);

  std::vector<QString> strings;
  Size size_block;
  IMenuTypeMap* menu_type_map;
  QPoint mouse_pos_clicked;
};

#endif // TYPESLIST_H
