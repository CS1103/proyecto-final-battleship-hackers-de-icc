#include"Player.h"

Player::Player(const fs::path& path_, const string& prefijo_) :
    path{path_}, prefijo{prefijo_} {}

Controller::Controller(string first, string second) : columnas{'J'}, filas{10} {
    players.push_back(make_unique<Player>(fs::current_path() / first, "FirstPlayer")); 
    players.push_back(make_unique<Player>(fs::current_path() / second, "SecondPlayer")); 

    for(const auto& player : players) {
        if(!fs::exists(player->path / "in"))
            fs::create_directories(player->path / "in");

        if(!fs::exists(player->path / "out"))
            fs::create_directories(player->path / "out");
    }
}

void Controller::start(const string& name, const to_send_item& item) {
    auto& player = players[item.first];
    string action = "HANDSHAKE=";
    string nombre = name;

    auto file_name = player->prefijo + to_string(player->sequence++) + ".in";
    ofstream file(player->path / "in"s / file_name);

    file << action << nombre << '\n';
}

void Controller::build(const to_send_item& item) {
    
}

void Controller::attack(const to_send_item& item) {
    
}

/*void Player::Recibir() {
    auto end = fs::directory_iterator{};

    while(true) {
        fs::directory_iterator first{};
        fs::directory_iterator second{};
        fs::directory_iterator third{};

    }
}

void Player::Jugar() {

}*/








