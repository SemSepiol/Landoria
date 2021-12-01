#ifndef IMENUTYPEMAP_H
#define IMENUTYPEMAP_H

#include <QWidget>


class IMenuTypeMap : public QWidget
{
public:
  virtual void set_type(size_t i) = 0;

protected:
  IMenuTypeMap(QWidget* win)
    :QWidget(win)
  {}
};

#endif // IMENUTYPEMAP_H
