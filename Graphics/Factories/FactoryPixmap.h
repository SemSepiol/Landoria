#ifndef FACTORYPIXMAP_H
#define FACTORYPIXMAP_H
#include <QPixmap>

#include "../../IObject.h"
#include "../../Controller/Enums.h"

class FactoryPixmap : IObject
{
public:
  QPixmap create_pixmap_for_res(Resources type_resource) const;
  QPixmap create_pixmap_for_unit(Units type_unit) const;
  QPixmap create_pixmap_for_building(Buildings type_building) const;
  QPixmap create_pixmap_for_landscape(Landscapes type_landscape) const;
  QPixmap create_pixmap_for_forest() const;

private:
  const QString image_path {":/Graphics/image/"};
  const QString resources_dir {"resources/"};
  const QString units_dir {"units/"};
  const QString buildings_dir {"building/"};
  const QString landscapes_dir {"landscapes/"};
};

#endif // FACTORYPIXMAP_H
