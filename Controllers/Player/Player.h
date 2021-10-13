#ifndef PLAYER_H
#define PLAYER_H
#include <vector>

#include "IPlayer.h"
#include "../../Graphics/Units/Unit.h"
#include "../../Graphics/GraphicsController/EventsStructures.h"
#include "../IGame.h"
#include "../UnitsCharaterichtics.h"
#include "../FindUnitVision.h"
#include "../FindUnitWay.h"
#include "PlayerTown.h"
#include "PlayerMap.h"
#include "PlayerRes.h"

struct PlayerUnit
{
  Position pos;
  class Unit* unit;
  std::unique_ptr<Event> event;

  PlayerUnit(class Unit* _unit, Position _pos)
    :pos{_pos}, unit{_unit}, event{new struct NoEvent} {}

  PlayerUnit(const PlayerUnit& playerunit)
    :pos{playerunit.pos}, unit{playerunit.unit}, event{playerunit.event->copy()} {}
};

class Player : public IPlayer
{
public:
    Player(IGameForPlayer* game_controller);
    virtual ~Player() override;

    virtual void click_unit(class Unit* unit) override;
    virtual void click_town(class Town* town) override;
    virtual void set_initial_units(Position initial_cell) override;

    virtual void menu_event(class Unit* unit, Event* event) override;

    virtual bool is_finish();
    virtual void start_move();
    virtual void end_move();
    virtual void draw_my_map();
private:
    PlayerUnit* get_my_unit(class Unit* unit);
    PlayerTown* get_my_town(class Town* town);
    void set_event_to_unit(PlayerUnit* my_unit, Event* event);
    void event_for_citizen(PlayerUnit* my_unit, Event* event);
    void event_for_worker(PlayerUnit* my_unit, Event* event);
    void move_unit_event(PlayerUnit* my_unit, MoveEvent* event);
    void set_units_vision(bool vision);
    void set_movement_to_max_unit();

    void add_town(class Town* town, Position pos);
    void add_unit(Units type_unit, Position pos_cell);
    void unit_move(PlayerUnit* unit);

    IGameForPlayer* game_controller;

    int gold_per_turn = 1000;

    std::vector<PlayerUnit> my_units;
    std::vector<std::unique_ptr<PlayerTown>> my_towns;
    std::unique_ptr<PlayerMap> player_map;
    std::unique_ptr<PlayerRes> player_res;
};

#endif // PLAYER_H
