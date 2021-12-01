#include "BottomMenu.h"

BottomMenu::BottomMenu(IMenuInWindowGraphicsController* _graphic_controller)
  : AMenuInWindow(_graphic_controller)
{}

void BottomMenu::update_infofm(Cell* _cell)
{
  cell = _cell;
  update();
}

void BottomMenu::del_inform()
{
  cell = nullptr;
  update();
}

QRect BottomMenu::open_type_map_butt() const
{
  QPoint topleft = QPoint{width_menu - 3*height_menu, 0};
  QPoint bottomright = QPoint{width_menu - 2*height_menu, height_menu};
  return QRect{topleft, bottomright};
}

void BottomMenu::mouseMoveEvent(QMouseEvent *event)
{
  if(event->pos().y() > height_menu - 5)
    graphics_controller->move_map({0, -50});
}

void BottomMenu::draw()
{
  draw_text();
  QPainter qp(this);

  QPixmap pixmap = FactoryPixmap().create_pixmap_for_minimap();
  QRectF source = FactoryPixmap().size_picture_content();
  qp.drawPixmap(show_minimap_butt(), pixmap, source);

  QPixmap pixmap2 = FactoryPixmap().create_pixmap_for_nextmotion();
  qp.drawPixmap(next_move_butt(), pixmap2, source);

  QPixmap pixmap3 = FactoryPixmap().create_pixmap_for_type_map();
  qp.drawPixmap(open_type_map_butt(), pixmap3, source);

  QPen pen{Qt::white, 2, Qt::SolidLine};
  qp.setPen(pen);
  QPoint p1 = QPoint{0, 0};
  QPoint p2 = QPoint{width_menu, 0};
  qp.drawLine(p1, p2);
}

void BottomMenu::click(QPoint pos)
{
  if (point_in_rect(show_minimap_butt(), pos))
    graphics_controller->show_minimap();
  else if (point_in_rect(next_move_butt(), pos))
    graphics_controller->next_move();
  else if (point_in_rect(open_type_map_butt(), pos))
    graphics_controller->click_open_menu_type_map();
}

void BottomMenu::draw_text()
{
  if(!cell)
    return;
  ControlContents cc{cell};
  std::stringstream ss;
  FactoryString Fstr = FactoryString();

  ss << "Ландшавт: " << Fstr.landscape_string(cc.get_main_landscape());
  OtherLandscapes otherland = cc.get_other_landscape();
  if(otherland != OtherLandscapes::Nothing)
    ss << ", " << Fstr.landscape_string(otherland);

  if(cc.get_country() != Countries::Nothing)
    ss << " | Страна: " << Fstr.country_string(cc.get_country());

  if(cc.has_resource())
    ss << " | Ресурс: " << Fstr.resource_string(cc.get_resource()) << " " << cc.get_count_of_res();

  if(cc.has_building())
    ss << " | Строение: " << Fstr.build_string(cc.get_building()->what_building_I());

  auto units = cc.get_units();
  if(units.size())
  {
    ss << " | Юниты: " << Fstr.unit_string(units[0]);
    for(size_t i{1}; i < units.size(); ++i)
      ss << ", " << Fstr.unit_string(units[i]);
    ss << " - Страна " << Fstr.country_string(cc.get_country_units());
  }

  QPainter qp(this);
  QPen pen{Qt::white, 2, Qt::SolidLine};
  qp.setPen(pen);
  QRect rect{0, 0, show_minimap_butt().topLeft().x(), height()};
  qp.drawText(rect, Qt::AlignVCenter, QString::fromStdString(ss.str()));
}

QRect BottomMenu::show_minimap_butt() const
{
  QPoint topleft = QPoint{width_menu - 2*height_menu, 0};
  QPoint bottomright = QPoint{width_menu - height_menu, height_menu};
  return QRect{topleft, bottomright};
}

QRect BottomMenu::next_move_butt() const
{
  QPoint topleft = QPoint{width_menu - height_menu, 0};
  QPoint bottomright = QPoint{width_menu, height_menu};
  return QRect{topleft, bottomright};
}
