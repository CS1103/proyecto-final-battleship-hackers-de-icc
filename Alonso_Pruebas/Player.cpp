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

string random_name(size_t length_first, size_t length_second) {
    srand(time(0));
    int random = rand()%23;

    char letras[] = {'a', 'b','c','d', 'e','f','g','h', 'i','j','k','l','m','n', 'o','p','q','r','s','t', 'u','v','w','x','z'};
    string first_name = "", second_name = "";

    for(; length_first > 0; length_first--) 
        first_name = first_name + letras[random];
    

    for(; length_second > 0; length_second--) 
        second_name = second_name + letras[random];
     
    return first_name + " " + second_name;
}

//position = pair<char, size_t>
Nave random_nave() {
    srand(time(0));

    char columnas[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    size_t filas[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    char orientacion[2] = {'H' , 'V'};
    char flota [4] = {'A', 'B', 'S', 'T'};

    Nave temp(flota[rand()%3], {columnas[rand()%9], filas[rand()%9]}, orientacion[rand()%1]);

    return temp;
}

position random_attack() {
    srand(time(0));

    char columnas[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    size_t filas[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    position temp = make_pair(columnas[rand()%9], filas[rand()%9]);

    return temp;
}

void Controller::start(const to_send_item& item) {
    auto& player = players[item.first];
    string action = "HANDSHAKE=";
    string nombre = random_name(5, 5);

    auto file_name = player->prefijo + to_string(player->sequence++) + ".in";
    ofstream file(player->path / "in"s / file_name);

    file << action << nombre << '\n';
}

void Controller::build(const to_send_item& item) {
    auto& player = players[item.first];
    string tk = "TOKEN=";
    string action = "PLACEFLEET=";

    auto file_name = player->prefijo + to_string(player->sequence++) + ".in";
    ofstream file(player->path / "in"s / file_name);

    auto temp_nave = random_nave();

    file << tk << player->token << '\n';
    file << action << temp_nave.id << '-' <<  temp_nave.posicion.first << temp_nave.posicion.second << '-' << temp_nave.orientacion << '\n';
}

void Controller::attack(const to_send_item& item) {
    auto& player = players[item.first];
    string tk = "TOKEN=";
    string action = "ATTACK=";
    
    auto file_name = player->prefijo + to_string(player->sequence++) + ".in";
    ofstream file(player->path / "in"s / file_name);

    auto temp_nave = random_nave();

    file << tk << player->token << '\n';
    file << action << temp_nave.posicion.first << temp_nave.posicion.second << '\n';
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








