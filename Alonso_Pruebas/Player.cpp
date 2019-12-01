#include"Player.h"

Player::Player(const fs::path& path_, const string& prefijo_) :
    path{path_}, prefijo{prefijo_} {}

Controller::Controller(string first, string second) : columnas{'J'}, filas{10} {
    make_unique<Player>(fs::current_path() / first, "Server");

        if(!fs::exists(players->path / "in"))
            fs::create_directories(players->path / "in");

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

position random_location() {
    srand(time(0));

    char columnas[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    size_t filas[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    position temp = make_pair(columnas[rand()%9], filas[rand()%9]);

    return temp;
}

Nave random_nave() {
    srand(time(0));

    char orientacion[2] = {'H' , 'V'};
    char flota [4] = {'A', 'B', 'S', 'T'};

    Nave temp(flota[rand()%3], random_location(), orientacion[rand()%1]);

    return temp;
}
statement push_statement(const fs::path& file_name) {
    ifstream file(file_name.generic_string());

    if(!file.is_open())
        throw runtime_error("no open");

    string line;
    getline(file, line, '\n');
    stringstream first(line);

    string action;
    getline(first, action, '\n');

    statement result {};

    string key_status, key_message;
    string value_status, value_message;

    if(action == "HANDSHAKE") {
        getline(file, line, '\n');
        stringstream second(line);

        getline(second, key_status, '=');
        getline(second, value_status, '\n');

        if(value_status == "ACCEPTED") {
            getline(second, key_message, '=');
            getline(second, value_message, '\n');

            result.token = value_message;
            result.action = "build";
        }

        else if(value_status == "REJECTED")
            result.action = "start";
    }

    else if(action == "PLACEFLEET") {
        getline(file, line, '\n');
        stringstream second(line);

        getline(second, key_status, '=');
        getline(second, value_status, '\n');

        if(value_status == "ACCEPTED") {
            getline(second, key_message, '=');
            getline(second, value_message, '\n');

            if(value_message == "FULL")
                result.action = "attack";

            else
                result.action = "build";
        }

        else if(value_status == "REJECTED")
            result.action = "build";
    }

    else if(action == "ATTACK") {
        getline(file, line, '\n');
        stringstream second(line);

        getline(second, key_status, '=');
        getline(second, value_status, '\n');

        if(value_status == "ACCEPTED") {
            getline(second, key_message, '=');
            getline(second, value_message, '\n');

            if(value_message == "FAILED" || value_message == "DAMAGED" || value_message == "DESTROYED")
                result.action = "attack";

            else if(value_message == "WINNER")
                result.action = "win";

            else if(value_message == "GAMEOVER")
                result.action = "lose";

        }

        else if(value_status == "REJECTED")
            result.action = "attack";

    }

void Controller::load_tokens()
{
    auto end_ = filesystem::directory_iterator{};
    std::error_code e;
    while (true) {
        try {
            filesystem::directory_iterator first_{ players->path / "out" };
            while (first_ != end_) {
                if (first_ != end_) {
                    statements_.push({ 0, push_statement(*first_) });
                    filesystem::remove(*first_++, e);
                    if (e)
                        std::cerr << e.message() << "\n";
                }
            }
        }
        catch (...) {
        }
    }
}
void Controller::start(const statement_item& item) {
    auto& player = players;
    string action = "HANDSHAKE=";
    string nombre = random_name(5, 5);

    auto file_name = player->prefijo + to_string(player->sequence++) + ".in";
    ofstream file(player->path / "in"s / file_name);

    file << action << nombre << '\n';
}

void Controller::build(const statement_item& item) {
    auto& player = players;
    string tk = "TOKEN=";
    string action = "PLACEFLEET=";

    auto file_name = player->prefijo + to_string(player->sequence++) + ".in";
    ofstream file(player->path / "in"s / file_name);

    auto temp_nave = random_nave();

    file << tk << player->token << '\n';
    file << action << temp_nave.id << '-' <<  temp_nave.posicion.first << temp_nave.posicion.second << '-' << temp_nave.orientacion << '\n';
}

void Controller::attack(const statement_item& item) {
    auto& player = players;
    string tk = "TOKEN=";
    string action = "ATTACK=";
    
    auto file_name = player->prefijo + to_string(player->sequence++) + ".in";
    ofstream file(player->path / "in"s / file_name);

    auto temp_attack = random_location();

    file << tk << player->token << '\n';
    file << action << temp_attack.first << temp_attack.second << '\n';
}


    return result;
}








