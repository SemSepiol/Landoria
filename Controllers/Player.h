#ifndef PLAYER_H
#define PLAYER_H
#include <vector>

#include "IPlayer.h"
#include "../Graphics/Units/Unit.h"
#include "../Graphics/GraphicsController/EventsStructures.h"
#include "IGame.h"
#include "UnitsCharaterichtics.h"

struct PlayerUnit : public IObject
{
  size_t cell_x;
  size_t cell_y;
  class Unit* unit;
  std::unique_ptr<Event> event;
  PlayerUnit(size_t _cell_x, size_t _cell_y, class Unit* _unit)
    :cell_x{_cell_x}, cell_y{_cell_y}, unit{_unit} {}
};

class Player : public IPlayer
{
public:
    Player(IGameForPlayer* game_controller);
    virtual ~Player() override;

    virtual void click_unit(class Unit* unit) override;
    virtual void set_initial_units(size_t initial_cell_x, size_t initial_cell_y) override;

    virtual void menu_event(class Unit* unit, Event* event) override;

private:
    PlayerUnit* get_my_unit(class Unit* unit);
    void set_event_to_unit(PlayerUnit* my_unit, Event* event);
    void event_for_citizen(PlayerUnit* my_unit, Event* event);
    void move_unit_event(PlayerUnit* my_unit, Move_event* event);

    void add_unit(Units type_unit, size_t position_x, size_t position_y);
    IGameForPlayer* game_controller;

    std::vector<PlayerUnit> my_units;
};

#endif // PLAYER_H
