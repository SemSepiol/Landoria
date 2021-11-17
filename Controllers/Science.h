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
