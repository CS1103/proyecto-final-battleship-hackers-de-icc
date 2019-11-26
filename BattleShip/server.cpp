
//
// Created by rudri on 11/15/2019.
//

#include "server.h"

std::map<model_t, model_size_t> predefined_fleet {
    {model_t::aircraft_carrier, {1, {4, 1}}},
    {model_t::battle_crusier,   {1, {3, 1}}},
    {model_t::submarine,        {1, {2, 1}}},
    {model_t::torped_boat,      {1, {1, 1}}}
};

layout_t generate_layout(const location_t& l, const dimension_t& d) {
    layout_t layout;
    for (size_t i = 0; i < d.w; ++i)
        for (size_t j = 0; j < d.h; ++j)
            layout[{l.x + i, l.y + j}] = false;
    return layout;
}

bool is_inside(const location_t& location, const rectangle_t& rectangle) {
    auto [x, y] = location;
    auto [l, d] = rectangle;
    return (x >= l.x && x < l.x + d.w && y >= l.y && y < l.y + d.h);
}

bool are_intersected(const rectangle_t& r1, const rectangle_t& r2) {
    if (r1.first.x > r2.first.x + r2.second.w - 1 ||
        r2.first.x > r1.first.x + r1.second.w - 1)
        return false;
    return !(r1.first.y > r2.first.y + r2.second.h - 1 ||
             r2.first.y > r1.first.y + r1.second.h - 1);
}

dimension_t calculate_dimension(const model_t& model, const orientation_t& orientation) {
    auto dim = predefined_fleet[model].second;
    return orientation == orientation_t::horizontal ?
           dimension_t{ dim.w, dim.h } :
           dimension_t{ dim.h, dim.w };
}

navy_t::navy_t(const location_t& location, const model_t& model, const orientation_t& orientation) :
        location_{ location },
        status_{ navy_status_t::healthy },
        model_{ model },
        dimension_{ calculate_dimension(model, orientation) },
        layout_{ generate_layout(location_, dimension_) } { }

navy_status_t navy_t::get_status() { return status_; }

bool navy_t::is_detroyed() {
    return std::all_of(begin(layout_), end(layout_),
                       [](auto status) { return status.second == true; });
}

size_t server_t::get_fleet_size() {
    return fleet_.size();
}

server_t::server_t(path_t path, text_t prefix):
    path_{path}, prefix_{prefix}, sequence_{1}, id_{0} { }

hit_result_t server_t::hit_navy(location_t location) {
    for (auto& n : fleet_) {
        if (is_inside(location, { n->location_, n->dimension_ })) {
            n->layout_[location] = true;
            n->status_ = n->is_detroyed() ?
                         navy_status_t::destroyed :
                         navy_status_t::damaged;
            return { n, true };
        }
    }
    auto ptr = std::make_pair (std::unique_ptr<navy_t>(), false);
    return ptr;
}

void server_t::list_fleet() {
    for (const auto& n : fleet_)
        std::cout << "x: " << n->location_.x << " y: " << n->location_.y << '\n';
}

size_t server_t::get_id() {
    return id_;
}

void server_t::set_id(size_t value) {
    id_ = value;
}

text_t server_t::get_name() {
    return name_;
}

void server_t::set_name(text_t value) {
    name_ = value;
}

path_t server_t::get_path() {
    return path_;
}

text_t server_t::get_prefix() {
    return prefix_;
}

size_t& server_t::sequence() {
    return sequence_;
}

bool server_t::is_fleet_destroyed() {
    return std::all_of(begin(fleet_), end(fleet_),
                       [](auto& navy) { return navy->get_status() == navy_status_t::destroyed; });
}