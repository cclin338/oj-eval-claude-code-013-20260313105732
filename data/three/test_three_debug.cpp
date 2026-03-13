#include<iostream>
#include<map>
#include<ctime>
#include<queue>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include "../../src/map.hpp"

using namespace std;

int main() {
    sjtu::map<int, int> Q;
    std::map<int, int> stdQ;
    
    srand(1);  // Fixed seed for reproducibility
    
    int num[30001];
    num[0] = 0;
    for(int i = 1; i <= 30000; i++) num[i] = num[i - 1] + rand() % 325 + 1; 
    for(int i = 1; i <= 60000; i++) swap(num[rand() % 30000 + 1], num[rand() % 30000 + 1]);
    
    cout << "Inserting 30000 elements..." << endl;
    for(int i = 1; i <= 30000; i++){
        int t = rand();
        stdQ[num[i]] = t; Q[num[i]] = t;
        if (i % 5000 == 0) {
            cout << "Inserted " << i << " elements, Q.size=" << Q.size() << endl;
        }
    }
    
    cout << "Q.size=" << Q.size() << " stdQ.size=" << stdQ.size() << endl;
    
    cout << "Shuffling and erasing..." << endl;
    sjtu::map<int, int>::iterator it;
    std::map<int, int>::iterator stdit;
    for(int i = 1; i <= 60000; i++) swap(num[rand() % 30000 + 1], num[rand() % 30000 + 1]);
    for(int i = 1; i <= 10325; i++){
        it = Q.find(num[i]); 
        if (it == Q.end()) {
            cout << "ERROR: Could not find element " << num[i] << endl;
            return 1;
        }
        Q.erase(it);
        stdit = stdQ.find(num[i]); stdQ.erase(stdit);
        if (i % 1000 == 0) {
            cout << "Erased " << i << " elements, Q.size=" << Q.size() << endl;
        }
    }
    
    cout << "After erasure: Q.size=" << Q.size() << " stdQ.size=" << stdQ.size() << endl;
    
    cout << "Iterating forward..." << endl;
    it = Q.begin();
    int count = 0;
    for(stdit = stdQ.begin(); stdit != stdQ.end(); stdit++){ 
        if (it == Q.end()) {
            cout << "ERROR: Q iterator reached end too early at count=" << count << endl;
            return 1;
        }
        if(stdit -> first != it -> first) {
            cout << "ERROR: Mismatch at count=" << count << " std=" << stdit->first << " sjtu=" << it->first << endl;
            return 1;
        }
        if(stdit -> second != (*it).second) {
            cout << "ERROR: Value mismatch" << endl;
            return 1;
        }
        it++;
        count++;
    }
    
    cout << "Forward iteration OK, count=" << count << endl;
    
    cout << "Iterating backward..." << endl;
    stdit = --stdQ.end();
    count = 0;
    for(it = --Q.end(); it != Q.begin(); it--){
        if(stdit -> first != it -> first) {
            cout << "ERROR: Backward mismatch at count=" << count << endl;
            return 1;
        }
        if(stdit -> second != (*it).second) {
            cout << "ERROR: Backward value mismatch" << endl;
            return 1;
        }
        stdit--;
        count++;
    }
    
    cout << "Backward iteration OK, count=" << count << endl;
    cout << "All checks passed!" << endl;
    
    return 0;
}
