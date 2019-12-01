#ifndef Player_H
#define Player_H

#include"Nave.h"

struct statement {
    string token;
    string action;
};

struct Player {
    vector<Nave> flota; 
    string token;
    fs::path path;
    string prefijo;
    size_t sequence;
    
    Player(const fs::path& path_, const string& prefijo_);
};

using statement_item = pair<size_t, statement>;
using statement_list = queue<statement_item>;

class Controller {
    char columnas;
    size_t filas;
    vector<unique_ptr<Player>> players;
    statement_list statements;

    void start(const statement_item& item);
    void build(const statement_item& item);
    void attack(const statement_item& item);

public:
    Controller(string first, string second);
    
    void load_tokens();
    void save_tokens();
    void execute();
};





#endif //Player_H
