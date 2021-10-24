#include "WidgetTownBuilding.h"

WidgetTownBuilding::WidgetTownBuilding(IMenuTown* _menu_town, TownBuildings _type_building, Type _type_widget)
  :QWidget{_menu_town->window()}, menu_town{_menu_town}, type_building{_type_building}, type_widget{_type_widget}
{
  QWidget::setAttribute( Qt::WA_TranslucentBackground, true );
}

void WidgetTownBuilding::set_geometry(QPoint pos, Size size)
{
  QWidget::setGeometry(pos.x(), pos.y(), size.width, size.height);
  this->hide();
  this->show();
}

void WidgetTownBuilding::paintEvent(QPaintEvent* event)
{
  draw();
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
  menu_town->set_build(type_building);
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

  QRectF rect3{QPoint{height(), height()/2}, QPoint{width(), height()}};
  std::stringstream ss;
  int build_moves = TownBuildNeeds().get_build_need_production(type_building) /
      menu_town->town()->get_production();
  ss << build_moves << " Ход";
  qp.drawText(rect3, Qt::AlignLeft | Qt::AlignVCenter, QString::fromStdString(ss.str()));
}
