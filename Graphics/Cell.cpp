#include "Cell.h"
#include <iostream>

Cell::Cell(IMap* map)
  :map{map}
{
}

void Cell::draw(QPoint point)
{
  if(!show_cell)
    return;

  Calculations* calc = calculations();

  QPoint p1 = point - calc->point_0();
  QPoint p2 = point - calc->point_60();
  QPoint p3 = point - calc->point_120();
  QPoint p4 = point - calc->point_180();
  QPoint p5 = point - calc->point_240();
  QPoint p6 = point - calc->point_300();

  QWidget* win = window();
  QPainter qp(win);

  QPen pen(Qt::black, 2, Qt::SolidLine);
  qp.setPen(pen);
  QPointF points[6] {p1, p2, p3, p4, p5, p6};
  qp.drawPolygon(points, 6);

  draw_landscape(point);
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
    if(!contents[i].show_content)
      continue;

    if(contents[i].content->what_content_I() == Contents::Unit){
      if (count_drawn_unit < 4){
        QPoint p = calc->point_circle_for_unit(count_drawn_unit);
        contents[i].content->draw(point + p);
      }
      count_drawn_unit++;
    }
    else if (contents[i].content->what_content_I() == Contents::Resource){
      QPoint p = calc->point_circle_for_res();
      contents[i].content->draw(point + p);
    }
    else if (contents[i].content->what_content_I() == Contents::Building) {
      QPoint p = calc->point_circle_for_build();
      contents[i].content->draw(point + p);
    }
  }
}

void ControlContents::set_main_landscape(MainLandscapes type_landscape)
{
//  if (cell->is_there_main_landscape)
//    throw std::runtime_error("set_main_landscape: There is already a landscape in the cell");

  cell->is_there_main_landscape = true;
  cell->mainlandscape = type_landscape;
}

void ControlContents::set_other_landscape(OtherLandscapes type_landscape)
{
//  if (cell->is_there_other_landscape)
//    throw std::runtime_error("set_other_landscape: There is already other landscape in the cell");

  cell->is_there_other_landscape = true;
  cell->otherlandscape = type_landscape;
}

IContent* ControlContents::add_resource(Resources type_resource)
{
  if (has_resource())
    throw std::runtime_error("add_resource: There is already a resource in the cell");
  cell->contents.push_back({FactoryRes().create_res(type_resource, cell)});
  return cell->contents[cell->contents.size()-1].content.get();
}

IContent* ControlContents::add_building(Buildings type_building)
{
  if (has_building())
    throw std::runtime_error("add_building: There is already a building in the cell");
  cell->contents.push_back({FactoryBuild().create_building(type_building, cell)});
  return cell->contents[cell->contents.size()-1].content.get();
}

IContent* ControlContents::add_unit(Units type_unit)
{
  if(count_units() == 4)
    throw std::runtime_error("add_unit: there are already 4 units in the cell");
  cell->contents.push_back({FactoryUnits().create_unit(type_unit, cell)});
  return cell->contents[cell->contents.size()-1].content.get();
}

void ControlContents::add_unit(IContent* unit)
{
  if (unit->what_content_I() != Contents::Unit)
    throw std::runtime_error("add_unit: It isn't unit");
  if(count_units() == 4)
    throw std::runtime_error("add_unit: there are already 4 units in the cell");
  cell->contents.push_back({unit});
}


void ControlContents::del_content(IContent* content)
{
  for(size_t i{0}; i < cell->contents.size(); ++i)
    if(cell->contents[i].content.get() == content){
      cell->contents.erase(cell->contents.begin() + i);
    }
}

IContent* ControlContents::pop_content(IContent* content)
{
  std::cout << content << std::endl;
  for(size_t i{0}; i < cell->contents.size(); ++i)
  {
    if(cell->contents[i].content.get() == content){
      IContent* temp{nullptr};
      temp = cell->contents[i].content.release();
      cell->contents.erase(cell->contents.begin() + i);
      return temp;
    }
  }
  throw std::runtime_error("pop_content: hasn't this constent");
}

MainLandscapes ControlContents::get_landscape() const
{
  if(!cell->is_there_main_landscape)
    throw std::runtime_error("landscape is not set");
  return cell->mainlandscape;
}

Resources ControlContents::get_resource() const
{
  for(size_t i{0}; i < cell->contents.size(); ++i)
    if(cell->contents[i].content->what_content_I() == Contents::Resource)
    {
      Res* res = static_cast<Res*>(cell->contents[i].content.get());
      res->what_resource_I();
    }
  throw std::runtime_error("Hasn't got resource");
}

Buildings ControlContents::get_building() const
{
  for(size_t i{0}; i < cell->contents.size(); ++i)
    if(cell->contents[i].content->what_content_I() == Contents::Building)
    {
      class Building* building = static_cast<class Building*>(cell->contents[i].content.get());
      building->what_building_I();
    }
  throw std::runtime_error("Hasn't got building");
}

std::vector<Units> ControlContents::get_units() const
{
  std::vector<Units> units;
  for(size_t i{0}; i < cell->contents.size(); ++i)
    if(cell->contents[i].content->what_content_I() == Contents::Unit)
    {
      class Unit* unit = static_cast<class Unit*>(cell->contents[i].content.get());
      units.push_back(unit->what_unit_I());
    }
  return units;
}

bool ControlContents::has_landscape() const
{
  return cell->is_there_main_landscape;
}

bool ControlContents::has_resource() const
{
  for(size_t i{0}; i < cell->contents.size(); ++i)
    if(cell->contents[i].content->what_content_I() == Contents::Resource)
      return true;
  return false;
}

bool ControlContents::has_building() const
{
  for(size_t i{0}; i < cell->contents.size(); ++i)
    if(cell->contents[i].content->what_content_I() == Contents::Building)
      return true;
  return false;
}

int ControlContents::count_units() const
{
  int count{0};
  for(size_t i{0}; i < cell->contents.size(); ++i)
    if(cell->contents[i].content->what_content_I() == Contents::Unit)
      count++;
  return count;
}

void ControlContents::set_show_cell(bool _show_cell)
{
  cell->show_cell = _show_cell;
}

void ControlContents::set_show_res(bool show_res)
{
  for(size_t i{0}; i < cell->contents.size(); ++i)
    if(cell->contents[i].content->what_content_I() == Contents::Resource)
      cell->contents[i].show_content = show_res;
}

void ControlContents::set_show_unit(bool show_unit, class Unit* unit)
{
  for(size_t i{0}; i < cell->contents.size(); ++i)
    if(cell->contents[i].content->what_content_I() == Contents::Unit)
      if(cell->contents[i].content.get() == unit)
        cell->contents[i].show_content = show_unit;
}
