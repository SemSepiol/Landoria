#ifndef ENUMS_H
#define ENUMS_H

struct CountInEnums
{
  int resources() { return 10; }
};

enum class Contents
{
  Resource,
  Unit,
  Building
};

enum class Units
{
  Worker,
  Citizen,
  Bowman,
  Swordsman
};

enum class MainLandscapes
{
  Ocean,
  Coast,
  Plain,
  Mountain,
  Tundra,
  Desert,
  Snow,
  Ice
};

enum class OtherLandscapes
{
  Nothing,
  Forest,
  Jungles,
  Hills,
  ForestAndHills,
  JunglesAndHills
};

enum class Resources
{
  Iron,
  Gold,
  Stone,
  Aluminum,
  Horses,
  Oil,
  Uranium,
  Coal,
  Fish,
  Silver
};

enum class Buildings
{
  Town,
  Farm,
  FishingBoat,
  Fort,
  LumberMill,
  Mine,
  OilWell,
  Pasture,
  Quarry,
  TradingPost
};

enum class Countries
{
  Nothing,
  Russia
};

#endif // ENUMS_H
