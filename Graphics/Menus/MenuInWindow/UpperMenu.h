#ifndef UPPERMENU_H
#define UPPERMENU_H

#include <sstream>

#include <QMouseEvent>
#include <QPainter>

#include "AMenuInWindow.h"
#include "../../Factories/FactoryPixmap.h"
#include "../../GraphicsController/IMenuGraphicsController.h"
#include "../../../Controllers/Player/IMenuTownPlayer.h"


class UpperMenu : public AMenuInWindow
{
  struct DrawRes
  {
    Resources res;
    int count_res;

    DrawRes(Resources _res, int _count_res)
      :res{_res}, count_res{_count_res}
    {}
  };

public:
  UpperMenu(IMenuInWindowGraphicsController* graphic_controller);

  void set_enable_move_map(bool enable_move_map);
  void update_infofm(IMenuTownPlayer* player);
protected:
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual void draw() override;
  virtual void click(QPoint pos) override;
  QRect exit_butt() const;

  void draw_gold();
  void draw_science();
  void draw_resource();

  QRect rect_gold() const;
  QRect rect_gold_pic() const;
  QRect rect_science() const;
  QRect rect_science_pic() const;
  QRect rect_res(size_t num) const;
  QRect rect_res_pic(size_t num) const;

  int count_simbols(int a) const;


  bool enable_move_map = true;

  std::vector<DrawRes> draw_res;
  int count_gold = 0;
  int count_science = 0;
};

#endif // UPPERMENU_H
