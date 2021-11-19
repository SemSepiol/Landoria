#include "MenuTown.h"
#include "iostream"

MenuTown::MenuTown(IMenuTownPlayer* player, ITownMenuGraphicsController* graphics_controller,
                   PlayerTown* town)
  : _player{player}, _graphics_controller{graphics_controller}, _town{town},
    menu_build_town{new MenuBuildTown(this)}, menu_type_work_town{new MenuTypeWorkTown{this}},
    menu_queue_town{new MenuQueueTown(this)}
{
  if(town->get_build_queue().size() > 1)
    type_work = AddQueue;
}

void MenuTown::set_geometry(QPoint _pos, Size _size)
{
  pos = _pos;
  size = _size;
  if(menu_build_town)
    set_geometry_menu_build();

  set_geometry_menu_selectwork();
  set_geometry_menu_queue();
}

void MenuTown::start()
{
  menu_build_town->hide();
  menu_build_town->show();
  menu_type_work_town->hide();
  menu_type_work_town->show();
  menu_queue_town->hide();
  menu_queue_town->show();
}

ITownMenuGraphicsController* MenuTown::graphics_controller() const
{
  return _graphics_controller;
}

QWidget* MenuTown::window() const
{
  return _graphics_controller->window();
}

PlayerTown* MenuTown::town() const
{
  return _town;
}

IMenuTownPlayer* MenuTown::player() const
{
  return _player;
}

void MenuTown::delete_townmenu()
{
  _graphics_controller->delete_townmenu();
}

void MenuTown::open_menu_build()
{
  close_menu_alreadybuild();

  if(menu_build_town.get())
    return;
  menu_build_town.reset(new MenuBuildTown{this});
  set_geometry_menu_build();
  menu_build_town->hide();
  menu_build_town->show();
}

void MenuTown::open_menu_alreadybuild()
{
  close_menu_build();

  if(menu_already_build_town.get())
    return;

  menu_already_build_town.reset(new MenuAlreadyBuildTown{this});
  set_geometry_menu_alreadybuild();
  menu_already_build_town->hide();
  menu_already_build_town->show();
}

void MenuTown::set_build(Units type_unit)
{
  if(type_work == AddQueue)
    _town->add_queue_build(type_unit);
  else if(type_work == EditProject)
    _town->set_build(type_unit);
  menu_queue_town->update_queue();
  if(menu_build_town)
    menu_build_town->update_inform();
  del_inform_widget();
}

void MenuTown::set_build(TownBuildings type_building)
{
  if(type_work == AddQueue)
    _town->add_queue_build(type_building);
  else if(type_work == EditProject)
    _town->set_build(type_building);

  if(menu_queue_town)
    menu_queue_town->update_queue();

  if(menu_build_town)
    menu_build_town->update_inform();
  if(menu_already_build_town)
    menu_already_build_town->update_inform();

  del_inform_widget();
}

void MenuTown::del_build_from_queue(AWidgetTown* wid)
{
  _town->del_build(num_from_queue(wid));

  if(menu_queue_town)
    menu_queue_town->update_queue();

  if(menu_build_town)
    menu_build_town->update_inform();

  del_inform_widget();
}

size_t MenuTown::num_from_queue(AWidgetTown* wid) const
{
  return menu_queue_town->num_widget(wid);
}

size_t MenuTown::count_from_queue() const
{
  return menu_queue_town->count_widgets();
}

void MenuTown::move_up_build(AWidgetTown* wid)
{
  _town->move_up_build(num_from_queue(wid));
  menu_queue_town->update_queue();

  if(menu_build_town)
    menu_build_town->update_inform();

  del_inform_widget();
}

void MenuTown::move_down_build(AWidgetTown* wid)
{
  _town->move_down_build(num_from_queue(wid));
  menu_queue_town->update_queue();

  if(menu_build_town)
    menu_build_town->update_inform();

  del_inform_widget();
}

void MenuTown::wheel_scroll(int angle_delta)
{
  if(menu_build_town)
    menu_build_town->wheel_scroll(angle_delta);
}

void MenuTown::do_inform_widget(std::vector<std::pair<QString, QColor>> text)
{
  graphics_controller()->do_inform_widget(text);
}

void MenuTown::del_inform_widget()
{
  graphics_controller()->del_inform_widget();
}

void MenuTown::set_type_work(TypeWork _type_work)
{
  if(_type_work == type_work)
    return;
  type_work = _type_work;
  set_geometry_menu_queue();

  if(menu_build_town)
    menu_build_town->update_inform();
}

IMenuTown::TypeWork MenuTown::get_type_work() const
{
  return type_work;
}

void MenuTown::close_menu_build()
{
  menu_build_town.reset();
}

void MenuTown::close_menu_alreadybuild()
{
  menu_already_build_town.reset();
}

void MenuTown::close_menu_queue()
{
  menu_queue_town.reset();
}

void MenuTown::set_geometry_menu_build()
{
  if(!menu_build_town)
    return;
  menu_build_town->set_geometry(pos + QPoint{size.width*4/5, 0}, {size.width/5, size.height*3/4});
}

void MenuTown::set_geometry_menu_alreadybuild()
{
  if(!menu_already_build_town)
    return;
  menu_already_build_town->set_geometry(pos + QPoint{size.width*4/5, 0}, {size.width/5, size.height*3/4});
}

void MenuTown::set_geometry_menu_selectwork()
{
  if(!menu_type_work_town)
    return;

  Size size_menu_type_work{size.width/5,
        size.height/20*int(menu_type_work_town->count_button())};

  QPoint pos_menu_type_work{pos.x(),
        pos.y() + size.height - size_menu_type_work.height};

  menu_type_work_town->set_geometry(pos_menu_type_work, size_menu_type_work);
}

void MenuTown::set_geometry_menu_queue()
{
  if(!menu_queue_town)
    return;

  Size size_menu_queue{size.width/5, size.height/10+1};
  QPoint pos_menu_queue{pos + QPoint{size.width*4/5, size.height*9/10}};

  if(type_work == AddQueue)
  {
    size_menu_queue = {size.width/5, size.height/4-1};
    pos_menu_queue = {pos + QPoint{size.width*4/5, size.height*3/4+1}};
  }
  menu_queue_town->set_geometry(pos_menu_queue, size_menu_queue);
}
