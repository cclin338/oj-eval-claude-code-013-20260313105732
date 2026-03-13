#include "../../src/map.hpp"
#include <iostream>

int main() {
    std::cout << "Creating map..." << std::endl;
    sjtu::map<int, int> Q;
    std::cout << "Map created" << std::endl;
    
    std::cout << "Inserting 1905..." << std::endl;
    Q[1905] = 1905;
    std::cout << "Inserted 1905, size=" << Q.size() << std::endl;
    
    std::cout << "Done" << std::endl;
    return 0;
}
