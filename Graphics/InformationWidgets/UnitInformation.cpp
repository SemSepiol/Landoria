#include "UnitInformation.h"

UnitInformation::UnitInformation(QWidget* win, class Unit* _unit)
  :QWidget{win}, unit{_unit}
{}

void UnitInformation::set_geometry(QPoint pos, int height)
{
  QWidget::setGeometry(pos.x(), pos.y(), height*3, height);
  this->hide();
  this->show();
}


void UnitInformation::paintEvent(QPaintEvent* event)
{
  Q_UNUSED(event)
  draw();
}

void UnitInformation::draw()
{
  QPainter qp(this);
  QPen pen{Qt::white, 2, Qt::SolidLine};
  qp.setPen(pen);
  qp.drawRect(0, 0, width(), height());

  QPixmap pixmap_unit = FactoryPixmap().create_pixmap_for_unit(unit->what_unit_I());
  QRectF source = FactoryPixmap().size_picture_unit();
  qp.drawPixmap(QRect{0, 0, height(), height()}, pixmap_unit, source);


  QRect rect_movement{QPoint{width()/3 + width()/10, 0}, QPoint{width() - width()/10, height()/2}};
  std::stringstream ss1;
  ss1 << "Movement: " << unit->get_movement() << "/" << unit->get_max_movement();
  qp.drawText(rect_movement, Qt::AlignVCenter, QString::fromStdString(ss1.str()));

  QRect rect_health{QPoint{width()/3 + width()/10, height()/2}, QPoint{width() - width()/10, height()}};
  std::stringstream ss2;
  ss2 << "Health: " << unit->get_health() << "/" << unit->get_max_health();
  qp.drawText(rect_health, Qt::AlignVCenter, QString::fromStdString(ss2.str()));
}
