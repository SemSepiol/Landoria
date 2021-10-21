#include "MenuBuildTown.h"

MenuBuildTown::MenuBuildTown(IMenuTown* _menu_town)
  :QWidget{_menu_town->window()}, menu_town{_menu_town}
{
  QWidget::setAttribute( Qt::WA_TranslucentBackground, true );
}

void MenuBuildTown::set_geometry(QPoint pos, Size size)
{
  QWidget::setGeometry(pos.x(), pos.y(), size.width, size.height);
  height_rect_build = size.height/10;
}

void MenuBuildTown::paintEvent(QPaintEvent* event)
{
  draw();
  draw_unit();
  draw_building();
}

void MenuBuildTown::mousePressEvent(QMouseEvent *event)
{
  mouse_pos_clicked = event->pos();
}

void MenuBuildTown::mouseReleaseEvent(QMouseEvent *event)
{
  QPoint mouse_move = event->pos() - mouse_pos_clicked;
  if(abs(mouse_move.x()) > 5 or abs(mouse_move.y()) > 5)
    return;
}

void MenuBuildTown::draw()
{
  QPainter qp(this);
  QRect rect{0, 0, width(), height()};
  qp.fillRect(rect, QBrush(QColor(0, 0, 0, 200)));
}

void MenuBuildTown::draw_unit()
{
  QPainter qp(this);
  qp.setPen(QPen{Qt::white, 3});

  PlayerScience* player_science = menu_town->player()->player_science();
  QPoint pos{0, 0};
  auto open_units = player_science->get_best_open_units();
  for(size_t i{0}; i < open_units.size(); ++i)
  {
    qp.drawRect(QRect{pos, pos + QPoint{width(), height_rect_build}});
    QPixmap pixmap = FactoryPixmap().create_pixmap_for_unit(open_units[i]);
    QRectF source = FactoryPixmap().size_picture_unit();
    QRectF rect = QRect{pos, pos + QPoint{height_rect_build, height_rect_build}};
    qp.drawPixmap(rect, pixmap, source);
    pos += QPoint{0, height_rect_build};
  }
}

void MenuBuildTown::draw_building()
{
  QPainter qp(this);
  qp.setPen(QPen{Qt::white, 3});

  PlayerScience* player_science = menu_town->player()->player_science();
  QPoint pos{0, int(player_science->count_best_open_units())*height_rect_build};
  auto open_buildings = player_science->get_open_town_buildings();
  auto already_build = menu_town->town()->get_town_buildings();
  for(size_t i{0}; i < open_buildings.size(); ++i)
  {
    if(std::find(already_build.begin(), already_build.end(), open_buildings[i]) != already_build.end())
      continue;

    qp.drawRect(QRect{pos, pos + QPoint{width(), height_rect_build}});
    QPixmap pixmap = FactoryPixmap().create_pixmap_for_town_building(open_buildings[i]);
    QRectF source = FactoryPixmap().size_picture_content();
    QRectF rect = QRect{pos, pos + QPoint{height_rect_build, height_rect_build}};
    qp.drawPixmap(rect, pixmap, source);
    pos += QPoint{0, height_rect_build};
  }
}

bool MenuBuildTown::point_in_rect(QRectF rect, QPoint point)
{
  if (point.x() >= rect.topLeft().x() && point.x() < rect.bottomRight().x())
    if (point.y() >= rect.topLeft().y() && point.y() <= rect.bottomRight().y())
      return true;
  return false;
}
