//
// Created by atanz on 12/3/2018.
//

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <cstdlib>
#include <iostream>
#include <string>

#include "hash.h"

using namespace std;

//Function: hash():
//Input Parameter: No input parameters because it is the constructor
//Output Parameter: No output parameters because it is the constructor
//Definition: Constructor to create hash() for each index which will include
//            the filename, the index value of where the n-letter phrase starts
//            and the pointer to the next node in case there is another item to
//            be placed at that index
hash::hash() {
    for(int i = 0; i < tableSize; i++){
        HashTable[i] = new item ;
        HashTable[i] -> filename = "empty" ;
        HashTable[i] -> index = "empty" ;
        HashTable[i] -> next = NULL ;
    }

}

//Function: getdir():
//Input Parameter: 1st value-the directory string value, 2nd value-the
//location of the vector of where the files are going to be
//Output Parameter: return 0 value
//Definition: Going to go to the directory and put the files in the
//file vector
int hash::getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

//Function: Additem():
//Input Parameter:
//Output Parameter:
//Definition:
void hash::Additem(string filename, string index) {
    int index1 = Hash(filename);

    if(HashTable[index1] -> filename == "empty"){
        HashTable[index1] -> filename = filename;
        HashTable[index1] -> index = index;
    }
    else{
        item* item1 = HashTable[index1];
        item* item2 = new item;

        while(item1 -> next != NULL){
            item1 = item1 -> next;
        }


        item2 -> filename = filename;
        item2 -> index = index;
        item2 -> next = NULL;

        item1 -> next = item2;
    }
}

//Function: ItemsTotal():
//Input Parameter:
//Output Parameter:
//Definition:
int hash::ItemsTotal(int index) {
    int count = 0;

    if(HashTable[index]->filename == "empty") {
        return count;
    }
    else{
        count++;
        item* item1 = HashTable[index];
        while(item1 -> next != NULL){
            count++;
            item1 = item1 -> next;
        }
    }
    return count;
}

//Function: PrintTable():
//Input Parameter:
//Output Parameter:
//Definition:
void hash::PrintTable() {
    int number;
    for(int i=0; i < tableSize; i++){
        number = ItemsTotal(i);
        cout << "index = " << i << endl;
        cout << HashTable[i]->filename << endl;
        cout << HashTable[i]->index << endl;
        cout << number << endl;
    }
}

//Function: Hash():
//Input Parameter:
//Output Parameter:
//Definition:
int hash::Hash(string key){
    int hash = 0;
    int index;

    for(int i =0; i < key.length(); i++){
        hash = hash + (int)key[i];
    }

    index = hash % tableSize;
    return index;
}

