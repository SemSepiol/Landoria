#include "Cell.h"
#include <iostream>

Cell::Cell(IMap* map)
  :map{map}
{}

void Cell::draw(QPoint point)
{
//  std::cout << int(country) << std::endl;
  if(show_cell == ShowCell::FogOfWar)
  {
    draw_fog_of_war(point);
    return;
  }

  draw_landscape(point);
  draw_contents(point);
  draw_cell(point);
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

void Cell::draw_cell(QPoint point)
{
  Calculations* calc = calculations();

  QPoint p1 = point - calc->point_0();
  QPoint p2 = point - calc->point_60();
  QPoint p3 = point - calc->point_120();
  QPoint p4 = point - calc->point_180();
  QPoint p5 = point - calc->point_240();
  QPoint p6 = point - calc->point_300();

  QWidget* win = window();
  QPainter qp(win);
  QPen pen(Qt::black, calc->hexagon_height()/10, Qt::SolidLine);
  if(show_cell == ShowCell::NotVisible)
  {
    qp.setBrush(QBrush(QColor(0, 0, 0, 200)));
  }

  qp.setPen(pen);
  QPointF points[6] {p1, p2, p3, p4, p5, p6};
  qp.drawPolygon(points, 6);
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

void Cell::draw_borders(QPoint point)
{
//  if(country == Countries::Nothing)
//    return;

  Calculations* calc = calculations();
  int width_border = calc->hexagon_height()/20;
  QPainter qp(window());
  QPen pen(FactoryColor().country_color(country), width_border, Qt::SolidLine);
  qp.setPen(pen);

  QPoint p1 = point + calc->point_0()   + QPoint{0, width_border/2};
  QPoint p2 = point + calc->point_60()  + QPoint{width_border/2, width_border/2};
  QPoint p3 = point + calc->point_120() + QPoint{width_border/2, -width_border/2};
  QPoint p4 = point + calc->point_180() + QPoint{0, -width_border/2};
  QPoint p5 = point + calc->point_240() + QPoint{-width_border/2, -width_border/2};
  QPoint p6 = point + calc->point_300() + QPoint{-width_border/2, width_border/2};

  std::vector<QLine> lines;
  std::vector<QPoint> ends;
  Position my_pos = map->indexes_by_cell(this);
  auto neighbors = map->adjacent_cells(my_pos);
//  std::cout << "---" << my_pos.x << " " << my_pos.y << std::endl;
  for(auto pos_cell : neighbors)
  {
//    std::cout << pos_cell.x << " " << pos_cell.y << " " << int(cell_country(pos_cell)) << std::endl;
    if(cell_country(pos_cell) == country)
      continue;

    if(pos_cell.y == my_pos.y)
    {
      if(pos_cell.x < my_pos.x)
      {
        lines.push_back({p2, p3});
        ends.push_back(p2);
        ends.push_back(p3);
      }
      else if (pos_cell.x > my_pos.x)
      {
        lines.push_back({p5, p6});
        ends.push_back(p5);
        ends.push_back(p6);
      }
    }
    else if(my_pos.y % 2 == 0)
    {
      if(pos_cell.y < my_pos.y)
      {
        if(pos_cell.x < my_pos.x)
        {
          lines.push_back({p1, p2});
          ends.push_back(p1);
          ends.push_back(p2);
        }
        else if (pos_cell.x == my_pos.x)
        {
          lines.push_back({p6, p1});
          ends.push_back(p6);
          ends.push_back(p1);
        }
      }
      else
      {
        if(pos_cell.x < my_pos.x)
        {
          lines.push_back({p3, p4});
          ends.push_back(p3);
          ends.push_back(p4);
        }
        else if (pos_cell.x == my_pos.x)
        {
          lines.push_back({p4, p5});
          ends.push_back(p4);
          ends.push_back(p5);
        }
      }
    }
    else if(my_pos.y % 2 == 1)
    {
      if(pos_cell.y < my_pos.y)
      {
        if(pos_cell.x == my_pos.x)
        {
          lines.push_back({p1, p2});
          ends.push_back(p1);
          ends.push_back(p2);
        }
        else if (pos_cell.x > my_pos.x)
        {
          lines.push_back({p6, p1});
          ends.push_back(p6);
          ends.push_back(p1);
        }
      }
      else
      {
        if(pos_cell.x == my_pos.x)
        {
          lines.push_back({p3, p4});
          ends.push_back(p3);
          ends.push_back(p4);
        }
        else if (pos_cell.x > my_pos.x)
        {
          lines.push_back({p4, p5});
          ends.push_back(p4);
          ends.push_back(p5);
        }
      }
    }
  }

  for(auto line : lines)
    qp.drawLine(line);
}

Countries Cell::cell_country(Position pos_cell)
{
  ControlContents cc{map->icell_by_indexes(pos_cell)};
  return cc.get_country();
}



