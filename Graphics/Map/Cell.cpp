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
    draw_cell(point);
  }
  else{
    auto overplay = map->get_type_map().overplay;
    ControlContents cc{this};

    if(overplay == TypeMap::NoOverlay ||
       (overplay == TypeMap::Political && country == Countries::Nothing) ||
       (overplay == TypeMap::HighlightResources && !cc.has_resource()))
      draw_landscape(point);

    draw_cell(point);
    draw_contents(point);
  }
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
  auto map_type_content = map->get_type_map().type_content;
  int num_circle = calculations()->point_in_circle(pos, count_units());

  if (num_circle == -1)
    return nullptr;

  ControlContents control_contents{this};

  if ((map_type_content == TypeMap::All || map_type_content == TypeMap::Units) &&
      num_circle < 4)
  {
    if (control_contents.count_units() < num_circle+1)
      return nullptr;

    int counter = 0;
    for(size_t j{0}; j < contents.size(); ++j)
      if(contents[j].content->what_content_I() == Contents::Unit)
        if(++counter == num_circle+1)
          return contents[j].content.get();
  }
  else if((map_type_content == TypeMap::All && num_circle == 4) ||
          (map_type_content == TypeMap::Resources && num_circle == 0))
  {
    if (!control_contents.has_resource())
      return nullptr;

    for(size_t j{0}; j < contents.size(); ++j)
      if(contents[j].content->what_content_I() == Contents::Resource)
        return contents[j].content.get();
  }
  else if((map_type_content == TypeMap::All && num_circle == 5) ||
          (map_type_content == TypeMap::Building && num_circle == 0))
  {
    if (!control_contents.has_building())
      return nullptr;

    for(size_t j{0}; j < contents.size(); ++j)
      if(contents[j].content->what_content_I() == Contents::Building)
        return contents[j].content.get();
  }

  throw std::runtime_error("Can't find content");
}

int Cell::count_units()
{
  ControlContents cc{this};
  return cc.count_units();
}

void Cell::update_pixmap_for_main_landscape()
{
  pixmap_for_main_landscape = FactoryPixmap().create_pixmap_for_main_landscape(mainlandscape);
}

void Cell::update_pixmap_for_other_landscape()
{
  pixmap_for_other_landscape = FactoryPixmap().create_pixmap_for_other_landscape(otherlandscape);
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

  if(show_cell == ShowCell::NotVisible && map->get_type_map().show_notvisible)
  {
    qp.setBrush(QBrush(QColor(0, 0, 0, 200)));
  }

  auto overplay = map->get_type_map().overplay;
  ControlContents cc{this};
  if(overplay == TypeMap::Political && country != Countries::Nothing)
    qp.setBrush(FactoryColor().country_color(country));
  else if (show_cell != ShowCell::FogOfWar && overplay == TypeMap::HighlightResources && cc.has_resource())
    qp.setBrush(Qt::green);

  qp.setPen(QPen(Qt::black, calc->hexagon_height()/10));

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

  QRectF source = FactoryPixmap().size_picture_landscape();
  QRectF target{1.* (point.x() - calc->hexagon_side()), 1.* (point.y() - calc->hexagon_side()),
        calc->hexagon_side()*2., calc->hexagon_side()*2.};
  qp.drawPixmap(target, pixmap_for_main_landscape, source);

  if(map->get_type_map().show_other_landscapes)
  {
    qp.drawPixmap(target, pixmap_for_other_landscape, source);
  }
}

void Cell::draw_contents(QPoint point)
{
  auto map_type_content = map->get_type_map().type_content;
  if(map_type_content == TypeMap::Nothing)
    return;

  int count_drawn_unit = 0;
  for(size_t i{0}; i < contents.size(); ++i)
  {
    Contents type_content = contents[i].content->what_content_I();
    if(type_content != Contents::Resource && show_cell == ShowCell::NotVisible)
      continue;

    if(!contents[i].show_content)
      continue;

    if(type_content == Contents::Unit)
      draw_unit(&contents[i], point, count_drawn_unit++);
    else if (type_content == Contents::Resource)
      draw_resource(&contents[i], point);
    else if (type_content == Contents::Building)
      draw_building(&contents[i], point);
  }
}

void Cell::draw_fog_of_war(QPoint point)
{
  Calculations* calc = calculations();
  QWidget* win = window();
  QPainter qp(win);

  QPixmap pixmap = FactoryPixmap().create_pixmap_for_fog_of_war();
  QRectF source = FactoryPixmap().size_picture_landscape();
  QRectF target{1.* (point.x() - calc->hexagon_side()), 1.* (point.y() - calc->hexagon_side()),
        calc->hexagon_side()*2., calc->hexagon_side()*2.};
  qp.drawPixmap(target, pixmap, source);
}

void Cell::draw_highlight(QPoint point)
{
  int rad = calculations()->circle_radius();

  QPainter qp(window());
  QPen pen(Qt::blue, int(rad/5), Qt::SolidLine);
  qp.setBrush(QBrush (Qt::blue));
  qp.drawEllipse(point, rad*6/5, rad*6/5);
}

void Cell::draw_borders(QPoint point)
{
  if(country == Countries::Nothing)
    return;
  if(show_cell == ShowCell::FogOfWar)
    return;

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

void Cell::draw_unit(Content* content, QPoint point_cell, int count_drawn_unit)
{
  auto map_type_content = map->get_type_map().type_content;
  Calculations* calc = calculations();
  QPoint p;
  if(map_type_content == TypeMap::All || map_type_content == TypeMap::Units)
  {
    ControlContents cc{this};
    p = calc->point_circle_for_unit(count_drawn_unit, cc.count_units());
  }
  else
    return;

  if(content->highlight)
    draw_highlight(p + point_cell);
  content->content->draw(p + point_cell);
}

void Cell::draw_resource(Content* content, QPoint point_cell)
{
  auto map_type_content = map->get_type_map().type_content;
  Calculations* calc = calculations();

  QPoint p;
  if(map_type_content == TypeMap::All || map_type_content == TypeMap::Resources)
    p = calc->point_circle_for_res();
  else
    return;
  content->content->draw(point_cell + p);
}

void Cell::draw_building(Content* content, QPoint point_cell)
{
  auto map_type_content = map->get_type_map().type_content;
  Calculations* calc = calculations();

  QPoint p;
  if(map_type_content == TypeMap::All || map_type_content == TypeMap::Building)
    p = calc->point_circle_for_build();
  else
    return;

  content->content->draw(point_cell + p);
}

