#include <iostream>
#include <QApplication>
#include "Controllers/Game.h"

using namespace std;

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Game game = Game(&a, 20, 20, 1);
  game.start();
  return a.exec();
}
