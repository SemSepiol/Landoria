#ifndef MENUBUILDTOWN_H
#define MENUBUILDTOWN_H

#include <QMouseEvent>
#include <QWidget>

#include "IMenuTown.h"
#include "InformWidget.h"
#include "WidgetTownBuilding.h"
#include "WidgetTownUnit.h"
#include "../Factories/FactoryPixmap.h"
#include "../GraphicsController/IWindowGraphicsController.h"
#include "../../Controllers/Player/IMenuTownPlayer.h"
#include "../../Controllers/Player/PlayerTown.h"


class MenuBuildTown : public QWidget
{
public:
  MenuBuildTown(IMenuTown* menu_town);
  void set_geometry(QPoint pos, Size size);

  void update_inform();

  void wheel_scroll(int angle_delta);
private:
  virtual void paintEvent(QPaintEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;
  virtual void wheelEvent(QWheelEvent *event) override;

  void draw();
  void draw_scroll();

  void do_units();
  void do_buildings();
  void set_geometry_units();
  void set_geometry_buildings();

  void click(QPoint pos);
  bool point_in_rect(QRectF rect, QPoint point);
  QRect rect_build(size_t i);

  IMenuTown* menu_town;
  QPoint mouse_pos_clicked;
  int height_rect_build;
  QPoint pos_menu;
  int scroll_indent = 0;
  int width_scroll;

  std::vector<std::unique_ptr<WidgetTownBuilding>> widget_town_buildings;
  std::vector<std::unique_ptr<WidgetTownUnit>> widget_town_units;
};

#endif // MENUBUILDTOWN_H
