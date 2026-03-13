#include "../../src/map.hpp"
#include <iostream>
#include <cassert>
#include <string>

class Integer {
public:
    static int counter;
    int val;
    
    Integer(int val) : val(val) {
        counter++;
    }

    Integer(const Integer &rhs) {
        val = rhs.val;
        counter++;
    }

    Integer& operator = (const Integer &rhs) {
        assert(false);
    }

    ~Integer() {
        counter--;
    }
};

int Integer::counter = 0;

class Compare {
public:
    bool operator () (const Integer &lhs, const Integer &rhs) const {
        return lhs.val < rhs.val;
    }
};

int main() {
    sjtu::map<Integer, std::string, Compare> map;
    
    // Insert
    for (int i = 0; i < 10; ++i) {
        std::string string = "";
        for (int number = i; number; number /= 10) {
            char digit = '0' + number % 10;
            string = digit + string;
        }
        if (i & 1) {
            map[Integer(i)] = string;
            auto result = map.insert(sjtu::pair<Integer, std::string>(Integer(i), string));
            assert(!result.second);
        } else {
            auto result = map.insert(sjtu::pair<Integer, std::string>(Integer(i), string));
            assert(result.second);
        }
    }
    
    std::cout << "Size after insertions: " << map.size() << std::endl;
    
    // Erase specific elements (like the test does)
    for (int i = 0; i < 10; ++i) {
        if (i > 1 && i <= 5) {
            continue;
        }
        assert(map.count(Integer(i)) == 1);
        assert(map.find(Integer(i)) != map.end());
        map.erase(map.find(Integer(i)));
        std::cout << "After erasing " << i << ", size = " << map.size() << std::endl;
    }
    
    std::cout << "Size after partial erases: " << map.size() << std::endl;
    
    // Should have 4 elements left: 2, 3, 4, 5
    if (map.size() != 4) {
        std::cout << "ERROR: Expected size 4, got " << map.size() << std::endl;
        return 1;
    }
    
    std::cout << "Test passed!" << std::endl;
    return 0;
}
