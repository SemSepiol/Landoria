#include "WidgetTownUnit.h"
#include <iostream>

WidgetTownUnit::WidgetTownUnit(IMenuTown* _menu_town, Units _type_unit, Type _type_widget)
  :QWidget{_menu_town->window()}, menu_town{_menu_town},
    type_unit{_type_unit}, type_widget{_type_widget}
{
  QWidget::setAttribute( Qt::WA_TranslucentBackground, true );
}

void WidgetTownUnit::set_geometry(QPoint pos, Size size)
{
  QWidget::setGeometry(pos.x(), pos.y(), size.width, size.height);
  this->hide();
  this->show();
}

void WidgetTownUnit::paintEvent(QPaintEvent* event)
{
  draw();
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
  menu_town->set_build(type_unit);
}

void WidgetTownUnit::draw()
{
  QPainter qp(this);
  qp.setPen(QPen{Qt::white, 3});
  qp.drawRect(QRect{QPoint{0,0}, QPoint{width(), height()}});

  QPixmap pixmap = FactoryPixmap().create_pixmap_for_unit(type_unit);
  QRectF source = FactoryPixmap().size_picture_unit();
  QRectF rect = QRect{QPoint{0,0}, QPoint{height(), height()}};
  qp.drawPixmap(rect, pixmap, source);

  std::cout << height() << std::endl;
  QString name_build = FactoryString().unit_string(type_unit);
  QRectF rect2{QPoint{height(), 0}, QPoint{width(), height()/2}};
  qp.drawText(rect2, Qt::AlignVCenter, name_build);

  QRectF rect3{QPoint{height(), height()/2}, QPoint{width(), height()}};
  std::stringstream ss;
  int build_moves = TownBuildNeeds().get_build_need_production(type_unit) /
      menu_town->town()->get_production();
  ss << build_moves << " Ход";
  qp.drawText(rect3, Qt::AlignVCenter, QString::fromStdString(ss.str()));
}
