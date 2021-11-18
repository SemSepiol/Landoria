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

void InformWidget::set_text(std::vector<std::pair<QString, QColor>> _text)
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
  resize(width(), fm.height()*int(text.size()));
  for(size_t i{}; i < text.size(); ++i)
  {
    QRect rect_str{0, fm.height()*int(i), width(), height()/int(text.size())};
    qp.setPen(text[i].second);
    qp.drawText(rect_str, Qt::AlignVCenter, text[i].first);
  }
}
