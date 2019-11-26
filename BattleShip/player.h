//
// Created by mauri on 26-Nov-19.
//

#ifndef POO_II_BATTLESHIP_PLAYER_H
#define POO_II_BATTLESHIP_PLAYER_H

#include "Header.h"
extern std::map<model_t, model_size_t> predefined_fleet;

using layout_t = std::map<location_t, bool>;
class ship{
private:
    // attributes
    location_t location_;
    navy_status_t status_;
    model_t model_;
    dimension_t dimension_;
    layout_t layout_;
    // methods
    bool is_detroyed();
    // friends
    friend class player_t;
public:
    // constructor
    ship(const location_t& location, const model_t& model, const orientation_t& orientation);
    // methods
    navy_status_t get_status();
};
using hit_result_t = std::pair<std::unique_ptr<ship>&, bool>;
using fleet_t = std::vector<std::unique_ptr<ship>>;
using fleet_size_t = std::map<model_t, size_t>;

class player {
private:
    // attributes
    text_t name_;
    fleet_t fleet_;
    fleet_size_t fleet_size_;
    size_t id_;
    size_t sequence_;
    path_t path_;
    text_t prefix_;

    // methods
    bool is_navy_outside(const rectangle_t& rect, const rectangle_t& battle_field);
    bool is_navy_overlap(const rectangle_t& rect);
    status_t can_add_navy(const model_t& model, const rectangle_t& rect, const rectangle_t& battle_field);
};


#endif //POO_II_BATTLESHIP_PLAYER_H
