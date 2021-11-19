#ifndef SCIENCE_H
#define SCIENCE_H

#include "../IObject.h"


enum class Studies
{
  // Древнейший мир

  // Земледелие
  // Ферма
  Agriculture,

  // Каменная кладка
  // Камень, Карьер
  Masonry,

  // Животноводство
  // Лошади, Пасдбище
  AnimalHusbandry,

  // Стрельба из лука
  // Лучники
  Archery,

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
  // Тарговый пост
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

  // Физика
  // Требушет
  Physics,
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


class Science : public IObject
{

};

#endif // SCIENCE_H
