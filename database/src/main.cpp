#include "../include/network.h"

int main() {

    DataBase carshop;

    carshop.parse();
    carshop.mkdir();

    createServer(carshop);
    
    return 0;
}