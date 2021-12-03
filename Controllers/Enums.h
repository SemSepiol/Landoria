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


enum class MainLandscapes
{
  Plain,
  Mountain,
  Tundra,
  Snow,
  Ice,
  Coast,
  Desert,
  Ocean
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


enum class Units
{
  Bowman,
  Citizen,
  Swordsman,
  Worker,
};


enum class Resources
{
  Fish,
  Oil,
  Aluminum,
  Coal,
  Horses,
  Gold,
  Iron,
  Silver,
  Stone,
  Uranium,
};


enum class Buildings
{
  Farm,
  FishingBoat,
  Fort,
  LumberMill,
  Mine,
  OilWell,
  Pasture,
  Quarry,
  Town,
  TradingPost
};


enum class Countries
{
  Nothing,
  Russia,
  America,
  China,
  England
};

#endif // ENUMS_H
