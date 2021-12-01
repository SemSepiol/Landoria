#include "MenuTypeMap.h"

MenuTypeMap::MenuTypeMap(IMenuInWindowGraphicsController* _graphics_controller, IMap* _map)
  : IMenuTypeMap{_graphics_controller->window()}, graphics_controller{_graphics_controller},
    map{_map}, type_map{_map->get_type_map()}
{
  QWidget::setMouseTracking(true);
}

void MenuTypeMap::set_geometry(QPoint pos, Size size)
{
  QWidget::setGeometry(pos.x(), pos.y(), size.width, size.height);
}

void MenuTypeMap::set_type(size_t i)
{
  types_list.reset();
  if(type_work == Overlay)
    type_map.overplay = v_overlay()[i];
  else if(type_work == TypeContent)
    type_map.type_content = v_type_content()[i];
  map->set_type_map(type_map);
  type_work = Nothing;
}

void MenuTypeMap::paintEvent(QPaintEvent* event)
{
  Q_UNUSED(event)
  draw();
  draw_notvisible();
  draw_other_landscapes();
}

void MenuTypeMap::mousePressEvent(QMouseEvent *event)
{
  mouse_pos_clicked = event->pos();
}

void MenuTypeMap::mouseReleaseEvent(QMouseEvent* event)
{
  QPoint mouse_move = event->pos() - mouse_pos_clicked;
  if(abs(mouse_move.x()) > 5 or abs(mouse_move.y()) > 5)
    return;
  click(event->pos());
}


void MenuTypeMap::draw()
{
  QPainter qp(this);
  qp.setPen(QPen(Qt::white, 2));
  QPoint p1;
  QPoint p2;

  auto fact_str = FactoryString();

  qp.drawText(text_overlay(), Qt::AlignBottom, "Активное наложение:");
  qp.fillRect(wid_overlay(), QBrush(Qt::gray));
  qp.drawRect(wid_overlay());
  qp.drawText(wid_overlay(), Qt::AlignCenter,
              QString::fromStdString(fact_str.typemap_overlay_string(type_map.overplay)));
  p1 = (wid_overlay().topRight() + wid_overlay().bottomRight())/2;
  p2 = wid_overlay().bottomRight() - QPoint{wid_overlay().height()/2, 0};
  qp.drawLine(p1, p2);

  qp.drawText(text_icons(), Qt::AlignBottom, "Отображение значков:");
  qp.fillRect(wid_icons(), QBrush(Qt::gray));
  qp.drawRect(wid_icons());
  qp.drawText(wid_icons(), Qt::AlignCenter,
              QString::fromStdString(fact_str.typemap_typecontent_string(type_map.type_content)));
  p1 = (wid_icons().topRight() + wid_icons().bottomRight())/2;
  p2 = wid_icons().bottomRight() - QPoint{wid_icons().height()/2, 0};
  qp.drawLine(p1, p2);
}

void MenuTypeMap::draw_notvisible()
{
  QPainter qp(this);
  qp.setPen(QPen(Qt::white, 2));

  if(type_map.show_notvisible)
    qp.setBrush(Qt::white);

  qp.drawText(text_notvisible(), Qt::AlignVCenter, "Туман войны");
  QRect rect_notv = wid_notvisible();
  qp.drawEllipse(rect_notv.center(), rad_wid_notvisible(), rad_wid_notvisible());
}

void MenuTypeMap::draw_other_landscapes()
{
  QPainter qp(this);
  qp.setPen(QPen(Qt::white, 2));

  if(type_map.show_other_landscapes)
    qp.setBrush(Qt::white);

  qp.drawText(text_other_landscapes(), Qt::AlignVCenter, "Особенности");
  QRect rect_ol = wid_other_landscapes();
  qp.drawEllipse(rect_ol.center(), rad_wid_other_landscapes(), rad_wid_other_landscapes());
}

