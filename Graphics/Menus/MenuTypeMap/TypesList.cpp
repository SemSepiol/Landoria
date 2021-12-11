#include "TypesList.h"

TypesList::TypesList(IMenuTypeMap* _menu_type_map)
  :QWidget{_menu_type_map}, menu_type_map{_menu_type_map}
{}

void TypesList::set_text(std::vector<QString> text)
{
  strings = text;
}

void TypesList::set_geometry(QPoint pos, Size _size_block)
{
  size_block = _size_block;
  QWidget::setGeometry(pos.x(), pos.y(),
                       _size_block.width, _size_block.height*int(strings.size()));
}

void TypesList::paintEvent(QPaintEvent* event)
{
  Q_UNUSED(event)
  draw();
}

void TypesList::mousePressEvent(QMouseEvent *event)
{
  mouse_pos_clicked = event->pos();
}

void TypesList::mouseReleaseEvent(QMouseEvent *event)
{
  QPoint mouse_move = event->pos() - mouse_pos_clicked;
  if(abs(mouse_move.x()) > 5 or abs(mouse_move.y()) > 5)
    return;
  click(event->pos());
}

void TypesList::draw()
{
  QPainter qp(this);
  qp.setPen(QPen(Qt::black, 2));
  qp.setBrush(Qt::green);
  for(size_t i{0}; i < strings.size(); ++i)
  {
    qp.drawRect(rect_str(int(i)));
    qp.drawText(rect_str(int(i)), Qt::AlignCenter, strings[i]);
  }
}

void TypesList::click(QPoint pos)
{
  for(int i{0}; i < int(strings.size()); ++i)
    if(rect_str(i).contains(pos))
    {
      menu_type_map->set_type(i);
      return;
    }
}

QRect TypesList::rect_str(int i)
{
  return QRect{0, i*size_block.height, size_block.width, size_block.height};
}
