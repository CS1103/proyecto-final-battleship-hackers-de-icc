#include "Controller.h"
using namespace std;

int main() {
    player *con= new player("hola");
    con->execute();
    delete con;
    return 0;
}
