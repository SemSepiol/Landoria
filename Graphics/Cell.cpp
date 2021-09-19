#include "Cell.h"
#include <iostream>

Cell::Cell(IMap* map)
  :map{map}
{
}

void Cell::draw(QPoint point)
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

  QPen pen(Qt::black, 2, Qt::SolidLine);
  qp.setPen(pen);
  qp.drawLine(p1, p2);
  qp.drawLine(p2, p3);
  qp.drawLine(p3, p4);
  qp.drawLine(p4, p5);
  qp.drawLine(p5, p6);
  qp.drawLine(p6, p1);

  int count_drawn_unit = 0;
  for(size_t i{0}; i < contents.size(); ++i)
  {
    if(contents[i]->what_content_I() == Contents::Unit){
      if (count_drawn_unit < 4){
        QPoint p = calculations()->point_circle_for_unit(count_drawn_unit);
        contents[i]->draw(point + p);
      }
      count_drawn_unit++;
    }
    else if (contents[i]->what_content_I() == Contents::Resource){
        QPoint p = calculations()->point_circle_for_res();
        contents[i]->draw(point + p);
    }
    else if (contents[i]->what_content_I() == Contents::Building) {
        QPoint p = calculations()->point_circle_for_build();
        contents[i]->draw(point + p);
    }
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
      if(contents[j]->what_content_I() == Contents::Unit)
        if(++counter == num_circle+1)
          return contents[j].get();
  }

  if(num_circle == 4)
  {
    if (!control_contents.has_resource())
      return nullptr;

    for(size_t j{0}; j < contents.size(); ++j)
      if(contents[j]->what_content_I() == Contents::Resource)
        return contents[j].get();
  }

  if(num_circle == 5)
  {
    if (!control_contents.has_building())
      return nullptr;

    for(size_t j{0}; j < contents.size(); ++j)
      if(contents[j]->what_content_I() == Contents::Building)
        return contents[j].get();
  }

  throw std::runtime_error("Can't find content");
}

void ControlContents::set_landscape(Landscapes type_landscape)
{
  cell->landscape = type_landscape;
}

void ControlContents::add_resource(Resources type_resource)
{
  cell->contents.push_back(std::unique_ptr<IContent>{FubricRes().create_res(type_resource, cell)});
}

void ControlContents::add_building(Buildings type_building)
{
  if (type_building == Buildings::Town)
    cell->contents.push_back(std::unique_ptr<IContent>{new class Town(cell)});
}

void ControlContents::add_unit(Units type_unit)
{
  if (type_unit == Units::Worker)
    cell->contents.push_back(std::unique_ptr<IContent>{new class Worker(cell)});
}


void ControlContents::del_content(IContent* content)
{
  for(size_t i{0}; i < cell->contents.size(); ++i)
    if(cell->contents[i].get() == content)
      cell->contents.erase(cell->contents.begin() + i);
}


Landscapes ControlContents::get_landscapes() const
{
  return cell->landscape;
}

Resources ControlContents::get_resource() const
{
  for(size_t i{0}; i < cell->contents.size(); ++i)
    if(cell->contents[i]->what_content_I() == Contents::Resource)
    {
      IRes* res = static_cast<IRes*>(cell->contents[i].get());
      res->what_resource_I();
    }
  throw std::runtime_error("Hasn't got resource");
}

Buildings ControlContents::get_building() const
{
  for(size_t i{0}; i < cell->contents.size(); ++i)
    if(cell->contents[i]->what_content_I() == Contents::Building)
    {
      IBuilding* building = static_cast<IBuilding*>(cell->contents[i].get());
      building->what_building_I();
    }
  throw std::runtime_error("Hasn't got building");
}

std::vector<Units> ControlContents::get_units() const
{
  std::vector<Units> units;
  for(size_t i{0}; i < cell->contents.size(); ++i)
    if(cell->contents[i]->what_content_I() == Contents::Unit)
    {
      IUnit* unit = static_cast<IUnit*>(cell->contents[i].get());
      units.push_back(unit->what_unit_I());
    }
  return units;
}


bool ControlContents::has_resource() const
{
  for(size_t i{0}; i < cell->contents.size(); ++i)
    if(cell->contents[i]->what_content_I() == Contents::Resource)
      return true;
  return false;
}

bool ControlContents::has_building() const
{
  for(size_t i{0}; i < cell->contents.size(); ++i)
    if(cell->contents[i]->what_content_I() == Contents::Building)
      return true;
  return false;
}

int ControlContents::count_units()
{
  int count{0};
  for(size_t i{0}; i < cell->contents.size(); ++i)
    if(cell->contents[i]->what_content_I() == Contents::Unit)
      count++;
  return count;
}

