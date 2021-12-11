#ifndef MENUTYPEMAP_H
#define MENUTYPEMAP_H

#include <QMouseEvent>
#include <QWidget>

#include "IMenuTypeMap.h"
#include "TypesList.h"
#include "../../Factories/FactoryString.h"
#include "../../GraphicsController/IMenuGraphicsController.h"
#include "../../Map/IMap.h"


class MenuTypeMap : public IMenuTypeMap
{
  enum TypeWork
  {
    Nothing,
    Overlay,
    TypeContent
  };

public:
  MenuTypeMap(IMenuInWindowGraphicsController* graphics_controller, IMap* map);

  void set_geometry(QPoint pos, Size size);

  virtual void set_type(size_t i) override;

private:
  virtual void paintEvent(QPaintEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override {Q_UNUSED(event)}
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;

  void draw();
  void draw_notvisible();
  void draw_other_landscapes();
  void click(QPoint pos);

  QRect text_overlay() const;
  QRect wid_overlay() const;
  QRect text_icons() const;
  QRect wid_icons() const;
  QRect text_notvisible() const;
  QRect wid_notvisible() const;
  int rad_wid_notvisible() const;
  QRect text_other_landscapes() const;
  QRect wid_other_landscapes() const;
  int rad_wid_other_landscapes() const;

  bool point_in_circle(QPoint center_circle, int rad_circle, QPoint point);

  void do_tipes_list();
  std::vector<TypeMap::Overlay> v_overlay() const;
  std::vector<TypeMap::TypeContent> v_type_content() const;

  IMenuInWindowGraphicsController* graphics_controller;
  IMap* map;
  TypeMap type_map;

  QPoint mouse_pos_clicked;
  TypeWork type_work = Nothing;
  std::unique_ptr<TypesList> types_list;
};

#endif // MENUTYPEMAP_H
