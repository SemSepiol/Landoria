#ifndef IMENUSCIENCE_H
#define IMENUSCIENCE_H

#include <QWidget>

class IMenuScience : public QWidget
{
public:
  virtual void wheel_scroll(int angle) = 0;
protected:
  IMenuScience(QWidget* win)
    :QWidget{win}
  {}
};

#endif // IMENUSCIENCE_H