void MenuTypeMap::click(QPoint pos)
{
  types_list.reset();
  type_work = Nothing;
  if(wid_overlay().contains(pos))
  {
    type_work = Overlay;
    do_tipes_list();
    return;
  }
  else if(wid_icons().contains(pos))
  {
    type_work = TypeContent;
    do_tipes_list();
    return;
  }
  else if(point_in_circle(wid_notvisible().center(), rad_wid_notvisible(), pos))
    type_map.show_notvisible = !type_map.show_notvisible;
  else if(point_in_circle(wid_other_landscapes().center(), rad_wid_other_landscapes(), pos))
    type_map.show_other_landscapes = !type_map.show_other_landscapes;
  else
    return;

  map->set_type_map(type_map);
  update();
}

void MenuTypeMap::do_tipes_list()
{
  types_list.reset(new TypesList{this});
  if(type_work == Overlay)
  {
    std::vector<QString> text;
    for(auto overlay : v_overlay())
      text.push_back(QString::fromStdString(FactoryString().typemap_overlay_string(overlay)));
    types_list->set_text(text);
    types_list->set_geometry(wid_overlay().topLeft(), {wid_overlay().width(), wid_overlay().height()});
  }
  else if(type_work == TypeContent)
  {
    std::vector<QString> text;
    for(auto type_c : v_type_content())
      text.push_back(QString::fromStdString(FactoryString().typemap_typecontent_string(type_c)));
    types_list->set_text(text);
    types_list->set_geometry(wid_icons().topLeft(), {wid_icons().width(), wid_icons().height()});
  }
  else
  {
    types_list.reset();
    return;
  }

  types_list->hide();
  types_list->show();
}

std::vector<TypeMap::Overlay> MenuTypeMap::v_overlay() const
{
  std::vector<TypeMap::Overlay> overlay;
  overlay.push_back(TypeMap::NoOverlay);
  overlay.push_back(TypeMap::Political);
  overlay.push_back(TypeMap::HighlightResources);
  return overlay;
}

std::vector<TypeMap::TypeContent> MenuTypeMap::v_type_content() const
{
  std::vector<TypeMap::TypeContent> type_c;
  type_c.push_back(TypeMap::All);
  type_c.push_back(TypeMap::Nothing);
  type_c.push_back(TypeMap::Units);
  type_c.push_back(TypeMap::Resources);
  type_c.push_back(TypeMap::Building);
  return type_c;
}

QRect MenuTypeMap::text_icons() const
{
  return QRect{width()/10, 0,  width()*8/10, height()/7};
}

QRect MenuTypeMap::wid_icons() const
{
  return QRect{width()/10, height()/6,  width()*8/10, height()/7};
}

QRect MenuTypeMap::text_overlay() const
{
  return QRect{width()/10, 2*height()/6, width()*8/10, height()/7};
}

QRect MenuTypeMap::wid_overlay() const
{
  return QRect{width()/10, 3*height()/6, width()*8/10, height()/7};
}

QRect MenuTypeMap::text_notvisible() const
{ 
  return QRect{width()/10, 4*height()/6, width()*3/4, height()/6};
}

QRect MenuTypeMap::wid_notvisible() const
{
  return QRect{width()*3/4, 4*height()/6, width()/4, height()/6};
}

int MenuTypeMap::rad_wid_notvisible() const
{
  return wid_notvisible().width()/6;
}

QRect MenuTypeMap::text_other_landscapes() const
{
  return QRect{width()/10, 5*height()/6, width()*3/4, height()/6};
}

QRect MenuTypeMap::wid_other_landscapes() const
{
  return QRect{width()*3/4, 5*height()/6, width()/4, height()/6};
}

int MenuTypeMap::rad_wid_other_landscapes() const
{
  return wid_other_landscapes().width()/6;
}

bool MenuTypeMap::point_in_circle(QPoint center_circle, int rad_circle, QPoint point)
{
  QPointF distance = point-center_circle;
  int a = int(std::sqrt(distance.x()*distance.x() + distance.y()*distance.y()));
  return a <= rad_circle;
}

