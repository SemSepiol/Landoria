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
    if(contents[i]->what_content_I() == Contents::Unit){
      if (count_drawn_unit < 4){
        QPoint p = calculations()->point_circle_for_unit(count_drawn_unit);
//        std::cout << p.x() << ":" << p.y() << std::endl;
        contents[i]->draw(point + p);
      } else if (count_drawn_unit == 4){
        QPoint p = calculations()->point_circle_for_res();
//        std::cout << p.x() << ":" << p.y() << std::endl;
        contents[i]->draw(point + p);
      } else if (count_drawn_unit == 5) {
        QPoint p = calculations()->point_circle_for_mod();
//        std::cout << p.x() << ":" << p.y() << std::endl;
        contents[i]->draw(point + p);
      }
      count_drawn_unit++;
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

void ControlContents::set_landscape(Landscapes type_landscape)
{
  cell->landscape = type_landscape;
}

void ControlContents::add_resource(Resources type_resource)
{

}

void ControlContents::add_building(Buildings type_building)
{

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
      return Resources::res; // тут нужный ресурс
  throw std::runtime_error("Hasn't got resource");
}

Buildings ControlContents::get_building() const
{
  for(size_t i{0}; i < cell->contents.size(); ++i)
    if(cell->contents[i]->what_content_I() == Contents::Resource)
      return Buildings::build; // тут нужные здание
  throw std::runtime_error("Hasn't got resource");
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

