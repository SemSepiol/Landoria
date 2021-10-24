#include "MenuBuildTown.h"

MenuBuildTown::MenuBuildTown(IMenuTown* _menu_town)
  :QWidget{_menu_town->window()}, menu_town{_menu_town}
{
  QWidget::setAttribute( Qt::WA_TranslucentBackground, true );
}

void MenuBuildTown::set_geometry(QPoint pos, Size size)
{
  QWidget::setGeometry(pos.x(), pos.y(), size.width, size.height);
  height_rect_build = size.height/20;
  pos_menu = pos;
  set_geometry_unit();
  set_geometry_building();
}

void MenuBuildTown::paintEvent(QPaintEvent* event)
{
  draw();
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

void MenuBuildTown::draw()
{
  QPainter qp(this);
  QRect rect{0, 0, width(), height()};
  qp.fillRect(rect, QBrush(QColor(0, 0, 0, 200)));
}

void MenuBuildTown::set_geometry_unit()
{
  PlayerScience* player_science = menu_town->player()->player_science();
  QPoint pos = pos_menu;
  auto open_units = player_science->get_best_open_units();
  for(size_t i{0}; i < open_units.size(); ++i)
  {
    widget_town_units.push_back(
          std::unique_ptr<WidgetTownUnit>{new WidgetTownUnit(menu_town,  open_units[i], WidgetTownUnit::Build)});

    (widget_town_units.end() - 1)->get()->set_geometry(pos, {width(), height_rect_build});

    pos += QPoint{0, height_rect_build};
  }
}

void MenuBuildTown::set_geometry_building()
{
  PlayerScience* player_science = menu_town->player()->player_science();
  QPoint pos = pos_menu + QPoint{0, int(player_science->count_best_open_units())*height_rect_build};
  auto open_buildings = player_science->get_open_town_buildings();
  auto already_build = menu_town->town()->get_town_buildings();
  for(size_t i{0}; i < open_buildings.size(); ++i)
  {
    if(std::find(already_build.begin(), already_build.end(), open_buildings[i]) != already_build.end())
      continue;

    widget_town_building.push_back(
          std::unique_ptr<WidgetTownBuilding>{new WidgetTownBuilding(menu_town,  open_buildings[i], WidgetTownBuilding::Build)});

    (widget_town_building.end() - 1)->get()->set_geometry(pos, {width(), height_rect_build});
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
