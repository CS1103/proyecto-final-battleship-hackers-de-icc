#include "Controller.h"
using namespace std;

int main() {
    player *con= new player("Documents/");
    con->execute();
    delete con;
    return 0;
}
