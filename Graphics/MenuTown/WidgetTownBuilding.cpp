#include "WidgetTownBuilding.h"
#include <iostream>

WidgetTownBuilding::WidgetTownBuilding(IMenuTown* _menu_town, TownBuildings _type_building, TypeWork _type_widget)
  :AWidgetTown{_menu_town->window(), _type_widget}, menu_town{_menu_town}, type_building{_type_building}
{
  QWidget::setAttribute( Qt::WA_TranslucentBackground, true );
  QWidget::setMouseTracking(true);
}

void WidgetTownBuilding::set_geometry(QPoint pos, Size size)
{
  QWidget::setGeometry(pos.x(), pos.y(), size.width, size.height);
  this->hide();
  this->show();
}

size_t WidgetTownBuilding::num_from_queue()
{
  return menu_town->num_from_queue(this);
}

size_t WidgetTownBuilding::count_from_queue()
{
  return menu_town->count_from_queue();
}

void WidgetTownBuilding::paintEvent(QPaintEvent* event)
{
  Q_UNUSED(event)
  draw();
  draw_butt();
}

void WidgetTownBuilding::mouseMoveEvent(QMouseEvent *event)
{
  if(event->pos().x() > 0 && event->pos().y() > 0 &&
     event->pos().x() < width() && event->pos().y() < height())
    menu_town->do_inform_widget(text());
  else
    menu_town->del_inform_widget();
}

void WidgetTownBuilding::mousePressEvent(QMouseEvent *event)
{
  mouse_pos_clicked = event->pos();
}

void WidgetTownBuilding::mouseReleaseEvent(QMouseEvent *event)
{
  QPoint mouse_move = event->pos() - mouse_pos_clicked;
  if(abs(mouse_move.x()) > 5 or abs(mouse_move.y()) > 5)
    return;
  if(type_widget == Build
     && menu_town->count_from_queue() < menu_town->town()->max_build_in_queue())
    menu_town->set_build(type_building);

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

void WidgetTownBuilding::wheelEvent(QWheelEvent *event)
{
  if(type_widget == TypeWork::Build)
    menu_town->wheel_scroll(event->angleDelta().y());
}

void WidgetTownBuilding::draw()
{
  QPainter qp(this);
  qp.setPen(QPen{Qt::white, 3});
  qp.drawRect(QRect{QPoint{0,0}, QPoint{width(), height()}});

  QPixmap pixmap = FactoryPixmap().create_pixmap_for_town_building(type_building);
  QRectF source = FactoryPixmap().size_picture_content();
  QRectF rect = QRect{QPoint{0,0}, QPoint{height(), height()}};
  qp.drawPixmap(rect, pixmap, source);

  QString name_build = FactoryString().building_in_town_string(type_building);
  QRectF rect2{QPoint{height(), 0}, QPoint{width(), height()/2}};
  qp.drawText(rect2, Qt::AlignLeft | Qt::AlignVCenter, name_build);

  if(type_widget != AlreadyBuild)
  {
    QRectF rect3{QPoint{height(), height()/2}, QPoint{width(), height()}};
    std::stringstream ss;
    int build_moves =  menu_town->town()->get_build_need_production(type_building) /
        menu_town->town()->get_production();
    ss << build_moves << " Ход";
    qp.drawText(rect3, Qt::AlignLeft | Qt::AlignVCenter, QString::fromStdString(ss.str()));
  }

  if(type_widget == Build &&
     menu_town->count_from_queue() == menu_town->town()->max_build_in_queue())
  {
    QRect rect{0, 0, width(), height()};
    qp.fillRect(rect, QBrush(QColor(0, 0, 0, 100)));
  }
}

QString WidgetTownBuilding::text()
{
  auto res = TownBuildNeeds().get_build_need_res(type_building);
  std::stringstream ss;
  ss << FactoryString().building_in_town_string(type_building).toStdString() << "\n";
  for(size_t i{0}; i < res.size(); ++i)
    ss << FactoryString().resource_string(res[i].first).toStdString()
       << ": " << res[i].second << "\n";
  return QString::fromStdString(ss.str());
}
