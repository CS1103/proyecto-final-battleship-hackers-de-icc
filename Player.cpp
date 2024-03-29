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

void Controller::start(const statement_item& item) {
    auto& player = players[item.first];
    string action = "HANDSHAKE=";
    string nombre = random_name(5, 5);

    auto file_name = player->prefijo + to_string(player->sequence++) + ".in";
    ofstream file(player->path / "in"s / file_name);

    file << action << nombre << '\n';
}

void Controller::build(const statement_item& item) {
    auto& player = players[item.first];
    string tk = "TOKEN=";
    string action = "PLACEFLEET=";

    auto file_name = player->prefijo + to_string(player->sequence++) + ".in";
    ofstream file(player->path / "in"s / file_name);

    auto temp_nave = random_nave();

    file << tk << player->token << '\n';
    file << action << temp_nave.id << '-' <<  temp_nave.posicion.first << temp_nave.posicion.second << '-' << temp_nave.orientacion << '\n';
}

void Controller::attack(const statement_item& item) {
    auto& player = players[item.first];
    string tk = "TOKEN=";
    string action = "ATTACK=";
    
    auto file_name = player->prefijo + to_string(player->sequence++) + ".in";
    ofstream file(player->path / "in"s / file_name);

    auto temp_attack = random_location();

    file << tk << player->token << '\n';
    file << action << temp_attack.first << temp_attack.second << '\n';
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

    return result;
}

void Controller::load_tokens()
{
    auto end_ = fs::directory_iterator{};
    std::error_code e;
    while (true) {
        try {
            fs::directory_iterator first_{ players[0]->path / "in"s };
            fs::directory_iterator second_{ players[1]->path / "in"s };
            while (first_ != end_ || second_ != end_) {
                if (first_ != end_) {
                    statements.push({ 0u, push_statement(*first_) });
                    fs::remove(*first_++, e);
                    if (e)
                        std::cerr << e.message() << "\n";
                }
                if (second_ != end_) {
                    statements.push({ 1u, push_statement(*second_) });
                    fs::remove(*second_++, e);
                    if (e)
                        std::cerr << e.message() << "\n";
                }
            }
        }
        catch (const std::exception& e) {
            std::cerr << e.what();
        }
    }
}

void Controller::save_tokens()
{
    auto end_ = fs::directory_iterator{};
    while (true) {
        try {
            while (!statements.empty()) {
                auto item = statements.front();
                statements.pop();
                if (item.second.action == "start")
                    start(item);

                else if (item.second.action == "build")
                    build(item);

                else if (item.second.action == "attack")
                    attack(item);

                else if (item.second.action== "lose" || item.second.action=="win")
                    break;
            }
        }
        
        catch (const std::exception& e) {
            std::cerr << e.what();
        }
    }
}

void Controller::execute()
{
    load_tokens(); 
    save_tokens(); 
}









