//
// Created by atanz on 12/3/2018.
//

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#ifndef UNTITLED8_HASH_H
#define UNTITLED8_HASH_H

class hash{
private:
    static const int tableSize =10;

    struct item{
        string filename;
        string index;
        item* next;
    };

    item* HashTable[tableSize];

public:
    hash();
    int Hash(string chunkingString);
    int getdir (string dir, vector<string> &files);
    void addData(string filename, string index);
};




#endif //UNTITLED8_HASH_H
