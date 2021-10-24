#ifndef MENUBUILDTOWN_H
#define MENUBUILDTOWN_H

#include <QMouseEvent>
#include <QWidget>

#include "../../Controllers/Player/IMenuTownPlayer.h"
#include "../GraphicsController/IGraphicsController.h"
#include "../../Controllers/Player/PlayerTown.h"
#include "../Factories/FactoryPixmap.h"
#include "IMenuTown.h"
#include "WidgetTownBuilding.h"
#include "WidgetTownUnit.h"

class MenuBuildTown : public QWidget
{
public:
  MenuBuildTown(IMenuTown* menu_town);
  void set_geometry(QPoint pos, Size size);
private:
  virtual void paintEvent(QPaintEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override {Q_UNUSED(event)}
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;

  void draw();
  void set_geometry_unit();
  void set_geometry_building();
  void click(QPoint pos);
  bool point_in_rect(QRectF rect, QPoint point);
  QRect rect_build(size_t i);

  IMenuTown* menu_town;
  QPoint mouse_pos_clicked;
  int height_rect_build;
  QPoint pos_menu;

  std::vector<std::unique_ptr<WidgetTownBuilding>> widget_town_building;
  std::vector<std::unique_ptr<WidgetTownUnit>> widget_town_units;
};

#endif // MENUBUILDTOWN_H
