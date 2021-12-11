#ifndef PLAYERRES_H
#define PLAYERRES_H

#include <map>

#include "../Enums.h"
#include "../../IObject.h"


class PlayerRes : public IObject
{
  std::map<Resources, int> player_resources;

public:
  PlayerRes(Mod mod);

  ///Добавляет к уже имеющимся
  void add_resource(Resources type_res, int count);

  ///Убирает, если нужно убрать больше чем есть убирет все.
  void del_resource(Resources type_res, int count);

  ///Заменяет на новое количество
  void set_resource(Resources type_res, int count);

  /// Возвращает количество ресурса
  int get_resource(Resources type_res);

private:
  Mod mod;
};

#endif // PLAYERRES_H
