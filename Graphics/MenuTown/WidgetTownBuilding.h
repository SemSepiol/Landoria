#ifndef WIDGETTOWNBUILDING_H
#define WIDGETTOWNBUILDING_H

#include <sstream>
#include <QMouseEvent>
#include <QWidget>

#include "../../Controllers/Player/IMenuTownPlayer.h"
#include "../GraphicsController/IGraphicsController.h"
#include "../../Controllers/Player/PlayerTown.h"
#include "../Factories/FactoryPixmap.h"
#include "../Factories/FactoryString.h"
#include "IMenuTown.h"
#include "AWidgetTown.h"

class WidgetTownBuilding : public AWidgetTown
{
public:
  WidgetTownBuilding(IMenuTown* menu_town, TownBuildings type_building, TypeWork type_widget);
  void set_geometry(QPoint pos, Size size);

  virtual TypeWidget who_i() const override{ return ForBuilding; }

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
  TownBuildings type_building;

};

#endif // WIDGETTOWNBUILDING_H
