//
// Created by rudri on 11/15/2019.
//

#ifndef BATTLESHIP_SERVER_PLAYER_H
#define BATTLESHIP_SERVER_PLAYER_H

#include "Header.h"

extern std::map<model_t, model_size_t> predefined_fleet;

using layout_t = std::map<location_t, bool>;


class server_t {
private:
    //-Atributos
    path_t         path_;
    text_t         prefix_;
public:
    //-Constructor
    server_t(const path_t& path, const text_t& prefix);
    path_t get_path();
    text_t get_prefix();

    //-Metodos


};

#endif //BATTLESHIP_SERVER_PLAYER_H