#ifndef SCIENCE_H
#define SCIENCE_H

#include <vector>

#include "Enums.h"
#include "TownBuildings.h"
#include "../IObject.h"


enum class Knowledges
{
  // Древнейший мир

  // Земледелие
  // Ферма
  Agriculture,

  // Животноводство
  // Лошади, Пасдбище
  AnimalHusbandry,

  // Стрельба из лука
  // Лучники
  Archery,

  // Каменная кладка
  // Камень, Карьер
  Masonry,

  // Язык
  // Манумент, Cвятилище
  Language,

  // Добыча руды
  // Железо, Рудник
  OreMining,

  // Мореходство
  // Какие-нибудь караблики
  Navigation,

  // Письменность
  // Школа
  Writing,

  // Колесо
  // Колесницы
  Wheel,

  // Обработка бронзы
  // Мелкие копейщики
  BronzeProcessing,

  /////////////////
  // Богословие
  // Храм
  Theology,

  // Верховая езда
  // Кавалерия
  HorseRiding,

  // Деньги
  // Рынок
  Money,

  // Драма и поэзия
  // Амфитеатор
  DramaAndPoetry,

  // Инженерное дело
  // Аквидук, Форт
  Engineering,

  // Математика
  // Школа, Катапульта
  Mathematics,

  // Металлоконструкции
  // Лесопилка, Крутые лучники
  MetalStructures,

  // Обработка железа
  // Мечники
  IronProcessing,

  // Оптика
  // Маяк
  Optics,

  // Философия
  // Храм 2
  Philosophy,

  /////////////
  // Гильдии
  // Торговый пост
  Guilds,

  // Госслужба
  // Крутые копейщики
  CivilService,

  // Компас
  // Гавань, Галеас
  Compass,

  // Литьё
  // Мастерская
  Casting,

  // Машиностроение
  // Мастерская 2
  MechanicalEngineering,

  // Образование
  // Институт
  Education,

  // Рыцарство
  // Стены 2, Тяж. конница
  Knighthood,

  // Сталеварение
  // Крутые мечники
  Steelmaking,
};


enum class Epochs
{
  AncientWorld,
  Antiquity,
  MiddleAges,
  NewTime,
  ModernTimes,
  Modernity,
  AgeOfAtom,
  InformationAge
};

struct PositionKnowledge
{
  int num_x = 0;
  int num_y = 0;
  PositionKnowledge(int x, int y)
    :num_x{x}, num_y{y}
  {}

  PositionKnowledge() {}
};

struct TownBuilding
{
  TownBuildings town_building;
  int level;

  TownBuilding(TownBuildings _town_building, int _level)
    :town_building{_town_building}, level{_level}
  {}
};

struct Knowledge
{
  Knowledges name_knowledge;
  Epochs epoch;

  PositionKnowledge position_knowledge;
  std::vector<Knowledges> necessary_knowledges;

  std::vector<TownBuilding> town_buildings;
  std::vector<Units> units;
  std::vector<Resources> resources;
  std::vector<Buildings> buildings;

  Knowledge(Knowledges _name_knowledge)
    :name_knowledge{_name_knowledge}
  {}
};

class Science : public IObject
{
public:
  std::vector<Knowledges> get_all_name_knowledges() const;
  Knowledge get_knowledge(Knowledges name_knowledge) const;
};

#endif // SCIENCE_H
