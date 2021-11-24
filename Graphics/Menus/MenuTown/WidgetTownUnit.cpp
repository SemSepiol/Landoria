#include "WidgetTownUnit.h"
#include <iostream>

WidgetTownUnit::WidgetTownUnit(IMenuTown* _menu_town, Units _type_unit, TypeWork _type_widget)
  :AWidgetTown{_menu_town->window(), _type_widget}, menu_town{_menu_town},
    type_unit{_type_unit}
{
  QWidget::setAttribute( Qt::WA_TranslucentBackground, true );
  QWidget::setMouseTracking(true);

  auto player = menu_town->player();
  auto player_res = player->get_player_res();

  for(auto res : TownBuildNeeds().get_build_need_res(type_unit))
    if(player_res->get_resource(res.first) < res.second)
      enable = false;
}

void WidgetTownUnit::set_geometry(QPoint pos, Size size)
{
  QWidget::setGeometry(pos.x(), pos.y(), size.width, size.height);
  this->hide();
  this->show();
}

size_t WidgetTownUnit::num_from_queue()
{
  return menu_town->num_from_queue(this);
}

size_t WidgetTownUnit::count_from_queue()
{
  return menu_town->count_from_queue();
}

void WidgetTownUnit::paintEvent(QPaintEvent* event)
{
  Q_UNUSED(event)
  draw_widget();
  draw_butt();
  AWidgetTown::draw_enable();
}

void WidgetTownUnit::mouseMoveEvent(QMouseEvent *event)
{
  if(event->pos().x() > 0 && event->pos().y() > 0 &&
     event->pos().x() < width() && event->pos().y() < height())
    menu_town->do_inform_widget(text());
  else
    menu_town->del_inform_widget();
}

void WidgetTownUnit::mousePressEvent(QMouseEvent *event)
{
  mouse_pos_clicked = event->pos();
}

void WidgetTownUnit::mouseReleaseEvent(QMouseEvent *event)
{
  QPoint mouse_move = event->pos() - mouse_pos_clicked;
  if(abs(mouse_move.x()) > 5 or abs(mouse_move.y()) > 5)
    return;

  if(type_widget == Build && enable &&
     menu_town->count_from_queue() < menu_town->town()->max_build_in_queue())
    menu_town->set_build(type_unit);
  if(type_widget == InQueue)
  {
    if(point_in_rect(rect_butt_del(), event->pos()))
      menu_town->del_build_from_queue(this);
    else if(point_in_rect(rect_butt_up(), event->pos()))
      menu_town->move_up_build(this);
    else if(point_in_rect(rect_butt_down(), event->pos()))
      menu_town->move_down_build(this);
  }
}

void WidgetTownUnit::wheelEvent(QWheelEvent *event)
{
  if(type_widget == TypeWork::Build)
    menu_town->wheel_scroll(event->angleDelta().y());
}

void WidgetTownUnit::draw_widget()
{
  QPainter qp(this);
  qp.setPen(QPen{Qt::white, 3});
  qp.drawRect(QRect{QPoint{0,0}, QPoint{width(), height()}});

  QPixmap pixmap = FactoryPixmap().create_pixmap_for_unit(type_unit);
  QRectF source = FactoryPixmap().size_picture_unit();
  QRectF rect = QRect{QPoint{0,0}, QPoint{height(), height()}};
  qp.drawPixmap(rect, pixmap, source);

  QString name_build = QString::fromStdString(FactoryString().unit_string(type_unit));
  QRectF rect2{QPoint{height(), 0}, QPoint{width(), height()/2}};
  qp.drawText(rect2, Qt::AlignVCenter, name_build);

  QRectF rect3{QPoint{height(), height()/2}, QPoint{width(), height()}};
  std::stringstream ss;
  int build_moves = menu_town->town()->get_build_need_production(type_unit) /
      menu_town->town()->get_production();
  ss << build_moves << " Ход";
  qp.drawText(rect3, Qt::AlignVCenter, QString::fromStdString(ss.str()));

  if(type_widget == Build && enable &&
     menu_town->count_from_queue() == menu_town->town()->max_build_in_queue())
  {
    QRect rect{0, 0, width(), height()};
    qp.fillRect(rect, QBrush(QColor(0, 0, 0, 100)));
  }
}

std::vector<std::pair<QString, QColor>>  WidgetTownUnit::text()
{
  auto res = TownBuildNeeds().get_build_need_res(type_unit);

  std::vector<std::pair<QString, QColor>> text;
  text.push_back({QString::fromStdString(
                  FactoryString().unit_string(type_unit)), Qt::white});

  auto player = menu_town->player();
  auto player_res = player->get_player_res();
  for(size_t i{0}; i < res.size(); ++i)
  {
    std::stringstream ss;
    ss << FactoryString().resource_string(res[i].first)
       << ": " << res[i].second;

    QColor color = Qt::white;
    if (player_res->get_resource(res[i].first) < res[i].second)
      color = Qt::red;
    text.push_back({QString::fromStdString(ss.str()), color});
  }
  return text;
}
