#ifndef FACTORYPIXMAP_H
#define FACTORYPIXMAP_H
#include <QPixmap>

#include "../../IObject.h"
#include "../../Controllers/Enums.h"

class FactoryPixmap : IObject
{
public:
  QPixmap create_pixmap_for_res(Resources type_resource) const;
  QPixmap create_pixmap_for_unit(Units type_unit) const;
  QPixmap create_pixmap_for_building(Buildings type_building) const;
  QPixmap create_pixmap_for_main_landscape(MainLandscapes type_landscape) const;
  QPixmap create_pixmap_for_other_landscape(OtherLandscapes type_landscape) const;

private:
  const QString image_path {":/Graphics/image/"};
  const QString resources_dir {"resources/"};
  const QString units_dir {"units/"};
  const QString buildings_dir {"building/"};
  const QString landscapes_dir {"landscapes/"};
};

#endif // FACTORYPIXMAP_H
