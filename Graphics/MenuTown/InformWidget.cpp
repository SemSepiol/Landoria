#include "InformWidget.h"
#include <iostream>

InformWidget::InformWidget(QWidget* parent)
  :QWidget{parent}
{
  setAttribute(Qt::WA_TransparentForMouseEvents);
}

void InformWidget::set_set_geometry(QPoint pos, Size size)
{
  QWidget::setGeometry(QRect{pos.x(), pos.y(), size.width, size.height});
}

void InformWidget::set_text(QString _text)
{
  text = _text;
}

void InformWidget::paintEvent(QPaintEvent* event)
{
  draw();
}

void InformWidget::draw()
{
  QPainter qp(this);
  qp.setPen(QPen{Qt::white, 2});
//  std::cout << text.toStdString() << std::endl;
  QFontMetrics fm = qp.fontMetrics();
  std::string str = text.toStdString();
  int count_str =  std::count(str.begin(), str.end(), '\n') +1;
  resize(width(),fm.height()*count_str);
  qp.drawText(QRectF{0, 0, width()*1., height()*1.}, Qt::AlignVCenter, text);
}
