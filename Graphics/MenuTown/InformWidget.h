#ifndef INFORMWIDGET_H
#define INFORMWIDGET_H

#include <QWidget>
#include <QPainter>

#include "../../IObject.h"

class InformWidget : public QWidget
{
public:
  InformWidget(QWidget* parent);

  void set_set_geometry(QPoint pos, Size size);
  void set_text(QString text);

private:
  virtual void paintEvent(QPaintEvent* event) override;

  void draw();

  QString text;
};

#endif // INFORMWIDGET_H
