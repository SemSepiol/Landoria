#ifndef MENUTOWN_H
#define MENUTOWN_H

#include <memory>

#include "IMenuTown.h"
#include "../../Controllers/Player/IMenuTownPlayer.h"
#include "../GraphicsController/IGraphicsController.h"
#include "../../Controllers/Player/PlayerTown.h"
#include "MenuBuildTown.h"
#include "MenuTypeWorkTown.h"
#include "MenuQueueTown.h"
#include "InformWidget.h"

class MenuTown : public IMenuTown
{
public:  
  MenuTown(IMenuTownPlayer* player, ITownMenuGraphicsController* graphics_controller, PlayerTown* town);
  void set_geometry(QPoint pos, Size size);
  void start();

  virtual ITownMenuGraphicsController* graphics_controller() const override;
  virtual QWidget* window() const override;
  virtual PlayerTown* town() const override;
  virtual IMenuTownPlayer* player() const override;
  virtual void delete_townmenu() override;
  virtual void open_menu_build() override;
  virtual void open_menu_alreadybuild() override;

  virtual void set_build(Units type_unit) override;
  virtual void set_build(TownBuildings type_building) override;
  virtual void del_build_from_queue(AWidgetTown* wid_build) override;
  virtual size_t num_from_queue(AWidgetTown* wid) const override;
  virtual size_t count_from_queue() const override;
  virtual void move_up_build(AWidgetTown* wid) override;
  virtual void move_down_build(AWidgetTown* wid) override;
  virtual void wheel_scroll(int angle_delta) override;
  virtual void do_inform_widget(QString text) override;
  virtual void del_inform_widget() override;

  void set_type_work(TypeWork _type_work) override;
private:
  void close_menu_build();
  void close_menu_alreadybuild();
  void close_menu_queue();

  void set_geometry_menu_build();
  void set_geometry_menu_selectwork();
  void set_geometry_menu_queue();

  IMenuTownPlayer* _player;
  ITownMenuGraphicsController* _graphics_controller;
  PlayerTown* _town;

  std::unique_ptr<MenuBuildTown> menu_build_town;
  std::unique_ptr<MenuTypeWorkTown> menu_type_work_town;
  std::unique_ptr<MenuQueueTown> menu_queue_town;
  std::unique_ptr<InformWidget> inform_widget;

  QPoint pos;
  Size size;

  TypeWork type_work = TypeWork::AddQueue;
};

#endif // MENUTOWN_H
