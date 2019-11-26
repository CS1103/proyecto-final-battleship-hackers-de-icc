//
// Created by mauri on 26-Nov-19.
//

#ifndef POO_II_BATTLESHIP_PLAYER_H
#define POO_II_BATTLESHIP_PLAYER_H

#include "Header.h"
#include "server.h"
struct statement_t {
    action_t action;
    text_t token;
    status_t status;
    text_t parameter;
};
using statement_item_t = std::pair<size_t, statement_t>;
using statement_list_t = std::queue<statement_item_t>;
using path_list_t = std::vector<path_t>;
using winner_t = std::optional<size_t>;

class controller_t {
    private:
        // attributes
        text_t              columns_;
        size_t              rows_;
        statement_list_t    statements_;
        winner_t            winner_;

        // methods
        statement_t     push_statement(path_t file_name);
        void            start(statement_item_t item);
        void            build(statement_item_t item);
        void            attack(statement_item_t item);

    public:
        // constructor
        controller_t(size_t rows, std::string_view columns, std::string_view path, std::string_view second);
        // methods
        void            execute();
        void            load_tokens();
        void            save_tokens();
    };

};


#endif //POO_II_BATTLESHIP_PLAYER_H
