#include "UpperMenu.h"
#include <iostream>

UpperMenu::UpperMenu(IMenuInWindowGraphicsController* _graphic_controller)
  : AMenuInWindow(_graphic_controller)
{
  QWidget::setMouseTracking(true);
}

void UpperMenu::update_infofm(IMenuTownPlayer* player)
{
  count_gold = player->get_gold_per_turn();
  count_science = player->get_science_per_turn();

  draw_res.clear();
  PlayerRes* player_res = player->get_player_res();
  for(int i{0}; i < CountInEnums().resources(); ++i)
  {
    if(Resources(i) == Resources::Fish || Resources(i) == Resources::Gold ||
       Resources(i) == Resources::Silver)
      continue;

    int count = player_res->get_resource(Resources(i));
    draw_res.push_back({Resources(i), count});
  }
  update();
}

void UpperMenu::mouseMoveEvent(QMouseEvent *event)
{
  graphics_controller->del_inform_widget();
  if(enable_move_map)
    if(event->pos().y() < 5)
      graphics_controller->move_map({0, 50});
}

void UpperMenu::set_enable_move_map(bool _enable_move_map)
{
  enable_move_map = _enable_move_map;
}

void UpperMenu::draw()
{
  draw_gold();
  draw_science();
  draw_resource();

  QPainter qp(this);

  QPixmap pixmap = FactoryPixmap().create_pixmap_for_exit();
  QRectF source = FactoryPixmap().size_picture_content();
  qp.drawPixmap(exit_butt(), pixmap, source);

  QPen pen{Qt::white, 2, Qt::SolidLine};
  qp.setPen(pen);
  QPoint p1 = QPoint{0, height_menu};
  QPoint p2 = QPoint{width_menu, height_menu};
  qp.drawLine(p1, p2);

  qp.drawLine(rect_science_pic().bottomRight(), rect_science_pic().topRight());
}

QRect UpperMenu::exit_butt() const
{
  QPoint topleft = QPoint{width_menu - height_menu, 0};
  QPoint bottomright = QPoint{width_menu, height_menu};
  return QRect{topleft, bottomright};
}

void UpperMenu::click(QPoint pos)
{
  if (point_in_rect(exit_butt(), pos))
    graphics_controller->exit();
}

void UpperMenu::draw_gold()
{
  QPainter qp(this);
  QColor color = Qt::white;
  if(count_gold < 0)
    color = Qt::red;

  qp.setPen(QPen{color, 2, Qt::SolidLine});
  QRect rect = rect_gold_pic();
  QPixmap pixmap = FactoryPixmap().create_pixmap_for_gold();
  QRectF source = FactoryPixmap().size_picture_gold();
  qp.drawPixmap(rect, pixmap, source);

  std::stringstream ss;

  if(count_gold < 0)
    ss << "-";
  else if(count_gold > 0)
    ss << "+";

  ss << count_gold;
  QRect rect2 = rect_gold();
  qp.drawText(rect2, Qt::AlignVCenter | Qt::AlignRight,  QString::fromStdString(ss.str()));
}

void UpperMenu::draw_science()
{
  QPainter qp(this);
  QColor color = Qt::white;
  if(count_science < 0)
    color = Qt::red;

  qp.setPen(QPen{color, 2, Qt::SolidLine});
  QRect rect = rect_science_pic();
  QPixmap pixmap = FactoryPixmap().create_pixmap_for_science();
  QRectF source = FactoryPixmap().size_picture_gold();
  qp.drawPixmap(rect, pixmap, source);

  std::stringstream ss;

  if(count_science < 0)
    ss << "-";
  else if(count_science > 0)
    ss << "+";

  ss << count_science;
  QRect rect2 = rect_science();
  qp.drawText(rect2, Qt::AlignVCenter | Qt::AlignRight,  QString::fromStdString(ss.str()));
}

void UpperMenu::draw_resource()
{
  QPainter qp(this);

  for(size_t i{0}; i < draw_res.size(); ++i)
  {
    QColor color = Qt::white;
    if(draw_res[i].count_res < 0)
      color = Qt::red;

    qp.setPen(QPen{color, 2, Qt::SolidLine});
    QRect rect = rect_res_pic(i);
    QPixmap pixmap = FactoryPixmap().create_pixmap_for_res(draw_res[i].res);
    QRectF source = FactoryPixmap().size_picture_content();
    qp.drawPixmap(rect, pixmap, source);

    std::stringstream ss;

    if(draw_res[i].count_res < 0)
      ss << "-";
    else if(draw_res[i].count_res > 0)
      ss << "+";

    ss << draw_res[i].count_res;
    QRect rect2 = rect_res(i);
    qp.drawText(rect2, Qt::AlignVCenter | Qt::AlignRight,  QString::fromStdString(ss.str()));
  }
}

QRect UpperMenu::rect_gold() const
{
  return QRect{0, 0, height() * (count_simbols(count_gold)+1)/4, height()};
}

QRect UpperMenu::rect_gold_pic() const
{
  return QRect{rect_gold().bottomRight().x(), height()/4, height()/2, height()/2};
}

QRect UpperMenu::rect_science() const
{
  return QRect{rect_gold_pic().bottomRight().x(), 0,
        height() * (count_simbols(count_science)+1)/4, height()};
}

QRect UpperMenu::rect_science_pic() const
{
  return QRect{rect_science().bottomRight().x(), height()/4, height()/2, height()/2};
}

QRect UpperMenu::rect_res(size_t num) const
{
  if(num == 0)
    return QRect{rect_science_pic().bottomRight().x(), 0,
          height() * (count_simbols(draw_res[num].count_res)+1)/4, height()};
  return QRect{rect_res_pic(num-1).bottomRight().x(), 0,
        height() * (count_simbols(draw_res[num].count_res)+1)/4, height()};
}

QRect UpperMenu::rect_res_pic(size_t num) const
{
  return QRect{rect_res(num).bottomRight().x(), height()/4, height()/2, height()/2};
}

int UpperMenu::count_simbols(int a) const
{
  a = std::abs(a);
  int count = 0;
  while(a != 0){
    a /= 10;
    ++count;
  }
  if(count)
    return count;
  return 1;
}
