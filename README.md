# BattleShip

|Integrantes|Código|URI|
|-----------|------|---|
|Alonso Barrios|201810483|[alonso1311](https://github.com/alonso1311)
|Mauricio Rodriguez|201810642|[mauricio-rodriguez](https://github.com/mauricio-rodriguez)
#El Proyecto battleship implementa una comunicación entre el jugador y el servidor. 
Nuestro programa lee los archivos que nos envía el servidor y el servidor lee los nuestros. Mediante algo similar 
a mensajes de protocolo http, ambos se relacionan a traves de mensaje de protocolo y status.
##*Las clases o archivos con los que contamos son*
1. Flota
2. Nave
3. Controller 
4. Player 
'''
###Donde
La clase nave(Que de hecho podria ser un struct) que contiene la orientacion y la posicion(pair) de la nave que vayamos a escoger,
al igual que su respectivo id.
```c++
class Nave {
public:
    size_t id;
    position posicion; 
    char orientacion;

    Nave(size_t id, position posicion, char orientacion);
};
```
El archivo flota.h contiene las clases hijas de la clase nave. Estas clases son las naves especificas que usara el programa
para posicionarlas en el tablero y comenzar a jugar 
```c++
class Aircraft_carrier : public Nave {
public:
    Aircraft_carrier(size_t id, position posicion, char orientacion); 
};
```
*ejemplo de clase heredada -> Aircraft_carrier.* 

Las clase controller nos permite así mismo hacer unas abstracción sobre 
lo que necesitamos hacer. Sin embargo, **la clase más importante es la clase player**

```c++
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
```
Esta clase realiza
- [x] Leída de archivos guardados por el servidor
- [x] Asignación de acciones a tomar
- [x] Registro del equipo
- [x] Construcción de la flota
- [x] Ataque a la flota enemiga

Se apoya de las funciones globales en el archivo
* random_name -- Genera el nombre inicial de la flota
* random_location -- Genera una posicion aleatoria
* random_nave -- Genera una nave con una posicion aleatoria

####La función global de mayor importancia es push_statement
Es esta función la que permite al player tomar las acciones ya
mencionadas en base 
a los datos obtenidos del server



