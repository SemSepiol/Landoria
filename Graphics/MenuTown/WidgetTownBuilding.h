#ifndef WIDGETTOWNBUILDING_H
#define WIDGETTOWNBUILDING_H

#include <sstream>
#include <QMouseEvent>
#include <QWidget>

#include "../../Controllers/Player/IMenuTownPlayer.h"
#include "../GraphicsController/IGraphicsController.h"
#include "../../Controllers/Player/PlayerTown.h"
#include "../../Controllers/TownBuildNeeds.h"
#include "../Factories/FactoryPixmap.h"
#include "../Factories/FactoryString.h"
#include "IMenuTown.h"

class WidgetTownBuilding : public QWidget
{
public:
  enum Type{
    Build,
    InQueue,
    AlreadyBuild
  };

  WidgetTownBuilding(IMenuTown* menu_town, TownBuildings type_building, Type type_widget);
  void set_geometry(QPoint pos, Size size);
private:
  virtual void paintEvent(QPaintEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override {Q_UNUSED(event)}
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;

  void draw();

  IMenuTown* menu_town;
  QPoint mouse_pos_clicked;
  TownBuildings type_building;
  Type type_widget;
};

#endif // WIDGETTOWNBUILDING_H
