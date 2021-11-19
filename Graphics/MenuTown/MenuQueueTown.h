#ifndef MENUQUEUETOWN_H
#define MENUQUEUETOWN_H

#include <string>

#include <QMouseEvent>
#include <QWidget>

#include "IMenuTown.h"
#include "WidgetTownBuilding.h"
#include "WidgetTownUnit.h"
#include "../Factories/FactoryPixmap.h"
#include "../GraphicsController/IWindowGraphicsController.h"
#include "../../Controllers/Player/IMenuTownPlayer.h"
#include "../../Controllers/Player/PlayerTown.h"


class MenuQueueTown : public QWidget
{
  struct WidgetTownBuild{
    enum TypeBuild{
      Building,
      Unit
    };
    std::unique_ptr<WidgetTownBuilding> wid_town_building;
    std::unique_ptr<WidgetTownUnit> wid_town_unit;
    TypeBuild type_build;

    WidgetTownBuild(WidgetTownBuilding* _wid_town_building)
      :wid_town_building{_wid_town_building}, type_build{Building}
    {}

    WidgetTownBuild(WidgetTownUnit* _wid_town_unit)
      :wid_town_unit{_wid_town_unit}, type_build{Unit}
    {}
  };

public:
  MenuQueueTown(IMenuTown* menu_town);
  void set_geometry(QPoint pos, Size size);
  void update_queue();

  size_t num_widget(AWidgetTown* wid_building) const;
  size_t count_widgets() const;
private:
  virtual void paintEvent(QPaintEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;

  void draw();
  void draw_number();
  void draw_butt_queue();
  void click(QPoint pos);
  bool point_in_rect(QRect rect, QPoint point);
  void set_geometry_wid(size_t ind);
  QRect rect_butt_queue() const;
  QRect rect_text_butt_queue() const;

  IMenuTown* menu_town;
  QPoint mouse_pos_clicked;
  int height_rect_build;
  int height_butt_queue;
  int height_text_queue;
  QPoint pos_menu;
  std::vector<WidgetTownBuild> widgets_town_build;
  Size numder_rect;
};
#endif // MENUQUEUETOWN_H
