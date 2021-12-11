#ifndef SCIENCE_H
#define SCIENCE_H

#include <vector>
#include <stdexcept>

#include "Enums.h"
#include "TownBuildings.h"
#include "../IObject.h"


enum class Knowledges
{
  /////////////////
  Agriculture,
  StoneProcessing,
  Language,
  WoodProcessing,
  Writing,

  /////////////////
  AnimalHusbandry,
  Wheel,
  OreMining,
  Archery,
  Theology,
  Navigation,
  HorseRiding,
  Winemaking,
  BronzeProcessing,
  Money,
  Philosophy,
  Optics,
  IronProcessing,
  PreciousOres,
  DramaAndPoetry,
  Mathematics,

  /////////////
  MetalStructures,
  Engineering,
  Guilds,
  Education,
  Compass,
  Knighthood,
  Steelmaking,
  Machinery,
  Trading,
  Medicine,
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

  bool operator<(const PositionKnowledge& pos1)
  {
    return num_x < pos1.num_x || (num_x == pos1.num_x && num_y < pos1.num_y);
  }
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
  double need_science_glasses = 2;

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
