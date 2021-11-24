#include "MenuScience.h"
#include <iostream>

MenuScience::MenuScience(IMenuInWindowGraphicsController* _graphics_controller, PlayerScience* _player_science)
  :QWidget{_graphics_controller->window()}, graphics_controller{_graphics_controller},
    player_science{_player_science}
{
  QWidget::setAttribute( Qt::WA_TranslucentBackground, true );
}

void MenuScience::set_geometry(QPoint pos, Size size)
{
  QWidget::setGeometry(pos.x(), pos.y(), size.width, size.height);
  update_information();
}

void MenuScience::paintEvent(QPaintEvent* event)
{
  Q_UNUSED(event)
  draw();
  draw_scroll();
}

void MenuScience::mousePressEvent(QMouseEvent* event)
{
  mouse_pos_clicked = event->pos();
}

void MenuScience::mouseReleaseEvent(QMouseEvent* event)
{
  QPoint mouse_move = event->pos() - mouse_pos_clicked;
  if(abs(mouse_move.x()) > 5 or abs(mouse_move.y()) > 5)
    return;
  click(event->pos());
}

void MenuScience::wheelEvent(QWheelEvent* event)
{
  indent_x -= event->angleDelta().y();
  if(indent_x > 0)
    indent_x = 0;
  else if(indent_x + end_widgets() < width())
    indent_x = width() - end_widgets();

  set_geometry_widgets();
  update();
}

void MenuScience::update_information()
{
  knowledges.clear();
  Science science;

  init_space_x = width()/20;
  init_space_y = height()/10;
  space_x = width()/8;
  space_y = height()/20;
  size_block = {width()/5, height()/20};
  scroll_height = height()/50;

  for(size_t i{0}; i < n; ++i)
  {
    knowledges.push_back(std::vector<std::unique_ptr<WidgetKnowledge>>());
    for(size_t j{0}; j < m; ++j)
    {
      knowledges[i].push_back(std::unique_ptr<WidgetKnowledge>{
                                new WidgetKnowledge(graphics_controller, {}, player_science)});
      knowledges[i][j]->hide();
      knowledges[i][j]->show();
    }
  }

  set_geometry_widgets();
}

void MenuScience::draw()
{
  QPainter qp(this);

  QRect rect{0, 0, width(), height()};
  qp.fillRect(rect, QBrush(QColor(0, 0, 0, 200)));
  qp.setPen(QPen{Qt::white});
  qp.drawRect(rect_but_close());
  qp.drawText(rect_but_close(), Qt::AlignCenter, QString("Закрыть"));
}

void MenuScience::draw_scroll()
{
  if(end_widgets() < width())
    return;

  QPainter qp(this);

  int scroll_begin = -indent_x*width()/end_widgets();
  int scroll_end = (-indent_x+width())*width()/end_widgets();


  QRect rect{QPoint{scroll_begin, height()-scroll_height}, QPoint{scroll_end, height()}};

  qp.fillRect(rect, QBrush{Qt::blue});

  qp.setPen(QPen{Qt::white});
  qp.drawRect(QRect{0, height()-scroll_height, width(), scroll_height});
}

void MenuScience::click(QPoint pos)
{
  if(point_in_rect(rect_but_close(), pos))
    graphics_controller->close_menu_science();
}

void MenuScience::set_geometry_widgets()
{
  for(size_t i{0}; i < n; ++i)
    for(size_t j{0}; j < m; ++j)
    {
      QPoint pos{int(i)*(space_x + size_block.width) + init_space_x + indent_x,
            int(j)*(space_y + size_block.height) + init_space_y};
      knowledges[i][j]->set_geometry(pos, size_block);
    }
}

int MenuScience::end_widgets()
{
  return int(knowledges.size())*(space_x + size_block.width) +
      init_space_x*2 - space_x;
}

QRect MenuScience::rect_but_close() const
{
  Size size{width()/20, height()/20};
  int a = height()/50;
  QPoint pos{width() - size.width - a, height() - size.height - a - scroll_height};
  return QRect{pos.x(), pos.y(), size.width, size.height};
}

bool MenuScience::point_in_rect(QRectF rect, QPoint point)
{
  if (point.x() >= rect.topLeft().x() && point.x() < rect.bottomRight().x())
    if (point.y() >= rect.topLeft().y() && point.y() <= rect.bottomRight().y())
      return true;
  return false;
}
