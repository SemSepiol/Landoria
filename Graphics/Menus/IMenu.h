#ifndef IMENU_H
#define IMENU_H

#include <QWidget>

class IMenu : public QWidget
{
public:
  IMenu(QWidget* widget) :QWidget{widget} {}
  virtual void draw(QPoint point) = 0;
};

#endif // IMENU_H
