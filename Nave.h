#ifndef Nave_H
#define Nave_H

#include"Header.h"

class Nave {
public:
    size_t id;
    position posicion; 
    char orientacion;

    Nave(size_t id, position posicion, char orientacion);
};

#endif //Nave_H
