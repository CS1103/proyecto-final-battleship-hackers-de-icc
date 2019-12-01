# BattleShip 

![](https://i.ytimg.com/vi/8rGoks7I7NU/maxresdefault.jpg)

## Introducción 
El juego está diseñado para jugarse entre dos personas. Se juega sobre dos tableros tridimensionales. Cada persona tiene un tablero que consiste de dos cuadrículas perpendiculares 10 x 10 con perforaciones. En una de ellas, la que queda horizontal, será su espacio naval y ahí colocará sus barcos. En la otra cuadrícula, la vertical, irá colocando marcadores que le ayudarán a ubicar la flota de su adversario. El objetivo es encontrar los barcos de tu oponente y hundir toda su flota. El primero en lograrlo ganará el juego.

## Objetivos
- Implementar los temas desarrollados durante el curso de POO II
- Efectuar una correcta lectura y escritura sobre archivos
- Implementar concurrencia asíncrona
- Implementar un sistema que se asemeje a la programación reactiva
- Desarrollar un programa que juegue en base a los elementos previos

## Nuestro programa
Este proyecto tiene una estructura Cliente-Servidor, en este caso se programó la parte de cliente.
Nuestro programa lee los archivos que nos envía el servidor. Mediante algo similar a mensajes de protocolo http, ambos se relacionan a traves de mensaje de protocolo y status.

## Clases
- **Nave:** esta clase se encarga de almacenar el *tipo de nave* (1 Aircraft carrier, 2 Battlecruisers, 3 Submarines, 4 Torpedo boat), *la posición en la que se encuentra* y *la orientación*.
- **Statement:** este almacena el *token* que envía el servidor y la *acción* que realizará en la siguiente jugada.
- **Player:** este almacena la *flota* del cliente, el *token*, sus *archivos* y un *sequence*.
- **Controller:** este se encarga de almacenar el tamaño del tablero *(10x10)*, el conjunto de *jugadores* y una lista de *statement*.

## Implementación del código
- **Nave:**

```c++
class Nave {
public:
    size_t id;
    position posicion; 
    char orientacion;

    Nave(size_t id, position posicion, char orientacion);
};
```
- **Statement:**

```c++
struct statement {
    string token;
    string action;
};
```
- **Player:**

```c++
struct Player {
    vector<Nave> flota;
    string token;
    fs::path path;
    string prefijo;
    size_t sequence

    Player(const fs::path& path_, const string& prefijo_);
};
```

- **Controller:**
```c++
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
```

## Funciones de aleatoriedad
- **random_name:** Genera el nombre aleatorio para el *HANDSHAKE*.
- **random_location:** Genera una posicion aleatoria.
- **random_nave:** Genera una nave aleatoria.

## Funciones extra
- **push_statement:** este se encarga de dar la siguiente *acción* y guardar el *token*.

## Operaciones del código
- [x] Leída de archivos guardados por el servidor
- [x] Asignación de acciones a tomar
- [x] Registro del equipo
- [x] Construcción de la flota
- [x] Ataque a la flota enemiga

## Compilador
```
g++ -lpthread *cpp -std=c++17 -lstdc++fs
```

## Hackers de ICC

|Integrantes|Código|URI|
|-----------|------|---|
|Alonso Barrios|201810483|[alonso1311](https://github.com/alonso1311)
|Mauricio Rodriguez|201810642|[mauricio-rodriguez](https://github.com/mauricio-rodriguez)

