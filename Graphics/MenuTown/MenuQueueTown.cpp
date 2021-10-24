#include "MenuQueueTown.h"
#include <iostream>

MenuQueueTown::MenuQueueTown(IMenuTown* _menu_town)
  :QWidget{_menu_town->window()}, menu_town{_menu_town}
{
  QWidget::setAttribute( Qt::WA_TranslucentBackground, true );
}

void MenuQueueTown::set_geometry(QPoint pos, Size size)
{
  QWidget::setGeometry(pos.x(), pos.y(), size.width, size.height);
  height_rect_build = size.height/6;
  pos_menu = pos;
  numder_rect = {size.width/10, height_rect_build};

  update_queue();
}

void MenuQueueTown::paintEvent(QPaintEvent* event)
{
  draw();
  draw_number();
}

void MenuQueueTown::mousePressEvent(QMouseEvent *event)
{
  mouse_pos_clicked = event->pos();
}

void MenuQueueTown::mouseReleaseEvent(QMouseEvent *event)
{
  QPoint mouse_move = event->pos() - mouse_pos_clicked;
  if(abs(mouse_move.x()) > 5 or abs(mouse_move.y()) > 5)
    return;
}

void MenuQueueTown::draw()
{
  QPainter qp(this);
  QRect rect{0, 0, width(), height()};
  qp.fillRect(rect, QBrush(QColor(0, 0, 0, 200)));
}

void MenuQueueTown::draw_number()
{
  QPainter qp(this);
  qp.setPen(QPen{Qt::white, 3});
  for(size_t i{0}; i < widgets_town_build.size(); ++i)
  {
    QRect rect{0, int(i)*numder_rect.height,
          numder_rect.width, numder_rect.height};

    qp.drawRect(rect);
    QString str = QString::fromStdString(std::to_string(i+1));
    qp.drawText(rect, Qt::AlignCenter, str);
  }
}

void MenuQueueTown::update_queue()
{
  widgets_town_build.clear();
  auto queue = menu_town->town()->get_build_queue();

  for(size_t i{0}; i < queue.size(); ++i)
  {
    if(queue[i].type_build == BuildInTown::Unit)
      widgets_town_build.push_back({new WidgetTownUnit(menu_town, queue[i].unit, WidgetTownUnit::InQueue)});
    else if(queue[i].type_build == BuildInTown::Building)
      widgets_town_build.push_back({new WidgetTownBuilding(menu_town, queue[i].building, WidgetTownBuilding::InQueue)});
    set_geometry_wid(i);
  }
  update();
}

size_t MenuQueueTown::num_widget(AWidgetTown* wid_build) const
{
  for(size_t i{0}; i < widgets_town_build.size(); ++i)
  {
    if(wid_build->who_i() == AWidgetTown::ForBuilding)
    {
      if(widgets_town_build[i].wid_town_building.get() == wid_build)
        return i;
    }
    else if(wid_build->who_i() == AWidgetTown::ForUnit)
    {
      if(widgets_town_build[i].wid_town_unit.get() == wid_build)
        return i;
    }
  }
  throw std::runtime_error("num_widget(): I haven't got this widget");
}

size_t MenuQueueTown::count_widgets() const
{
  return widgets_town_build.size();
}

bool MenuQueueTown::point_in_rect(QRectF rect, QPoint point)
{
  if (point.x() >= rect.topLeft().x() && point.x() < rect.bottomRight().x())
    if (point.y() >= rect.topLeft().y() && point.y() <= rect.bottomRight().y())
      return true;
  return false;
}

void MenuQueueTown::set_geometry_wid(size_t i)
{
  QPoint pos = pos_menu + QPoint{numder_rect.width, height_rect_build*int(i)};
  if(widgets_town_build[i].type_build == WidgetTownBuild::Unit)
    widgets_town_build[i].wid_town_unit->set_geometry(pos, {width() - numder_rect.width, height_rect_build});
  else if(widgets_town_build[i].type_build == WidgetTownBuild::Building)
    widgets_town_build[i].wid_town_building->set_geometry(pos, {width() - numder_rect.width, height_rect_build});
}
