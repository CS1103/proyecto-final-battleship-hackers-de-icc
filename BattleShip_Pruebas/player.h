#ifndef POO_II_BATTLESHIP_PLAYER_H
#define POO_II_BATTLESHIP_PLAYER_H

#include "Header.h"
#include "server.h"
std::map<model_t, model_size_t> predefined_fleet {
        {model_t::aircraft_carrier, {1, {4, 1}}},
        {model_t::battle_crusier,   {1, {3, 1}}},
        {model_t::submarine,        {1, {2, 1}}},
        {model_t::torped_boat,      {1, {1, 1}}}
};
class navy_t {
private:
    // attributes
    location_t location_;
    model_t model_;
    dimension_t dimension_;
    layout_t layout_;
    friend class player_t;
public:
    // constructor
    navy_t(const location_t& location, const model_t& model, const orientation_t& orientation);
    // methods
};

using hit_result_t = std::pair<std::unique_ptr<navy_t>&, bool>;
using fleet_t = std::vector<std::unique_ptr<navy_t>>;
using fleet_size_t = std::map<model_t, size_t>;
struct statement_t {
    action_t action;
    text_t token;
    text_t scope;
    status_t  status;
};
using statement_item_t = std::pair<size_t, statement_t>;
using statement_list_t = std::queue<statement_item_t>;
using path_list_t = std::vector<path_t>;
using servertype = std::unique_ptr<server_t>;
class player_t {
    private:
        // attributes
        text_t          name_;
        fleet_t         fleet_;
        fleet_size_t    fleet_size_;
        path_t          path_;
        text_t          prefix_;
        //
        servertype          server_;
        text_t              columns_;
        size_t              rows_;
        statement_list_t    statements_;

        // methods
        statement_t     push_statement(path_t file_name);
        void            start(statement_item_t item);
        void            build(statement_item_t item);
        void            attack(statement_item_t item);

    public:
        // constructor
        player_t(size_t rows, std::string_view columns, std::string_view path, std::string_view second);
        // methods
        void            execute();
        void            load_tokens();
        void            save_tokens();
    };

#endif //POO_II_BATTLESHIP_PLAYER_H
