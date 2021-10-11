#include "Cell.h"
#include <iostream>

Cell::Cell(IMap* map)
  :map{map}
{}

void Cell::draw(QPoint point)
{
  if(show_cell == ShowCell::FogOfWar)
  {
    draw_fog_of_war(point);
    return;
  }

  Calculations* calc = calculations();

  QPoint p1 = point - calc->point_0();
  QPoint p2 = point - calc->point_60();
  QPoint p3 = point - calc->point_120();
  QPoint p4 = point - calc->point_180();
  QPoint p5 = point - calc->point_240();
  QPoint p6 = point - calc->point_300();

  QWidget* win = window();

  draw_landscape(point);
  QPainter qp(win);
  QPen pen(Qt::black, calc->hexagon_height()/10, Qt::SolidLine);
  if(show_cell == ShowCell::NotVisible)
  {
    qp.setBrush(QBrush(QColor(0, 0, 0, 200)));
  }

  qp.setPen(pen);
  QPointF points[6] {p1, p2, p3, p4, p5, p6};
  qp.drawPolygon(points, 6);

  draw_contents(point);

}

QWidget* Cell::window() const
{
  return map->window();
}

Calculations* Cell::calculations() const
{
  return map->calculations();
}

IContent* Cell::click(QPoint pos)
{
  int num_circle = calculations()->point_in_circle(pos);

  if (num_circle == -1)
    return nullptr;

  ControlContents control_contents{this};

  if (num_circle < 4)
  {
    if (control_contents.count_units() < num_circle+1)
      return nullptr;

    int counter = 0;
    for(size_t j{0}; j < contents.size(); ++j)
      if(contents[j].content->what_content_I() == Contents::Unit)
        if(++counter == num_circle+1)
          return contents[j].content.get();
  }

  if(num_circle == 4)
  {
    if (!control_contents.has_resource())
      return nullptr;

    for(size_t j{0}; j < contents.size(); ++j)
      if(contents[j].content->what_content_I() == Contents::Resource)
        return contents[j].content.get();
  }

  if(num_circle == 5)
  {
    if (!control_contents.has_building())
      return nullptr;

    for(size_t j{0}; j < contents.size(); ++j)
      if(contents[j].content->what_content_I() == Contents::Building)
        return contents[j].content.get();
  }

  throw std::runtime_error("Can't find content");
}

void Cell::draw_landscape(QPoint point)
{
  Calculations* calc = calculations();
  QWidget* win = window();
  QPainter qp(win);

  if (!is_there_main_landscape)
    throw std::runtime_error("The main landscape is not set in the cell");

  QPixmap pixmap = FactoryPixmap().create_pixmap_for_main_landscape(mainlandscape);
  QRectF source = FactoryPixmap().size_picture_landscape();
  QRectF target{1.* (point.x() - calc->hexagon_side()), 1.* (point.y() - calc->hexagon_side()),
        calc->hexagon_side()*2., calc->hexagon_side()*2.};
  qp.drawPixmap(target, pixmap, source);

  QPixmap pixmap2 = FactoryPixmap().create_pixmap_for_other_landscape(otherlandscape);
  qp.drawPixmap(target, pixmap2, source);
}

void Cell::draw_contents(QPoint point)
{
  Calculations* calc = calculations();
  int count_drawn_unit = 0;
  for(size_t i{0}; i < contents.size(); ++i)
  {
    Contents type_content = contents[i].content->what_content_I();
    if(type_content != Contents::Resource && show_cell == ShowCell::NotVisible)
      continue;

    if(!contents[i].show_content)
      continue;

    if(type_content == Contents::Unit){
      QPoint p = calc->point_circle_for_unit(count_drawn_unit) + point;
      if(contents[i].highlight)
        draw_highlight(p);
      contents[i].content->draw(p);
      count_drawn_unit++;
    }
    else if (type_content == Contents::Resource){
      QPoint p = calc->point_circle_for_res();
      contents[i].content->draw(point + p);
    }
    else if (type_content == Contents::Building) {
      QPoint p = calc->point_circle_for_build();
      contents[i].content->draw(point + p);
    }
  }
}

void Cell::draw_fog_of_war(QPoint point)
{

}

void Cell::draw_highlight(QPoint point)
{
  int rad = calculations()->circle_radius()+5;

  QPainter qp(window());
  QPen pen(Qt::blue, 10, Qt::SolidLine);
  qp.setBrush(QBrush (Qt::blue));
  qp.drawEllipse(point, rad, rad);
}
