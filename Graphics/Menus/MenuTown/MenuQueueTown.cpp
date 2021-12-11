#include "MenuQueueTown.h"
#include <iostream>

MenuQueueTown::MenuQueueTown(IMenuTown* _menu_town)
  :QWidget{_menu_town->window()}, menu_town{_menu_town}
{
  QWidget::setAttribute( Qt::WA_TranslucentBackground, true );
  QWidget::setMouseTracking(true);
}

void MenuQueueTown::set_geometry(QPoint pos, Size size)
{
  QWidget::setGeometry(pos.x(), pos.y(), size.width, size.height);
  height_butt_queue = size.width/20;
  height_text_queue = size.width/20;

  height_rect_build = size.height - height_butt_queue - height_text_queue;
  if(menu_town->get_type_work() == IMenuTown::AddQueue)
    height_rect_build /= menu_town->town()->max_build_in_queue();

  pos_menu = pos;

  numder_rect = {0,0};
  if(menu_town->get_type_work() == IMenuTown::AddQueue)
    numder_rect = {size.width/10, height_rect_build};

  update_queue();
}

void MenuQueueTown::paintEvent(QPaintEvent* event)
{
  Q_UNUSED(event)
  draw();
  draw_number();
  draw_butt_queue();
}

void MenuQueueTown::mouseMoveEvent(QMouseEvent *event)
{
  Q_UNUSED(event)
  menu_town->del_inform_widget();
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

  if(point_in_rect(rect_butt_queue(), event->pos()))
  {
    if(menu_town->get_type_work() == IMenuTown::AddQueue)
      menu_town->set_type_work(IMenuTown::EditProject);
    else
      menu_town->set_type_work(IMenuTown::AddQueue);
  }
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

void MenuQueueTown::draw_butt_queue()
{
  QPainter qp(this);
  qp.setPen(QPen{Qt::white, 2});

  qp.drawRect(rect_butt_queue());
  if(menu_town->get_type_work() == IMenuTown::AddQueue)
    qp.fillRect(rect_butt_queue(), Qt::white);

  qp.drawText(rect_text_butt_queue(), Qt::AlignVCenter | Qt::AlignRight, "Показать очередь");
}

void MenuQueueTown::update_queue()
{
  widgets_town_build.clear();
  auto queue = menu_town->town()->get_build_queue();

  if(queue.size() == 0)
  {
    update();
    return;
  }
  size_t a = 1;
  if(menu_town->get_type_work() == IMenuTown::AddQueue)
    a = queue.size();
  for(size_t i{0}; i < a; ++i)
  {
    if(queue[i]->type_build == BuildInTown::Unit)
      widgets_town_build.push_back({new WidgetTownUnit(menu_town, queue[i]->unit, WidgetTownUnit::InQueue)});
    else if(queue[i]->type_build == BuildInTown::Building)
      widgets_town_build.push_back({new WidgetTownBuilding(menu_town, queue[i]->building, WidgetTownBuilding::InQueue)});
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

bool MenuQueueTown::point_in_rect(QRect rect, QPoint point)
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

QRect MenuQueueTown::rect_butt_queue() const
{
  return QRect{width() - height_butt_queue*9/10 , height() - height_butt_queue*9/10,
        height_butt_queue*8/10, height_butt_queue*8/10};
}

QRect MenuQueueTown::rect_text_butt_queue() const
{
  return QRect{QPoint{0, rect_butt_queue().topLeft().y()},
    rect_butt_queue().bottomLeft() - QPoint{height_butt_queue/5,0}};
}
