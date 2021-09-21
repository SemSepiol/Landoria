#include "FactoryPixmap.h"

QPixmap FactoryPixmap::create_pixmap_for_res(Resources type_resource)
{
  switch (type_resource) {
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

QPixmap FactoryPixmap::create_pixmap_for_unit(Units type_unit)
{
  switch (type_unit) {
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

QPixmap FactoryPixmap::create_pixmap_for_building(Buildings type_building)
{
  Q_UNUSED(type_building)
  throw std::runtime_error("chert");
}
