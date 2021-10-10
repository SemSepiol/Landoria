#ifndef PLAYER_H
#define PLAYER_H
#include <vector>

#include "IPlayer.h"
#include "../Graphics/Units/Unit.h"
#include "../Graphics/Buildings/Town.h"
#include "../Graphics/GraphicsController/EventsStructures.h"
#include "IGame.h"
#include "UnitsCharaterichtics.h"
#include "FindUnitWay.h"

struct PlayerUnit
{
  Position pos;
  class Unit* unit;
  std::unique_ptr<Event> event;

  PlayerUnit(class Unit* _unit, Position _pos)
    :pos{_pos}, unit{_unit}, event{new struct NoEvent} {}
};

struct PlayerTown
{
  Position pos;
  class Town* town;

  PlayerTown(class Town* _town, Position _pos)
    :pos{_pos}, town{_town} {}
};

class Player : public IPlayer, public IMenuTownPlayer
{
public:
    Player(IGameForPlayer* game_controller);
    virtual ~Player() override;

    virtual void click_unit(class Unit* unit) override;
    virtual void click_town(class Town* town) override;
    virtual void set_initial_units(Position initial_cell) override;

    virtual void menu_event(class Unit* unit, Event* event) override;
    virtual IMenuTownPlayer* menutown_player() override { return this; }

    virtual void start_move();
    virtual void end_move();
private:
    PlayerUnit* get_my_unit(class Unit* unit);
    PlayerTown* get_my_town(class Town* town);
    void set_event_to_unit(PlayerUnit* my_unit, Event* event);
    void event_for_citizen(PlayerUnit* my_unit, Event* event);
    void event_for_worker(PlayerUnit* my_unit, Event* event);
    void move_unit_event(PlayerUnit* my_unit, MoveEvent* event);

    void add_town(class Town* town, Position pos);
    void add_unit(Units type_unit, Position pos_cell);
    void unit_move(PlayerUnit* unit);

    IGameForPlayer* game_controller;

    std::vector<PlayerUnit> my_units;
    std::vector<PlayerTown> my_towns;
};

#endif // PLAYER_H
