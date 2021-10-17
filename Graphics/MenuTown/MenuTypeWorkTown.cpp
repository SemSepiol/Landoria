#include "MenuTypeWorkTown.h"

MenuTypeWorkTown::MenuTypeWorkTown(IMenuTown* _menu_town)
  :QWidget{_menu_town->window()}, menu_town{_menu_town}
{
  QWidget::setAttribute( Qt::WA_TranslucentBackground, true );
  buttuns.push_back(TypesWork::Build);
  buttuns.push_back(TypesWork::AlreadyBuilt);
  buttuns.push_back(TypesWork::Close);
}

void MenuTypeWorkTown::set_geometry(QPoint pos, Size size)
{
  QWidget::setGeometry(pos.x(), pos.y(), size.width, size.height);
}

size_t MenuTypeWorkTown::count_button() const
{
  return buttuns.size();
}

void MenuTypeWorkTown::paintEvent(QPaintEvent* event)
{
  draw();
}

void MenuTypeWorkTown::mousePressEvent(QMouseEvent *event)
{
  mouse_pos_clicked = event->pos();
}

void MenuTypeWorkTown::mouseReleaseEvent(QMouseEvent *event)
{
  QPoint mouse_move = event->pos() - mouse_pos_clicked;
  if(abs(mouse_move.x()) > 5 or abs(mouse_move.y()) > 5)
    return;

  for(size_t i{0}; i < buttuns.size(); ++i)
  {
    if(point_in_rect(rect_butt(int(i)), event->pos()))
      click_on_butt(i);
  }
}

void MenuTypeWorkTown::draw()
{
  QPainter qp(this);
  QRect rect{0, 0, width(), height()};
  qp.setPen(QPen{Qt::white, 2});
  qp.fillRect(rect, QBrush(QColor(0, 0, 0, 200)));
  for(size_t i{0}; i < buttuns.size(); ++i)
  {
    qp.drawRect(rect_butt(int(i)));
    qp.drawText(rect_butt(int(i)), Qt::AlignCenter,  str_text_butt(i));
  }
}

QRectF MenuTypeWorkTown::rect_butt(int i)
{
  return QRectF{0., i*height_butt()*1.,
        width()*1., height_butt()*1.};
}

bool MenuTypeWorkTown::point_in_rect(QRectF rect, QPoint point)
{
  if (point.x() >= rect.topLeft().x() && point.x() < rect.bottomRight().x())
    if (point.y() >= rect.topLeft().y() && point.y() <= rect.bottomRight().y())
      return true;
  return false;
}

int MenuTypeWorkTown::height_butt()
{
  return height()/int(buttuns.size());
}

void MenuTypeWorkTown::click_on_butt(size_t i)
{
  TypesWork type_work = buttuns[i];
  switch (type_work)
  {
  case TypesWork::Close:
    menu_town->delete_townmenu();
    break;
  case TypesWork::AlreadyBuilt:
    menu_town->open_menu_alreadybuild();
    break;
  case TypesWork::Build:
    menu_town->open_menu_build();
    break;
  }
}

QString MenuTypeWorkTown::str_text_butt(size_t i)
{
  QString str = "";
  TypesWork type_work = buttuns[i];
  switch (type_work) {
  case TypesWork::Close:
    str = "Закрыть";
    break;
  case TypesWork::Build:
    str = "Построить";
    break;
  case TypesWork::AlreadyBuilt:
    str = "Построенно в городе";
    break;
  }
  return str;
}
