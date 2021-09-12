#ifndef IMAP_H
#define IMAP_H
#include <QPoint>
#include <QWidget>

#include "IDrawObject.h"

class IMap : public IDrawObject
{
  virtual void draw(QPoint point) override = 0;
  virtual QWidget* window() = 0;
//  virtual
};

#endif // IMAP_H
