#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "IMenuTownPlayer.h"
#include "IPlayer.h"
#include "ITownPlayer.h"
#include "PlayerBuild.h"
#include "PlayerMap.h"
#include "PlayerTown.h"
#include "PlayerRes.h"
#include "PlayerUnit.h"
#include "../FindVision.h"
#include "../FindUnitWay.h"
#include "../IGame.h"
#include "../../Graphics/Buildings/Building.h"
#include "../../Graphics/GraphicsController/EventsStructures.h"
#include "../../Graphics/Units/Unit.h"
#include "../../Graphics/Units/Worker.h"


class Player : public IPlayer, public IMenuTownPlayer, public ITownPlayer
{
public:
    Player(IGameForPlayer* game_controller, Countries country, Mod mod);
    virtual ~Player() override;

    virtual void click_unit(class Unit* unit) override;
    virtual void click_town(class Town* town) override;
    virtual void del_menu_town() override;
    virtual void set_initial_units(Position initial_cell) override;

    virtual void menu_event(class Unit* unit, Event* event) override;

    virtual bool is_finish();
    virtual void start_move();
    virtual void end_move();
    virtual void draw_my_map();

    virtual PlayerScience* player_science() const override;
    virtual void add_unit(Units type_unit, Position pos_cell) override;

    virtual double get_gold_per_turn() const override;
    virtual double get_gold() const override;
    virtual double get_science_per_turn() const override;
    virtual PlayerRes* get_player_res() const override;
    virtual Countries get_country() const override;

private:
    PlayerUnit* get_my_unit(class Unit* unit);
    size_t get_ind_my_unit(PlayerUnit* unit);
    PlayerTown* get_my_town(class Town* town);
    void set_event_to_unit(PlayerUnit* my_unit, Event* event);
    void event_for_citizen(PlayerUnit* my_unit, Event* event);
    void event_for_worker(PlayerUnit* my_unit, Event* event);
    void move_unit_event(PlayerUnit* my_unit, MoveEvent* event);
    void set_vision(bool vision);
    void set_town_vision(PlayerTown* town, bool vision);
    void set_movement_to_max_unit();
    void set_new_move_to_towns();

    void do_events_unit();
    void do_build_towns();

    void build_town(PlayerUnit* my_unit);
    void del_unit(PlayerUnit* unit);
    void unit_move(PlayerUnit* unit);
    void capture_cell(Position pos);

    void add_build(PlayerUnit* unit, Buildings type_building);
    void stop_build(PlayerUnit* unit);
    void add_res(Position pos);
    void del_res(Position pos);

    void same_centering();

    IGameForPlayer* game_controller;
    Countries country;
    Mod mod;
    double gold = 0;

    std::vector<std::unique_ptr<PlayerUnit>> my_units;
    std::vector<std::unique_ptr<PlayerTown>> my_towns;
    std::vector<PlayerBuild> unit_build;
    std::unique_ptr<PlayerMap> player_map;
    std::unique_ptr<PlayerRes> player_res;
    std::unique_ptr<PlayerScience> _player_science;
};

#endif // PLAYER_H
