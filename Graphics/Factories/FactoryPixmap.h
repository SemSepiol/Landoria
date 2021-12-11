#ifndef FACTORYPIXMAP_H
#define FACTORYPIXMAP_H

#include <sstream>

#include <QPixmap>

#include "../GraphicsController/EventsStructures.h"
#include "../../Controllers/Enums.h"
#include "../../Controllers/Science.h"
#include "../../Controllers/TownBuildings.h"
#include "../../IObject.h"


class FactoryPixmap : public IObject
{
public:
  QPixmap create_pixmap_for_res(Resources type_resource) const;
  QPixmap create_pixmap_for_unit_on_map(Units type_unit) const;
  QPixmap create_pixmap_for_unit(Units type_unit) const;
  QPixmap create_pixmap_for_building(Buildings type_building) const;
  QPixmap create_pixmap_for_main_landscape(MainLandscapes type_landscape) const;
  QPixmap create_pixmap_for_other_landscape(OtherLandscapes type_landscape) const;
  QPixmap create_pixmap_for_knowledges(Knowledges name_knowledge) const;
  QPixmap create_pixmap_for_butt_menu(Event* event) const;
  QPixmap create_pixmap_for_exit() const;
  QPixmap create_pixmap_for_del_in_queue() const;
  QPixmap create_pixmap_for_up_in_queue() const;
  QPixmap create_pixmap_for_down_in_queue() const;
  QPixmap create_pixmap_for_minimap() const;
  QPixmap create_pixmap_for_nextmotion() const;
  QPixmap create_pixmap_for_type_map() const;
  QPixmap create_pixmap_for_butt_build() const;
  QPixmap create_pixmap_for_town_building(TownBuildings type_building) const;
  QPixmap create_pixmap_for_fog_of_war() const;
  QPixmap create_pixmap_for_gold() const;
  QPixmap create_pixmap_for_science() const;
  QPixmap create_pixmap_for_upgrade() const;

  QRectF size_picture_content() const;
  QRectF size_picture_unit() const;
  QRectF size_picture_landscape() const;

  /// для золота и науки
  QRectF size_picture_gold() const;
private:
  const QString image_path {":/Graphics/image/"};
  const QString resources_dir {"resources/"};
  const QString units_on_map_dir {"units_on_map/"};
  const QString units_dir {"units/"};
  const QString buildings_dir {"building/"};
  const QString landscapes_dir {"landscapes/"};
  const QString knowledges_dir {"knowledges/"};
  const QString menu_dir {"menu/"};
  const QString town_building_dir{"town_building/"};
};

#endif // FACTORYPIXMAP_H
