#ifndef MENUTYPEWORKTOWN_H
#define MENUTYPEWORKTOWN_H

#include <QMouseEvent>
#include <QWidget>
#include <vector>

#include "../../Controllers/Player/IMenuTownPlayer.h"
#include "../GraphicsController/IWindowGraphicsController.h"
#include "../../Controllers/Player/PlayerTown.h"
#include "IMenuTown.h"

class MenuTypeWorkTown : public QWidget
{
  enum TypesWork{
    Build,
    AlreadyBuilt,
    Close
  };

public:
  MenuTypeWorkTown(IMenuTown* menu_town);
  void set_geometry(QPoint pos, Size size);

  size_t count_button() const;
private:
  virtual void paintEvent(QPaintEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override {Q_UNUSED(event)}
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;

  void draw();
  void click(QPoint pos);
  QRectF rect_butt(int ind);
  bool point_in_rect(QRectF rect, QPoint point);
  int height_butt();
  void click_on_butt(size_t ind);
  QString str_text_butt(size_t ind);

  IMenuTown* menu_town;
  QPoint mouse_pos_clicked;
  std::vector<TypesWork> buttuns;
};

#endif // MENUTYPEWORKTOWN_H
