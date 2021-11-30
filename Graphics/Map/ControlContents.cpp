#include "Cell.h"

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

IContent* ControlContents::add_resource(Resources type_resource, int count_of_res)
{
  if (has_resource())
    throw std::runtime_error("add_resource: There is already a resource in the cell");
  cell->contents.push_back({FactoryRes().create_res(type_resource, cell, count_of_res)});
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

void ControlContents::del_building()
{
  del_content(_get_building());
}

IContent* ControlContents::pop_content(IContent* content)
{
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

MainLandscapes ControlContents::get_main_landscape() const
{
  if(!cell->is_there_main_landscape)
    throw std::runtime_error("landscape is not set");
  return cell->mainlandscape;
}

OtherLandscapes ControlContents::get_other_landscape() const
{
  return cell->otherlandscape;
}

Resources ControlContents::get_resource() const
{
  Res* resource = _get_resource();
  if(resource)
    return resource->what_resource_I();
  throw std::runtime_error("Hasn't got resource");
}

Building* ControlContents::get_building() const
{
  class Building* building = _get_building();
  if(building)
    return building;
  throw std::runtime_error("Hasn't got building");
}

std::vector<Units> ControlContents::get_units() const
{
  std::vector<class Unit*> units = _get_units();
  std::vector<Units> types_units;
  for(auto unit : units)
    types_units.push_back(unit->what_unit_I());
  return types_units;
}

Countries ControlContents::get_country_units() const
{
  std::vector<class Unit*> units = _get_units();
  if(!units.size())
    throw std::runtime_error("Hasn't got units");
  return units[0]->get_country();
}

bool ControlContents::has_main_landscape() const
{
  return cell->is_there_main_landscape;
}

bool ControlContents::has_resource() const
{
  return _get_resource();
}

bool ControlContents::has_building() const
{
  return _get_building();
}

int ControlContents::count_units() const
{
  return int(_get_units().size());
}

void ControlContents::set_show_cell(Cell::ShowCell _show_cell)
{
  cell->show_cell = _show_cell;
}

ICell::ShowCell ControlContents::get_show_cell() const
{
  return cell->show_cell;
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

void ControlContents::set_highlight_unit(IContent* unit, bool highlight)
{
  for(size_t i{0}; i < cell->contents.size(); ++i)
    if(cell->contents[i].content->what_content_I() == Contents::Unit)
      if(cell->contents[i].content.get() == unit)
        cell->contents[i].highlight = highlight;
}

void ControlContents::set_count_of_res(int count)
{
  Res* res = _get_resource();
  if(res)
    res->set_count_of_res(count);
  else
    throw std::runtime_error("set_count_of_res(): hasn't resource in this cell");
}

int ControlContents::get_count_of_res() const
{
  Res* res = _get_resource();
  if(res)
    return res->get_count_of_res();
  return 0;
}

void ControlContents::set_country(Countries country)
{
  cell->country = country;
}

Countries ControlContents::get_country() const
{
  return cell->country;
}

Res* ControlContents::_get_resource() const
{
  for(size_t i{0}; i < cell->contents.size(); ++i)
    if(cell->contents[i].content->what_content_I() == Contents::Resource)
    {
      Res* res = static_cast<Res*>(cell->contents[i].content.get());
      return res;
    }
  return nullptr;
}

class Building* ControlContents::_get_building() const
{
  for(size_t i{0}; i < cell->contents.size(); ++i)
  if(cell->contents[i].content->what_content_I() == Contents::Building)
  {
    class Building* building = static_cast<class Building*>(cell->contents[i].content.get());
    return building;
  }
  return nullptr;
}

std::vector<class Unit*> ControlContents::_get_units() const
{
  std::vector<class Unit*> units;
  for(size_t i{0}; i < cell->contents.size(); ++i)
    if(cell->contents[i].content->what_content_I() == Contents::Unit)
    {
      class Unit* unit = static_cast<class Unit*>(cell->contents[i].content.get());
      units.push_back(unit);
    }
  return units;
}
