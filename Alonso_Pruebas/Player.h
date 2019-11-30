#ifndef Player_H
#define Player_H

#include"Nave.h"

struct to_send {
    string identify;
    string action;
    string parameter;
};

struct Player {
    vector<Nave> flota; 
    string token;
    fs::path path;
    string prefijo;
    size_t sequence;
    
    Player(const fs::path& path_, const string& prefijo_);
};

using to_send_item = pair<size_t, to_send>;

class Controller {
    char columnas;
    size_t filas;
    vector<unique_ptr<Player>> players;

    void start(const string& name, const to_send_item& item);
    void build(const to_send_item& item);
    void attack(const to_send_item& item);

public:
    Controller(string first, string second);
    
    
};





#endif //Player_H
