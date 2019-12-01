#ifndef Player_H
#define Player_H

#include"Nave.h"

struct statement {
    string token;
    string action;
};

struct Controller {
    vector<Nave> flota; 
    string token;
    fs::path path;
    string prefijo;
    size_t sequence;
    
    Controller(const fs::path& path_, const string& prefijo_);
};

using statement_item = pair<size_t, statement>;
using statement_list_t = std::queue<statement_item>;
statement_list_t statements_;
class player {
    char columnas;
    size_t filas;
    unique_ptr<Controller> server;
    void start(const statement_item& item);
    void build(const statement_item& item);
    void attack(const statement_item& item);
public:
    player(string first);
    void execute();
    void load_tokens();
    void save_tokens();
};





#endif //Player_H
