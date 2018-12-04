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
hashes::hashes() {
    for(int i = 0; i < tableSize; i++){
        HashTable[i] = new item ;
        HashTable[i] -> filename = "N/A" ;
        HashTable[i] -> index = "N/A" ;
        HashTable[i] -> next = NULL ;
    }

}

//Function: Hash():
//Input Parameter: 1st value-The chunk of data that is going to be compared to see if
//there are others with similar phrases.
//Output Parameter: Index value of where to insert Input Parameter data into
//the HashTable
//Definition: Going to return an index value of where to insert the file
//information by adding up the string's ASCII values (not including punctuation)
//and comparing with others.
int hashes::Hash(string chunkingString){
    int hash = 0;
    int index;

    for(int i =0; i < chunkingString.length(); i++){
        hash = hash + (int)chunkingString[i];
    }

    index = hash;
    return index;
}

//Function: getdir():
//Input Parameter: 1st value-the directory string value, 2nd value-the
//location of the vector of where the files are going to be
//Output Parameter: return 0 value
//Definition: Going to go to the directory and put the files in the
//file vector
int hashes::getdir (string dir, vector<string> &files)
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

//Function: addData():
//Input Parameter: 1st-The chunk of data that is going to be compared to see if
//there are others with similar phrases, 2nd value-the filename of the document, 3rd
//value-the index of where the chunk starts.
//Output Parameter: No Output Parameters
//Definition: Inserts the filename and the index of where the
//chunk of the string starts into the HashTable.
void hashes::addData(string chunkingString, string filename, int index) {
    int index1 = Hash(chunkingString);

    if(HashTable[index1] -> filename == "N/A"){
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

