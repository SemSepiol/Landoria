#ifndef INFORMWIDGET_H
#define INFORMWIDGET_H

#include <QPainter>
#include <QWidget>

#include "../../../IObject.h"


class InformWidget : public QWidget
{
public:
  InformWidget(QWidget* parent);

  void set_set_geometry(QPoint pos, Size size);
  void set_text(std::vector<std::pair<QString, QColor>> text);

private:
  virtual void paintEvent(QPaintEvent* event) override;

  void draw();

  std::vector<std::pair<QString, QColor>> text;
};

#endif // INFORMWIDGET_H
