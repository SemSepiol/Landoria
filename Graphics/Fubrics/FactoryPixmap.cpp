#include "FactoryPixmap.h"

QPixmap FactoryPixmap::create_pixmap_for_res(Resources type_resource)
{
  switch (type_resource) {
  case Resources::Gold:
    return QPixmap{image_path + resource_dir + "Gold.png/"};
  case Resources::Iron:
    return QPixmap{image_path + resource_dir + "Iron.png/"};
  case Resources::Stone:
    return QPixmap{image_path + resource_dir + "Stone.png/"};
  case Resources::Aluminum:
    return QPixmap{image_path + resource_dir + "Aluminum.png/"};
  case Resources::Horses:
    return QPixmap{image_path + resource_dir + "Horses.png/"};
  case Resources::Oil:
    return QPixmap{image_path + resource_dir + "Oil.png/"};
  case Resources::Uranium:
    return QPixmap{image_path + resource_dir + "Uranium.png/"};
  case Resources::Coal:
    return QPixmap{image_path + resource_dir + "Coal.png/"};
  case Resources::Fish:
    return QPixmap{image_path + resource_dir + "Fish.png/"};
  case Resources::Silver:
    return QPixmap{image_path + resource_dir + "Silver.png/"};
  default:
    throw std::runtime_error("There are no images for this resource");
  }
}

QPixmap FactoryPixmap::create_pixmap_for_unit(Units type_unit)
{
  Q_UNUSED(type_unit)
  throw std::runtime_error("chert");
}

QPixmap FactoryPixmap::create_pixmap_for_building(Buildings type_building)
{
  Q_UNUSED(type_building)
  throw std::runtime_error("chert");
}
