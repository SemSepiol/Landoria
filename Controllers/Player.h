#ifndef PLAYER_H
#define PLAYER_H
#include <vector>

#include "IPlayer.h"
#include "../Graphics/Units/Unit.h"
#include "IGame.h"

struct PlayerUnit : public IObject
{
  size_t cell_x;
  size_t cell_y;
  class Unit* unit;
  PlayerUnit(size_t _cell_x, size_t _cell_y, class Unit* _unit)
    :cell_x{_cell_x}, cell_y{_cell_y}, unit{_unit} {}
};

class Player : public IPlayer
{
public:
    Player(IGameForPlayer* game_controller);

    virtual void click_unit(class Unit* unit) override;
    virtual void set_initial_units(size_t initial_cell_x, size_t initial_cell_y) override;

private:
    PlayerUnit* get_my_unit(class Unit* unit);

    IGameForPlayer* game_controller;

    std::vector<PlayerUnit> my_units;
};

#endif // PLAYER_H
