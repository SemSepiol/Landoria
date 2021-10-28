#ifndef WIDGETTOWNUNIT_H
#define WIDGETTOWNUNIT_H

#include <QMouseEvent>
#include <QWidget>

#include "../../Controllers/Player/IMenuTownPlayer.h"
#include "../GraphicsController/IGraphicsControllerFor.h"
#include "../../Controllers/Player/PlayerTown.h"
#include "../Factories/FactoryPixmap.h"
#include "../Factories/FactoryString.h"
#include "IMenuTown.h"
#include "AWidgetTown.h"

class WidgetTownUnit : public AWidgetTown
{
public:
  WidgetTownUnit(IMenuTown* menu_town, Units type_unit, TypeWork type_widget);
  void set_geometry(QPoint pos, Size size);

  virtual TypeWidget who_i() const override{ return ForUnit; }

protected:
  virtual size_t num_from_queue() override;
  virtual size_t count_from_queue() override;

private:
  virtual void paintEvent(QPaintEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;
  virtual void wheelEvent(QWheelEvent *event) override;

  void draw();
  QString text();

  IMenuTown* menu_town;
  QPoint mouse_pos_clicked;
  Units type_unit;
};

#endif // WIDGETTOWNUNIT_H
