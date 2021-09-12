#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H
#include <memory>

#include <QWidget>
#include <QPoint>
#include "../Controller/IGame.h"

class GameWindow : public QWidget
{
  const QPoint p_win = QPoint{100,100};
  const int height_win = 1000;
  const int width_win = 1000;

public:
  GameWindow(IGame* game);

  int height_window();
  int width_window();
  QPoint center_window();


  ~GameWindow();

private:
  std::unique_ptr<IGame> game_controller;
};

#endif // GAME_WINDOW_H
