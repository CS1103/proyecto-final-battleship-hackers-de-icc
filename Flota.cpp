#include"Flota.h"

Aircraft_carrier::Aircraft_carrier(size_t id, position posicion, char orientacion) :
    Nave(id, posicion, orientacion) {}

Battlecruiser::Battlecruiser(size_t id, position posicion, char orientacion) :
    Nave(id, posicion, orientacion) {}

Submarine::Submarine(size_t id, position posicion, char orientacion) :
    Nave(id, posicion, orientacion) {}

Torpedo_boat::Torpedo_boat(size_t id, position posicion, char orientacion) :
    Nave(id, posicion, orientacion) {}






