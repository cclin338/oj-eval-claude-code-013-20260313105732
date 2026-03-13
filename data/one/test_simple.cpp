#include "../../src/map.hpp"
#include <iostream>
#include <string>

int main() {
    sjtu::map<int, std::string> map;
    
    // Insert a few elements
    map.insert(sjtu::pair<int, std::string>(1, "one"));
    map.insert(sjtu::pair<int, std::string>(2, "two"));
    map.insert(sjtu::pair<int, std::string>(3, "three"));
    
    std::cout << "Size after inserts: " << map.size() << std::endl;
    std::cout << "Empty? " << map.empty() << std::endl;
    
    // Erase all
    while (map.begin() != map.end()) {
        std::cout << "Erasing key: " << map.begin()->first << std::endl;
        map.erase(map.begin());
        std::cout << "Size after erase: " << map.size() << std::endl;
    }
    
    std::cout << "Final size: " << map.size() << std::endl;
    std::cout << "Empty? " << map.empty() << std::endl;
    
    return 0;
}
