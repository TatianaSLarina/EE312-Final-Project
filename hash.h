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

class hashes{
private:
    static const int tableSize =1000;

    struct item{
        string filename;
        string index;
        item* next;
    };

    item* HashTable[tableSize];

public:
    hashes();
    int Hash(string chunkingString);
    int getdir (string dir, vector<string> &files);
    void addData(string chunkingString, string filename, int index);
};




#endif //UNTITLED8_HASH_H
