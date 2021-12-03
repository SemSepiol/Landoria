#ifndef MENUGRAPHICSCONTROLLER_H
#define MENUGRAPHICSCONTROLLER_H

#include "IGraphicsController.h"
#include "IMenuGraphicsControllerFull.h"
#include "../Menus/MenuInWindow/MenuLists.h"
#include "../Menus/MenuInWindow/OpenMenuLists.h"
#include "../Menus/MenuScience/MenuScience.h"
#include "../Menus/MenuTypeMap/MenuTypeMap.h"

class MenuGraphicsController : public IMenuGraphicsControllerFull
{
public:
  MenuGraphicsController(IGraphicsController* graphics_controller);

  virtual QWidget* window() const override;
  virtual void move_map(QPoint move_point) override;
  virtual void exit() override;
  virtual void show_minimap() override;
  virtual void next_move() override;

  virtual void menu_unit_event(class Unit* unit, Event* event) override;

  virtual void delete_townmenu() override;
  virtual void do_inform_widget(std::vector<std::pair<QString, QColor>> text) override;
  virtual void del_inform_widget() override;

  virtual void open_menu_lists() override;
  virtual void close_menu_lists() override;

  virtual void open_menu_science() override;
  virtual void close_menu_science() override;

  virtual void event_open_menu_type_map() override;
  virtual void click_open_menu_type_map() override;
  virtual void open_menu_type_map() override;
  virtual void close_menu_type_map() override;
  virtual void set_type_map(TypeMap type_map) override;

  virtual PlayerScience* player_science() override;

  void create_elements();
  void create_uppermenu();
  void create_bottommenu();
  void create_menu_lists();
  virtual void del_menu_unit() override;
  virtual void press_escape() override;
  virtual BottomMenu* get_bottom_menu() override;
  virtual UpperMenu* get_upper_menu() override;
private:
  Map* map();
  IGraphicsController* graphics_controller;

  Size size_open_menu_lists;
  Size size_menu_lists;

  std::unique_ptr<UpperMenu> upper_menu;
  std::unique_ptr<BottomMenu> bottom_menu;
  std::unique_ptr<OpenMenuLists> wid_open_menu_lists;
  std::unique_ptr<MenuLists> menu_lists;
  std::unique_ptr<MenuScience> menu_science;
  std::unique_ptr<MenuTypeMap> menu_type_map;
};

#endif // MENUGRAPHICSCONTROLLER_H
