#ifndef UNITINFORMATION_H
#define UNITINFORMATION_H

#include <sstream>
#include <QWidget>
#include "../Units/Unit.h"
#include "../Factories/FactoryPixmap.h"

class UnitInformation : public QWidget
{
public:
  UnitInformation(QWidget* win, class Unit* unit);

  //width = height*2
  virtual void set_geometry(QPoint pos, int height);
private:
  virtual void paintEvent(QPaintEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override {Q_UNUSED(event)}
  virtual void mousePressEvent(QMouseEvent *event) override {Q_UNUSED(event)}
  virtual void mouseReleaseEvent(QMouseEvent *event) override {Q_UNUSED(event)}

  void draw();
  class Unit* unit;
};

#endif // UNITINFORMATION_H
