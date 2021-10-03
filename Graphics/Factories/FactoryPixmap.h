#ifndef FACTORYPIXMAP_H
#define FACTORYPIXMAP_H

#include <sstream>
#include <QPixmap>

#include "../../IObject.h"
#include "../../Controllers/Enums.h"
#include "../GraphicsController/EventsStructures.h"

class FactoryPixmap : IObject
{
public:
  QPixmap create_pixmap_for_res(Resources type_resource) const;
  QPixmap create_pixmap_for_unit(Units type_unit) const;
  QPixmap create_pixmap_for_building(Buildings type_building) const;
  QPixmap create_pixmap_for_main_landscape(MainLandscapes type_landscape) const;
  QPixmap create_pixmap_for_other_landscape(OtherLandscapes type_landscape) const;
  QPixmap create_pixmap_for_butt_menu(Event* event) const;
  QPixmap create_pixmap_for_exit() const;
  QPixmap create_pixmap_for_minimap() const;
  QPixmap create_pixmap_for_nextmotion() const;

  QRectF size_picture_content() const;
  QRectF size_picture_landscape() const;
private:
  const QString image_path {":/Graphics/image/"};
  const QString resources_dir {"resources/"};
  const QString units_dir {"units/"};
  const QString buildings_dir {"building/"};
  const QString landscapes_dir {"landscapes/"};
  const QString menu_dir {"menu/"};
};

#endif // FACTORYPIXMAP_H
