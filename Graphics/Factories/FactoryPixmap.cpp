#include "FactoryPixmap.h"

QPixmap FactoryPixmap::create_pixmap_for_res(Resources type_resource) const
{
  switch (type_resource)
  {
  case Resources::Gold:
    return QPixmap{image_path + resources_dir + "Gold.png/"};
  case Resources::Iron:
    return QPixmap{image_path + resources_dir + "Iron.png/"};
  case Resources::Stone:
    return QPixmap{image_path + resources_dir + "Stone.png/"};
  case Resources::Aluminum:
    return QPixmap{image_path + resources_dir + "Aluminum.png/"};
  case Resources::Horses:
    return QPixmap{image_path + resources_dir + "Horses.png/"};
  case Resources::Oil:
    return QPixmap{image_path + resources_dir + "Oil.png/"};
  case Resources::Uranium:
    return QPixmap{image_path + resources_dir + "Uranium.png/"};
  case Resources::Coal:
    return QPixmap{image_path + resources_dir + "Coal.png/"};
  case Resources::Fish:
    return QPixmap{image_path + resources_dir + "Fish.png/"};
  case Resources::Silver:
    return QPixmap{image_path + resources_dir + "Silver.png/"};
  default:
    throw std::runtime_error("There are no images for this resource");
  }
}

QPixmap FactoryPixmap::create_pixmap_for_unit(Units type_unit) const
{
  switch (type_unit)
  {
  case Units::Worker:
    return QPixmap{image_path + units_dir + "Worker.png/"};
  case Units::Citizen:
    return QPixmap{image_path + units_dir + "Citizen.png/"};
  case Units::Bowman:
    return QPixmap{image_path + units_dir + "Bowman.png/"};
  case Units::Swordsman:
    return QPixmap{image_path + units_dir + "Swordsman.png/"};
  default:
    throw std::runtime_error("There are no images for this unit");
  }
}

QPixmap FactoryPixmap::create_pixmap_for_building(Buildings type_building) const
{
  switch (type_building)
  {
  case Buildings::Town:
    return QPixmap{image_path + buildings_dir + "Town.png/"};
  case Buildings::Farm:
    return QPixmap{image_path + buildings_dir + "Farm.png/"};
  case Buildings::FishingBoats:
    return QPixmap{image_path + buildings_dir + "FishingBoats.png/"};
  case Buildings::Fort:
    return QPixmap{image_path + buildings_dir + "Fort.png/"};
  case Buildings::Pasture:
    return QPixmap{image_path + buildings_dir + "Pasture.png/"};
  case Buildings::Mine:
    return QPixmap{image_path + buildings_dir + "Mine.png/"};
  case Buildings::OilWell:
    return QPixmap{image_path + buildings_dir + "OilWell.png/"};
  case Buildings::Quarry:
    return QPixmap{image_path + buildings_dir + "Quarry.png/"};
  case Buildings::TradingPost:
    return QPixmap{image_path + buildings_dir + "TradingPost.png/"};
  case Buildings::LumberMill:
    return QPixmap{image_path + buildings_dir + "LumberMill.png/"};
  default:
    throw std::runtime_error("There are no images for this building");
  }
}

QPixmap FactoryPixmap::create_pixmap_for_main_landscape(MainLandscapes type_landscape) const
{
  switch (type_landscape)
  {
  case MainLandscapes::Plain:
    return QPixmap{image_path + landscapes_dir + "Plain.png/"};
  case MainLandscapes::Mountain:
    return QPixmap{image_path + landscapes_dir + "Mountain.png/"};
  case MainLandscapes::Ocean:
    return QPixmap{image_path + landscapes_dir + "Ocean.png/"};
  case MainLandscapes::Coast:
    return QPixmap{image_path + landscapes_dir + "Coast.png/"};
  case MainLandscapes::Tundra:
    return QPixmap{image_path + landscapes_dir + "Tundra.png/"};
  case MainLandscapes::Desert:
    return QPixmap{image_path + landscapes_dir + "Desert.png/"};
  case MainLandscapes::Snow:
    return QPixmap{image_path + landscapes_dir + "Snow.png/"};
  case MainLandscapes::Ice:
    return QPixmap{image_path + landscapes_dir + "Ice.png/"};
  default:
    throw std::runtime_error("There are no images for this landscape");
  }
}


QPixmap FactoryPixmap::create_pixmap_for_other_landscape(OtherLandscapes type_landscape) const
{
  switch (type_landscape)
  {
  case OtherLandscapes::Forest:
    return QPixmap{image_path + landscapes_dir + "Forest.png/"};
  case OtherLandscapes::ForestAndHills:
    return QPixmap{image_path + landscapes_dir + "Forest_hills.png/"};
  case OtherLandscapes::Jungles:
    return QPixmap{image_path + landscapes_dir + "Jungles.png/"};
  case OtherLandscapes::JunglesAndHills:
    return QPixmap{image_path + landscapes_dir + "Jungles_hills.png/"};
  case OtherLandscapes::Nothing:
    return QPixmap{""};
  default:
    throw std::runtime_error("There are no images for this other landscape");
  }
}
