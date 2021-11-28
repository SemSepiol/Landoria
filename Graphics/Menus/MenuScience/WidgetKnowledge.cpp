#include "WidgetKnowledge.h"
#include <iostream>

WidgetKnowledge::WidgetKnowledge(IMenuInWindowGraphicsController* _graphics_controller,
                                 IMenuScience* _menu_science,
                                 Knowledge _knowledge, PlayerScience* _player_sience)
  :QWidget{_graphics_controller->window()}, graphics_controller{_graphics_controller},
    menu_science{_menu_science}, knowledge{_knowledge}, player_sience{_player_sience}
{}


void WidgetKnowledge::set_geometry(QPoint pos, Size size)
{
  QWidget::setGeometry(pos.x(), pos.y(), size.width, size.height);
}

const Knowledge& WidgetKnowledge::get_knowledge() const
{
  return knowledge;
}

void WidgetKnowledge::paintEvent(QPaintEvent* event)
{
  Q_UNUSED(event)
  draw();
}

void WidgetKnowledge::mousePressEvent(QMouseEvent* event)
{
  mouse_pos_clicked = event->pos();
}

void WidgetKnowledge::mouseReleaseEvent(QMouseEvent* event)
{
  QPoint mouse_move = event->pos() - mouse_pos_clicked;
  if(abs(mouse_move.x()) > 5 or abs(mouse_move.y()) > 5)
    return;
  click(event->pos());
}

void WidgetKnowledge::wheelEvent(QWheelEvent *event)
{
  menu_science->wheel_scroll(event->angleDelta().y());
}

void WidgetKnowledge::draw()
{
  draw_wid();
  draw_knowledge_pixmap();
  draw_text();
  draw_open();
}

void WidgetKnowledge::draw_wid()
{
  QPainter qp(this);

  qp.setPen(Qt::white);
  qp.drawRect(QRect{0, 0, width(), height()});
  if(player_sience->get_queue_science().size() > 0 &&
     player_sience->get_queue_science()[0] == knowledge.name_knowledge)
    qp.fillRect(QRect{0, 0, width(), height()}, QBrush(QColor(Qt::yellow)));
  else if(player_sience->is_knowledge_open(knowledge.name_knowledge))
    qp.fillRect(QRect{0, 0, width(), height()}, QBrush(QColor(Qt::green)));
}

void WidgetKnowledge::draw_knowledge_pixmap()
{
  QPainter qp(this);

  QRect rect_knowledge = rect_knowledge_pixmap();
  QPixmap knowledge_pixmap = FactoryPixmap().create_pixmap_for_knowledges(knowledge.name_knowledge);
  qp.drawPixmap(rect_knowledge, knowledge_pixmap);
}

void WidgetKnowledge::draw_text()
{
  QPainter qp(this);
  qp.setPen(Qt::white);

  QString text = QString::fromStdString(FactoryString().knowledge_string(knowledge.name_knowledge));
  qp.drawText(rect_text(), Qt::AlignVCenter, text);
}

void WidgetKnowledge::draw_open()
{
  QPainter qp(this);

  auto factory_pixmap = FactoryPixmap();

  int num = 0;
  for(auto& res : knowledge.resources)
  {
    QRect rect = rect_open_pixmap(num++);
    QPixmap pixmap = factory_pixmap.create_pixmap_for_res(res);
    qp.drawPixmap(rect, pixmap);
  }
  for(auto& building : knowledge.buildings)
  {
    QRect rect = rect_open_pixmap(num++);
    QPixmap pixmap = factory_pixmap.create_pixmap_for_building(building);
    qp.drawPixmap(rect, pixmap);
  }
  for(auto& town_building : knowledge.town_buildings)
  {
    QRect rect = rect_open_pixmap(num++);
    QPixmap pixmap = factory_pixmap.create_pixmap_for_town_building(town_building.town_building);
    qp.drawPixmap(rect, pixmap);
  }
  for(auto& unit : knowledge.units)
  {
    QRect rect = rect_open_pixmap(num++);
    QPixmap pixmap = factory_pixmap.create_pixmap_for_unit(unit);
    qp.drawPixmap(rect, pixmap);
  }
}

void WidgetKnowledge::click(QPoint pos)
{
  Q_UNUSED(pos)
  if(!player_sience->is_knowledge_open(knowledge.name_knowledge))
    player_sience->set_study_knowledge(knowledge.name_knowledge);
  menu_science->update();
}

QRect WidgetKnowledge::rect_knowledge_pixmap() const
{
  return QRect{0, 0, height(), height()};
}

QRect WidgetKnowledge::rect_text() const
{
  return QRect{rect_knowledge_pixmap().topRight(), QPoint{width(), height()/3}};
}

QRect WidgetKnowledge::rect_open_pixmap(int num) const
{
  QPoint pos{rect_text().bottomLeft()};
  int rect_side = height() - pos.y();
  int space = rect_side/5;
  pos += QPoint(num*(rect_side+space) + space, 0);
  return QRect{pos.x(), pos.y(), rect_side, rect_side};
}
