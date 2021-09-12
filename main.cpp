#include <iostream>
#include <QApplication>
#include "Controller/Game.h"
using namespace std;

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Game game = Game();
  return a.exec();
}
