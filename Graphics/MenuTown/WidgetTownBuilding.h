#ifndef WIDGETTOWNBUILDING_H
#define WIDGETTOWNBUILDING_H

#include <sstream>

#include <QMouseEvent>
#include <QWidget>

#include "AWidgetTown.h"
#include "IMenuTown.h"
#include "../Factories/FactoryString.h"
#include "../Factories/FactoryPixmap.h"
#include "../GraphicsController/IWindowGraphicsController.h"
#include "../../Controllers/Player/IMenuTownPlayer.h"
#include "../../Controllers/Player/PlayerTown.h"


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
  virtual void draw_butt() override;
  void draw_widget();
  void draw_level();
  std::vector<std::pair<QString, QColor>> text();

  IMenuTown* menu_town;
  QPoint mouse_pos_clicked;
  TownBuildings type_building;

};

#endif // WIDGETTOWNBUILDING_H
