#ifndef Flota_H
#define Flota_H

#include"Nave.h"

//------------------------------------------------
class Aircraft_carrier : public Nave {
public:
    Aircraft_carrier(size_t id, position posicion, char orientacion); 
};

//------------------------------------------------
class Battlecruiser : public Nave {
public:
    Battlecruiser(size_t id, position posicion, char orientacion); 
};

//------------------------------------------------
class Submarine : public Nave {
public:
    Submarine (size_t id, position posicion, char orientacion); 
};

//------------------------------------------------
class Torpedo_boat : public Nave {
public:
    Torpedo_boat(size_t id, position posicion, char orientacion); 
};

#endif //Flota_H
