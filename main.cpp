#include "Alonso_Pruebas/Player.h"

using namespace std;

int main() {
    Controller *con= new Controller("hola");
    con->execute();
    delete con;
    return 0;
}
