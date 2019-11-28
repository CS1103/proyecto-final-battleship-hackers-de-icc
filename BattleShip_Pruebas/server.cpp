
//
// Created by rudri on 11/15/2019.
//

#include "server.h"



layout_t generate_layout(const location_t& l, const dimension_t& d) {
    layout_t layout;
    for (size_t i = 0; i < d.w; ++i)
        for (size_t j = 0; j < d.h; ++j)
            layout[{l.x + i, l.y + j}] = false;
    return layout;
}

dimension_t calculate_dimension(const model_t& model, const orientation_t& orientation) {
    auto dim = predefined_fleet[model].second;
    return orientation == orientation_t::horizontal ?
           dimension_t{ dim.w, dim.h } :
           dimension_t{ dim.h, dim.w };
}


server_t::server_t(const path_t &path, const text_t &prefix) {

}

path_t server_t::get_path() {
    return path_;
}

text_t server_t::get_prefix() {
    return prefix_;
}

