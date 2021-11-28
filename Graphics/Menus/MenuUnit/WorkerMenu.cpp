#include "WorkerMenu.h"
#include <iostream>

WorkerMenu::WorkerMenu(QWidget* _win, IUnitMenuGraphicsController* _graphics_controller,
                       PlayerUnit* _unit, Cell* _cell)
  :AMenuForUnit(_win, _graphics_controller, _unit, _cell)
{
  set_buttons();
}

void WorkerMenu::set_buttons()
{
  AMenuForUnit::set_buttons();
  num_butt_build = buttons.size();
  buttons.push_back(new BuildEvent{Buildings::Farm});
  set_is_enable(buttons[num_butt_build]);
  buttons.push_back(new MoveEvent{{0,0}});
  buttons.push_back(new SlipEvent{});
  set_is_enable(buttons[num_butt_build+2]);
}

void WorkerMenu::draw_butt(size_t num_butt)
{
  if(num_butt != num_butt_build)
  {
    AMenuForUnit::draw_butt(num_butt);
    return;
  }

  QPainter qp(this);
  QRectF source = FactoryPixmap().size_picture_content();
  QPixmap pixmap = FactoryPixmap().create_pixmap_for_butt_build();

  qp.drawPixmap(rect_butt(num_butt), pixmap, source);
  if(!buttons[num_butt].is_enable)
    qp.fillRect(rect_butt(num_butt), QBrush(QColor(0, 0, 0, 100)));
}

void WorkerMenu::click_butt(size_t num_butt)
{
  if(num_butt != num_butt_build)
  {
    AMenuForUnit::click_butt(num_butt);
    has_menu = false;
    //    menu.reset();
    return;
  }
  if(!buttons[num_butt].is_enable)
    return;

  if(has_move_event)
  {
    has_move_event = false;
    graphics_controller->menu_unit_event(unit->unit, new MoveEvent{{0,0}});
  }

  if(has_menu)
  {
    has_menu = false;
    menu.reset();
    return;
  }

  menu.reset(new MenuBuild{win, graphics_controller, unit, cell});
  menu->set_geometry(pos_menu + rect_butt(num_butt_build).topRight().toPoint(), side_square);
  menu->hide();
  menu->show();
  win->update();
  has_menu = true;
}

void WorkerMenu::set_is_enable(MyButton& my_butt)
{
  if(my_butt.event->event == Events::Build)
  {
    ControlContents controlcontents(cell);
    if(controlcontents.has_building())
    {
      Building* building = controlcontents.get_building();
      if(building->is_built())
        my_butt.is_enable = false;
    }
    if(controlcontents.get_country() != unit->unit->get_country())
      my_butt.is_enable = false;
  }

  if(my_butt.event->event == Events::Slip)
  {
    ControlContents controlcontents(cell);
    int count = 0;
    for(auto type_unit : controlcontents.get_units())
      if(type_unit == Units::Worker || type_unit == Units::Citizen)
        count++;
    if(count > 1)
      my_butt.is_enable = false;
  }
}

MenuBuild::MenuBuild(QWidget* _win, IUnitMenuGraphicsController* _graphics_controller,
                     PlayerUnit* _unit, Cell* _cell)
  :AMenuForUnit(_win, _graphics_controller, _unit, _cell)
{
  set_buttons();
}

void MenuBuild::set_buttons()
{
  add_farm();
  add_lumbermill();
  add_mine();
  add_pasture();
  add_oilwell();
  add_quarry();
  add_tradingpost();
  add_fort();

  set_is_enable();
}

QRectF MenuBuild::rect_butt(size_t i)
{
  return QRectF{int(i)*side_square*1., 0, side_square*1., side_square*1.};
}

void MenuBuild::set_geometry(QPoint pos, int _side_square)
{
  side_square = _side_square;
  QWidget::setGeometry(pos.x(), pos.y(), side_square * int(buttons.size()), side_square);
}

void MenuBuild::set_is_enable()
{
  ControlContents controlcontents(cell);
  if(controlcontents.has_building())
  {
    Building* building = controlcontents.get_building();
    for(size_t i{0}; i < buttons.size(); ++i)
    {
      BuildEvent* build_event = static_cast<BuildEvent*>(buttons[i].event.get());
      if(building->is_built() || building->what_building_I() != build_event->building)
        buttons[i].is_enable = false;
    }
  }
}

void MenuBuild::add_farm()
{
  ControlContents cc(cell);
  if(graphics_controller->player_science()->is_open_buildings(Buildings::Farm))
    if(cc.get_main_landscape() == MainLandscapes::Plain)
      buttons.push_back(new BuildEvent{Buildings::Farm});
}

void MenuBuild::add_lumbermill()
{
  ControlContents cc(cell);
  if(graphics_controller->player_science()->is_open_buildings(Buildings::LumberMill))
    if(cc.get_other_landscape() == OtherLandscapes::Forest ||
       cc.get_other_landscape() == OtherLandscapes::ForestAndHills)
      buttons.push_back(new BuildEvent{Buildings::LumberMill});
}

void MenuBuild::add_mine()
{
  ControlContents cc(cell);

  if(!graphics_controller->player_science()->is_open_buildings(Buildings::Mine))
    return;

  if(cc.get_other_landscape() == OtherLandscapes::Hills ||
     cc.get_other_landscape() == OtherLandscapes::ForestAndHills ||
     cc.get_other_landscape() == OtherLandscapes::JunglesAndHills)
    buttons.push_back(new BuildEvent{Buildings::Mine});
  else if(cc.has_resource())
    if(cc.get_resource() == Resources::Aluminum ||
       cc.get_resource() == Resources::Coal ||
       cc.get_resource() == Resources::Gold ||
       cc.get_resource() == Resources::Iron ||
       cc.get_resource() == Resources::Silver ||
       cc.get_resource() == Resources::Uranium
       )
      buttons.push_back(new BuildEvent{Buildings::Mine});
}

void MenuBuild::add_pasture()
{
  ControlContents cc(cell);
  if(graphics_controller->player_science()->is_open_buildings(Buildings::Pasture))
    if(cc.has_resource())
      if(cc.get_resource() == Resources::Horses)
        buttons.push_back(new BuildEvent{Buildings::Pasture});
}

void MenuBuild::add_oilwell()
{
  ControlContents cc(cell);
  if(graphics_controller->player_science()->is_open_buildings(Buildings::OilWell))
    if(cc.has_resource())
      if(cc.get_resource() == Resources::Oil)
        buttons.push_back(new BuildEvent{Buildings::OilWell});
}

void MenuBuild::add_quarry()
{
  ControlContents cc(cell);
  if(graphics_controller->player_science()->is_open_buildings(Buildings::Quarry))
    if(cc.has_resource())
      if(cc.get_resource() == Resources::Stone)
        buttons.push_back(new BuildEvent{Buildings::Quarry});
}

void MenuBuild::add_tradingpost()
{
  ControlContents cc(cell);
  if(graphics_controller->player_science()->is_open_buildings(Buildings::TradingPost))
    buttons.push_back(new BuildEvent{Buildings::TradingPost});
}

void MenuBuild::add_fort()
{
  ControlContents cc(cell);
  if(graphics_controller->player_science()->is_open_buildings(Buildings::Fort))
    buttons.push_back(new BuildEvent{Buildings::Fort});
}

