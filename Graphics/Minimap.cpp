#include "Minimap.h"
#include <iostream>

Minimap::Minimap(QWidget* win, Map* _map, IGraphicsControllerForMiniMap* _graphics_controller)
  :QWidget(win), graphics_controller{_graphics_controller}, map{_map}, calc()
{}

void Minimap::set_geometry(QPoint bottomright, int hexagon_side)
{
  calc.set_side(hexagon_side);
  do_size();

  QWidget::setGeometry(bottomright.x() - width_minimap, bottomright.y() - height_minimap,
                       width_minimap, height_minimap);
}

void Minimap::draw()
{
  for(size_t i{0}; i < size_t(graphics_controller->count_cell_y()); ++i)
    for(size_t j{0}; j < size_t(graphics_controller->count_cell_x()); ++j)
      draw_cell(pos_corner_map + point_of_cell(j,i), map->cell_by_indexes(j, i));

  QPainter qp(this);
  QPen pen(Qt::black, 4, Qt::SolidLine);
  qp.setPen(pen);
  qp.drawRect(win_on_map);
}

void Minimap::set_win_rect(double coeffx, double coeffy, double coeff_width, double coeff_height)
{
  double win_center_x = width_minimap/2 - coeffx*width_minimap;
  double win_center_y = height_minimap/2 - coeffy*height_minimap;
  double win_width = coeff_width * width_minimap;
  double win_height = coeff_height * height_minimap;
  win_on_map = QRectF(win_center_x, win_center_y, win_width, win_height);
}

void Minimap::paintEvent(QPaintEvent* event)
{
  Q_UNUSED(event)
  draw();
}

void Minimap::mousePressEvent(QMouseEvent *event)
{
  double coeffx = (width_minimap/2 - event->pos().x() + win_on_map.width()/2)*1. / width_minimap;
  double coeffy = (height_minimap/2 - event->pos().y() + win_on_map.height()/2)*1. / height_minimap;
  graphics_controller->move_map(coeffx, coeffy);
}

QPoint Minimap::point_of_cell(size_t ind_x, size_t ind_y)
{
  int y = int(ind_y+1)*calc.hexagon_side() + int(ind_y)*calc.hexagon_side()/2;
  QPoint cell_point{calc.hexagon_height(), y};
  if (ind_y % 2 == 1)
    cell_point += QPoint{calc.hexagon_height(), 0};

  cell_point += QPoint{calc.hexagon_height()*2*int(ind_x), 0};
  return cell_point;
}

void Minimap::draw_cell(QPoint pos, Cell* cell)
{
  QPoint p1 = pos - calc.point_0();
  QPoint p2 = pos - calc.point_60();
  QPoint p3 = pos - calc.point_120();
  QPoint p4 = pos - calc.point_180();
  QPoint p5 = pos - calc.point_240();
  QPoint p6 = pos - calc.point_300();

  QPainter qp(this);

  QBrush brush(color(cell));
  qp.setBrush(brush);

  QPointF points[6] {p1, p2, p3, p4, p5, p6};
  qp.drawPolygon(points, 6);
}

QColor Minimap::color(Cell* cell)
{
  ControlContents controlcontents{cell};
  switch (controlcontents.get_landscape())
  {
  case MainLandscapes::Ocean:
    return QColor(Qt::darkBlue);
  case MainLandscapes::Coast:
    return QColor(Qt::blue);
  case MainLandscapes::Plain:
    return QColor(Qt::darkGreen);
  case MainLandscapes::Mountain:
    return QColor(Qt::darkGray);
  case MainLandscapes::Tundra:
    return QColor(Qt::gray);
  case MainLandscapes::Desert:
    return QColor(Qt::yellow);
  case MainLandscapes::Snow:
    return QColor(Qt::white);
  case MainLandscapes::Ice:
    return QColor(Qt::white);
  default:
    throw std::runtime_error("Minimap::color(): here are no color for this landscape");
  }
}

void Minimap::do_size()
{
  int num_cell_x = graphics_controller->count_cell_x();
  int num_cell_y = graphics_controller->count_cell_y();
  height_minimap = calc.hexagon_side()*num_cell_y + calc.hexagon_side()*(num_cell_y+1)/2;
  width_minimap = calc.hexagon_height()*(num_cell_x*2+1);
}
