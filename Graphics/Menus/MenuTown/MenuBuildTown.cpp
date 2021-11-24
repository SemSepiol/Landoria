#include "MenuBuildTown.h"
#include <iostream>

MenuBuildTown::MenuBuildTown(IMenuTown* _menu_town)
  :QWidget{_menu_town->window()}, menu_town{_menu_town}
{
  QWidget::setAttribute( Qt::WA_TranslucentBackground, true );
  QWidget::setMouseTracking(true);
}

void MenuBuildTown::set_geometry(QPoint pos, Size size)
{
  QWidget::setGeometry(pos.x(), pos.y(), size.width, size.height);
  height_rect_build = size.height/20;
  pos_menu = pos;
  width_scroll = width()/50;
  do_units();
  do_buildings();
  set_geometry_units();
  set_geometry_buildings();
}

void MenuBuildTown::update_inform()
{
  do_units();
  do_buildings();
  set_geometry_units();
  set_geometry_buildings();
  update();
}

void MenuBuildTown::wheel_scroll(int angle_delta)
{
  scroll_indent += angle_delta;

  int count_wid = int(widget_town_buildings.size() + widget_town_units.size());
  if(scroll_indent + height_rect_build * count_wid < height())
    scroll_indent = height() - height_rect_build * count_wid;
  if(scroll_indent > 0)
    scroll_indent = 0;


  set_geometry_units();
  set_geometry_buildings();
  update();
}

void MenuBuildTown::paintEvent(QPaintEvent* event)
{
  Q_UNUSED(event)
  draw();
  draw_scroll();
}

void MenuBuildTown::mouseMoveEvent(QMouseEvent *event)
{
  Q_UNUSED(event)
  menu_town->del_inform_widget();
}

void MenuBuildTown::mousePressEvent(QMouseEvent *event)
{
  mouse_pos_clicked = event->pos();
}

void MenuBuildTown::mouseReleaseEvent(QMouseEvent *event)
{
  QPoint mouse_move = event->pos() - mouse_pos_clicked;
  if(abs(mouse_move.x()) > 5 or abs(mouse_move.y()) > 5)
    return;
  click(event->pos());
}

void MenuBuildTown::wheelEvent(QWheelEvent* event)
{
  int angle_delta = event->angleDelta().y();
  wheel_scroll(angle_delta);
}

void MenuBuildTown::draw()
{
  QPainter qp(this);
  QRect rect{0, 0, width(), height()};
  qp.fillRect(rect, QBrush(QColor(0, 0, 0, 200)));
}

void MenuBuildTown::draw_scroll()
{
  QPainter qp(this);
  int height_begin = 0;
  int height_end = height();
  int count_wid = int(widget_town_buildings.size() + widget_town_units.size());
  if(height_rect_build * count_wid > height())
  {
    height_begin = -scroll_indent*height()/(height_rect_build * count_wid);
    height_end = height_begin + height()*height()/(height_rect_build * count_wid);
  }

  QRect rect{width() - width_scroll, height_begin, width_scroll, height_end - height_begin};
  qp.fillRect(rect, QBrush(Qt::blue));
}

void MenuBuildTown::do_units()
{
  widget_town_units.clear();
  PlayerScience* player_science = menu_town->player()->player_science();
  auto open_units = player_science->get_best_open_units();

  for(size_t i{0}; i < open_units.size(); ++i)
    widget_town_units.push_back(
          std::unique_ptr<WidgetTownUnit>{new WidgetTownUnit(menu_town,  open_units[i], WidgetTownUnit::Build)});

}

void MenuBuildTown::do_buildings()
{
  widget_town_buildings.clear();
  PlayerScience* player_science = menu_town->player()->player_science();
  auto open_buildings = player_science->get_open_town_buildings();
  auto already_build = menu_town->town()->get_building_already_build();
  auto queue_building = menu_town->town()->get_queue_buildings();
  for(size_t i{0}; i < open_buildings.size(); ++i)
  {
    if(std::find(already_build.begin(), already_build.end(), open_buildings[i]) != already_build.end())
      continue;

    if(std::find(queue_building.begin(), queue_building.end(), open_buildings[i]) != queue_building.end())
      continue;

    widget_town_buildings.push_back(
          std::unique_ptr<WidgetTownBuilding>{new WidgetTownBuilding(menu_town,  open_buildings[i], WidgetTownBuilding::Build)});
  }
}

void MenuBuildTown::set_geometry_units()
{
  QPoint pos = pos_menu;

  for(size_t i{0}; i < widget_town_units.size(); ++i)
  {
    if(pos.y() >= height() || pos.y()+scroll_indent <= 0)
      widget_town_units[i]->hide();
    else
    {
      widget_town_units[i]->set_geometry(pos + QPoint{0, scroll_indent}, {width() - width_scroll, height_rect_build});
      widget_town_units[i]->show();
    }
    pos += QPoint{0, height_rect_build};
  }
}

void MenuBuildTown::set_geometry_buildings()
{

  QPoint pos = pos_menu + QPoint{0, int(widget_town_units.size())*height_rect_build};

  for(size_t i{0}; i < widget_town_buildings.size(); ++i)
  {
    if(pos.y()+scroll_indent >= height() || pos.y()+scroll_indent <= 0)
      widget_town_buildings[i]->hide();
    else
    {
      widget_town_buildings[i]->set_geometry(pos + QPoint{0, scroll_indent}, {width() - width_scroll, height_rect_build});
      widget_town_buildings[i]->show();
    }
    pos += QPoint{0, height_rect_build};
  }
}

void MenuBuildTown::click(QPoint)
{

}

bool MenuBuildTown::point_in_rect(QRectF rect, QPoint point)
{
  if (point.x() >= rect.topLeft().x() && point.x() < rect.bottomRight().x())
    if (point.y() >= rect.topLeft().y() && point.y() <= rect.bottomRight().y())
      return true;
  return false;
}

QRect MenuBuildTown::rect_build(size_t i)
{
  QPoint pos{0, int(i)*height_rect_build};
  return QRect{pos, pos + QPoint{height_rect_build, height_rect_build}};
}
