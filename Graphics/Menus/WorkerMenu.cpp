#include "WorkerMenu.h"
#include <iostream>

WorkerMenu::WorkerMenu(QWidget* _win, IGraphicsControllerMenuForUnit* _graphics_controller,
                       class Unit* _unit, Cell* _cell)
  :AMenuForUnit(_win, _graphics_controller, _unit, _cell)
{
  buttons.push_back(new BuildEvent{Buildings::Farm});
  buttons.push_back(new MoveEvent{0,0});
  buttons.push_back(new SlipEvent{});
}

void WorkerMenu::draw_butt(size_t num_butt)
{
  if(num_butt != 0)
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
  if(num_butt != 0)
  {
    AMenuForUnit::click_butt(num_butt);
    has_menu = false;
    menu.reset();
    return;
  }

  if(has_move_event)
  {
    has_move_event = false;
    graphics_controller->menu_unit_event(unit, new MoveEvent{0,0});
  }

  if(has_menu)
  {
    has_menu = false;
    menu.reset();
    return;
  }

  menu.reset(new MenuBuild{win, graphics_controller, unit, cell});
  menu->set_geometry(pos_menu + rect_butt(0).topRight().toPoint(), side_square);
  menu->hide();
  menu->show();
  win->update();
  has_menu = true;
}

MenuBuild::MenuBuild(QWidget* _win, IGraphicsControllerMenuForUnit* _graphics_controller,
                     class Unit* _unit, Cell* _cell)
  :AMenuForUnit(_win, _graphics_controller, _unit, _cell)
{
  buttons.push_back(new BuildEvent{Buildings::Farm});
  buttons.push_back(new BuildEvent{Buildings::Fort});
  buttons.push_back(new BuildEvent{Buildings::LumberMill});
  buttons.push_back(new BuildEvent{Buildings::Mine});
  buttons.push_back(new BuildEvent{Buildings::OilWell});
  buttons.push_back(new BuildEvent{Buildings::Pasture});
  buttons.push_back(new BuildEvent{Buildings::Quarry});
  buttons.push_back(new BuildEvent{Buildings::TradingPost});
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
    for(size_t i{0}; i < buttons.size(); ++i)
      buttons[i].is_enable = false;
}

