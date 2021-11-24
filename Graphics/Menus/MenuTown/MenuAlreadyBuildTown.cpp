#include "MenuAlreadyBuildTown.h"

MenuAlreadyBuildTown::MenuAlreadyBuildTown(IMenuTown* _menu_town)
  :QWidget{_menu_town->window()}, menu_town{_menu_town}
{
  QWidget::setAttribute( Qt::WA_TranslucentBackground, true );
  QWidget::setMouseTracking(true);
}

void MenuAlreadyBuildTown::set_geometry(QPoint pos, Size size)
{
  QWidget::setGeometry(pos.x(), pos.y(), size.width, size.height);
  height_rect_build = size.height/20;
  pos_menu = pos;
  width_scroll = width()/50;
  do_buildings();
  set_geometry_buildings();
}

void MenuAlreadyBuildTown::update_inform()
{
  do_buildings();
  set_geometry_buildings();
  update();
}

void MenuAlreadyBuildTown::wheel_scroll(int angle_delta)
{
  scroll_indent += angle_delta;

  int count_wid = int(widget_town_buildings.size());
  if(scroll_indent + height_rect_build * count_wid < height())
    scroll_indent = height() - height_rect_build * count_wid;
  if(scroll_indent > 0)
    scroll_indent = 0;

  set_geometry_buildings();
  update();
}

void MenuAlreadyBuildTown::paintEvent(QPaintEvent* event)
{
  Q_UNUSED(event)
  draw();
  draw_scroll();
}

void MenuAlreadyBuildTown::mouseMoveEvent(QMouseEvent *event)
{
  Q_UNUSED(event)
  menu_town->del_inform_widget();
}

void MenuAlreadyBuildTown::mousePressEvent(QMouseEvent *event)
{
  mouse_pos_clicked = event->pos();
}

void MenuAlreadyBuildTown::mouseReleaseEvent(QMouseEvent *event)
{
  QPoint mouse_move = event->pos() - mouse_pos_clicked;
  if(abs(mouse_move.x()) > 5 or abs(mouse_move.y()) > 5)
    return;
}

void MenuAlreadyBuildTown::wheelEvent(QWheelEvent* event)
{
  int angle_delta = event->angleDelta().y();
  wheel_scroll(angle_delta);
}

void MenuAlreadyBuildTown::draw()
{
  QPainter qp(this);
  QRect rect{0, 0, width(), height()};
  qp.fillRect(rect, QBrush(QColor(0, 0, 0, 200)));
}

void MenuAlreadyBuildTown::draw_scroll()
{
  QPainter qp(this);
  int height_begin = 0;
  int height_end = height();
  int count_wid = int(widget_town_buildings.size());
  if(height_rect_build * count_wid > height())
  {
    height_begin = -scroll_indent*height()/(height_rect_build * count_wid);
    height_end = height_begin + height()*height()/(height_rect_build * count_wid);
  }

  QRect rect{width() - width_scroll, height_begin, width_scroll, height_end - height_begin};
  qp.fillRect(rect, QBrush(Qt::blue));
}

void MenuAlreadyBuildTown::do_buildings()
{
  widget_town_buildings.clear();
  auto already_build = menu_town->town()->get_building_already_build();

  for(size_t i{0}; i < already_build.size(); ++i)
  {
    widget_town_buildings.push_back(
          std::unique_ptr<WidgetTownBuilding>{new WidgetTownBuilding(menu_town,  already_build[i], WidgetTownBuilding::AlreadyBuild)});
  }
}

void MenuAlreadyBuildTown::set_geometry_buildings()
{

  QPoint pos = pos_menu;

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

bool MenuAlreadyBuildTown::point_in_rect(QRectF rect, QPoint point)
{
  if (point.x() >= rect.topLeft().x() && point.x() < rect.bottomRight().x())
    if (point.y() >= rect.topLeft().y() && point.y() <= rect.bottomRight().y())
      return true;
  return false;
}

QRect MenuAlreadyBuildTown::rect_build(size_t i)
{
  QPoint pos{0, int(i)*height_rect_build};
  return QRect{pos, pos + QPoint{height_rect_build, height_rect_build}};
}
