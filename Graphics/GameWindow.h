#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H
#include <memory>

#include <QWidget>
#include <QPoint>
#include <QResizeEvent>
#include "../Controller/IGame.h"

class GameWindow : public QWidget
{
  const QPoint _p_win = QPoint{0,0};
public:
  GameWindow(IGame* game);

  ~GameWindow() override;

  void show();
  virtual void paintEvent(QPaintEvent* event) override;
private:
  IGame* game_controller;
};

#endif // GAME_WINDOW_H
