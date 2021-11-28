#include "MenuScience.h"
#include <iostream>

MenuScience::MenuScience(IMenuInWindowGraphicsController* _graphics_controller, PlayerScience* _player_science)
  :IMenuScience{_graphics_controller->window()}, graphics_controller{_graphics_controller},
    player_science{_player_science}
{
  QWidget::setAttribute( Qt::WA_TranslucentBackground, true );
}

void MenuScience::set_geometry(QPoint pos, Size size)
{
  QWidget::setGeometry(pos.x(), pos.y(), size.width, size.height);
  update_information();
}

void MenuScience::wheel_scroll(int angle)
{
  indent_x -= angle;
  if(indent_x > 0)
    indent_x = 0;
  else if(indent_x + end_widgets() < width())
    indent_x = width() - end_widgets();

  set_geometry_widgets();
  update();
}

void MenuScience::paintEvent(QPaintEvent* event)
{
  Q_UNUSED(event)
  draw();
  draw_queue();
  draw_connections();
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
  wheel_scroll(event->angleDelta().y());
}

void MenuScience::update_information()
{
  knowledges.clear();
  Science science;

  init_space_x = width()/20;
  init_space_y = height()/20;
  space_x = width()/8;
  space_y = height()/20;
  size_block = {width()/8, height()/15};
  scroll_height = height()/50;
  count_columns = 0;
  for(auto name_knowledge : Science().get_all_name_knowledges())
  {
    Knowledge knowledge = Science().get_knowledge(name_knowledge);
    if (knowledge.position_knowledge.num_x > count_columns)
      count_columns = knowledge.position_knowledge.num_x;

    knowledges.push_back(std::unique_ptr<WidgetKnowledge>{
                           new WidgetKnowledge(graphics_controller, this, knowledge, player_science)});
    knowledges.back()->hide();
    knowledges.back()->show();
    for(auto& need_knowledges : knowledge.necessary_knowledges)
    {
      PositionKnowledge need_know_pos = Science().get_knowledge(need_knowledges).position_knowledge;
      connections.push_back({need_know_pos, knowledge.position_knowledge});
    }
  }
  count_columns++;
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

void MenuScience::draw_connections()
{
  QPainter qp(this);
  qp.setPen(QPen{Qt::white, 3, Qt::SolidLine});
  for(Connection& connection : connections)
  {
    QPoint pos_begin_wid = pos_knowledge_widget(connection.begin);
    QPoint begin = pos_begin_wid + QPoint{size_block.width, size_block.height/2};

    QPoint pos_end_wid = pos_knowledge_widget(connection.end);
    QPoint end = pos_end_wid + QPoint{0, size_block.height/2};

    if(end.y() == begin.y())
    {
      qp.drawLine(begin, end);
      continue;
    }

    QPoint p1{end.x() - space_x/2, begin.y()};
    QPoint p2{end.x() - space_x/2, end.y()};

    int rad_rounding = std::min(space_x,space_y)/3;

    if(begin.y() > end.y())
    {
      qp.drawLine(begin, p1 - QPoint(rad_rounding, 0));
      qp.drawArc(QRectF{p1 - QPoint(2*rad_rounding, 2*rad_rounding), p1}, 0, -90 * 16);
      qp.drawLine(p1 - QPoint(0, rad_rounding), p2 + QPoint(0, rad_rounding));
      qp.drawArc(QRectF{p2, p2 + QPoint(2*rad_rounding, 2*rad_rounding)}, 90 * 16, 90 * 16);
      qp.drawLine(p2 + QPoint(rad_rounding, 0), end);
    }
    else
    {
      qp.drawLine(begin, p1 - QPoint(rad_rounding, 0));
      qp.drawArc(QRectF{p1 - QPoint(2*rad_rounding, 0),
                        p1 + QPoint(0, 2*rad_rounding)}, 0, 90 * 16);
      qp.drawLine(p1 + QPoint(0, rad_rounding), p2 - QPoint(0, rad_rounding));
      qp.drawArc(QRectF{p2 - QPoint(0, 2*rad_rounding),
                        p2 + QPoint(2*rad_rounding, 0)}, 180 * 16, 90 * 16);
      qp.drawLine(p2 +QPoint(rad_rounding, 0), end);
    }
  }
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

void MenuScience::draw_queue()
{
  auto& queue = player_science->get_queue_science();
  if(queue.size() < 2)
    return;

  QPainter qp(this);
  qp.setPen(QPen{Qt::white});

  auto science = Science();
  for(size_t i{1}; i < queue.size(); ++i)
  {
    auto pos_knowledge = science.get_knowledge(queue[i]).position_knowledge;
    QPoint pos_rect = pos_knowledge_widget(pos_knowledge) + QPoint{size_block.width, 0};
    QPoint size_rect{size_block.height/4, size_block.height/4};
    QRect rect{pos_rect, pos_rect+size_rect};

    qp.drawEllipse(rect);
    std::stringstream ss;
    ss << i;
    qp.drawText(rect, Qt::AlignCenter, QString::fromStdString(ss.str()));
  }
}

void MenuScience::click(QPoint pos)
{
  if(point_in_rect(rect_but_close(), pos))
    graphics_controller->close_menu_science();
}

void MenuScience::set_geometry_widgets()
{
  for(auto& knowledge : knowledges)
  {
    auto pos_knowledge = knowledge->get_knowledge().position_knowledge;

    QPoint pos = pos_knowledge_widget(pos_knowledge);
    knowledge->set_geometry(pos, size_block);
  }
}

int MenuScience::end_widgets()
{
  return count_columns*(space_x + size_block.width) + init_space_x*2 - space_x;
}

QPoint MenuScience::pos_knowledge_widget(PositionKnowledge pos) const
{
  return QPoint{pos.num_x*(space_x + size_block.width) + init_space_x + indent_x,
        pos.num_y*(space_y + size_block.height) + init_space_y};
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
