#ifndef GRAPHICSCONTROLLER_H
#define GRAPHICSCONTROLLER_H

#include <memory>

#include "AGraphicsController.h"
#include "../Units/Unit.h"
#include "EventsStructures.h"
#include "../Cell.h"
#include "../Minimap.h"
#include "../../Controllers/FindUnitWay.h"
#include "../DrawWay.h"
#include "../MenuTown/MenuTown.h"
#include "../InformationWidgets/UnitInformation.h"
#include "../../Controllers/Player/IMenuTownPlayer.h"
#include "../InformationWidgets/StartMoveInform.h"
#include "PlayerGraphicsController.h"

class GraphicsController : public AGraphicsController,
    public IUnitMenuGraphicsController
{
public:
  GraphicsController(IGameForGraphic* game_controller);

  void do_start_inform(QString string);
  void del_start_inform();

  virtual void press_enter() override;

  virtual void create_elements() override;

  virtual void start_check_move_unit() override;
  virtual void stop_check_move_unit(QPoint mouse_pos) override;
  virtual void move_mouse(QPoint new_pos) override;
  virtual void click(QPoint pos) override;

  virtual void draw_elements() override;
  virtual void move_map(QPoint move_point) override;
  virtual void resize_map(double coefficient, QPoint pos_mouse) override;

  /*
   * coeffx = new_map_center.x / width_map
   * coeffy = new_map_center.y / height_map
  */
  virtual void move_map(double coeffx, double coeffy) override;

  virtual void menu_unit_event(class Unit* unit, Event* event) override;

  virtual void delete_townmenu() override;
  virtual void show_minimap() override;
  virtual void next_move() override;

  virtual void do_inform_widget(std::vector<std::pair<QString, QColor>> text) override;
  virtual void del_inform_widget() override;

  virtual bool& get_is_tracking_unit() override;
  virtual bool& get_is_moving_unit() override;
  virtual class Unit*& get_tracking_unit() override;
  virtual Position& get_pos_tracking_unit() override;

  virtual int& get_side_square_unit_menu() override;
  virtual int& get_hexagon_side_minimap() override;

  virtual DrawWay* get_drawway() override;

  virtual AMenuForUnit* get_unit_menu() override;
  virtual void set_unit_menu(AMenuForUnit* unit_menu) override;

  virtual UnitInformation* get_unit_information() override;
  virtual void set_unit_information(UnitInformation* unit_information) override;

  virtual MenuTown* get_town_menu() override;
  virtual void set_town_menu(MenuTown*) override;

  virtual Minimap* get_minimap();

  virtual StartMoveInform* get_start_move_inform() override;

  virtual IUnitMenuGraphicsController* get_iunit_menu_gc() override;
  virtual ITownMenuGraphicsController* get_itown_menu_gc() override;
  virtual IPlayerGraphicsController* get_iplayer_gc() override;

private:
  void create_minimap();
  void set_win_rect_minimap();
  void no_highlight_unit(class Unit* unit, Position pos);

  void start_check_move_unit(class Unit* unit);
  void stop_check_move_unit();
  void del_menu_unit();
  void unit_moved_to_cell(Cell* cell);

  bool is_tracking_unit = false;
  bool is_moving_unit = false;
  class Unit* tracking_unit = nullptr;
  Position pos_tracking_unit;

  int side_square_unit_menu;
  int hexagon_side_minimap;

  Cell* click_cell = nullptr;
  std::unique_ptr<DrawWay> drawway{nullptr};
  std::unique_ptr<AMenuForUnit> unit_menu{nullptr};
  std::unique_ptr<UnitInformation> unit_information{nullptr};
  std::unique_ptr<MenuTown> town_menu{nullptr};
  std::unique_ptr<Minimap> minimap;
  std::unique_ptr<StartMoveInform> start_move_inform;

  std::unique_ptr<PlayerGraphicsController> player_gc;
};

#endif // GRAPHICSCONTROLLER_H
