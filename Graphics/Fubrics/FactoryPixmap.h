#ifndef FACTORYPIXMAP_H
#define FACTORYPIXMAP_H
#include <QPixmap>

#include "../../IObject.h"
#include "../../Controller/Enums.h"

class FactoryPixmap : IObject
{
public:
  QPixmap create_pixmap_for_res(Resources type_resource);
  QPixmap create_pixmap_for_unit(Units type_unit);
  QPixmap create_pixmap_for_building(Buildings type_building);

private:
  const QString image_path {":/Graphics/image/"};
  const QString resources_dir {"resources/"};
  const QString units_dir {"units/"};
};

#endif // FACTORYPIXMAP_H
