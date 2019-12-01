#include "Alonso_Pruebas/Controller.h"

using namespace std;

int main() {
    Controller *con= new Controller("hola");
    con->execute();
    delete con;
    return 0;
}
