
#ifndef BST_312_H
#define BST_312_H

#include <cstdlib>  // Provides size_t
#include <vector>
#include <string>
#include <iostream>

/*  hash.h
  EE 312 Fall 2018

 class that contains all the functions for creating
 a hash table


*/
using namespace std;

#define SUCCESS 0;
#define FAIL -1;
#define HASH_SIZE 6151
#define HASH_CALC_NUM 11.0

class Hash {


private:
    struct HashList {	// basically the linked list tyoe that will be the actual entries stored in the hash table
        int fNum;
        HashList *next;
    };

    HashList* HashTable[HASH_SIZE];


    string processString(string s);
    int computeHash(string s);


public:

    Hash()
    {
        cout<<"initializing\n";
        for (int i = 0; i<HASH_SIZE; i++)
            HashTable[i] = NULL;
    }


    //Copy constructor
    // Hash(const Hash & src);

    ~Hash()
    {

    }


/****************************
makeHash

Function:
Preconditions:
Postconditions:
*****************************/
    int makeHash(string s, int id);

/****************************
getCheaters

Function:
Preconditions:
Postconditions:
*****************************/
    void getCheaters(int numDocs, vector<string> &names, int minCheatsize);



};

#endif


























/****************************
makeEmpty

Function: Removes all the items from the hash table.
Preconditions:
Postconditions:
*****************************/
// void makeEmpty();

/****************************
isEmpty

Function: Checks to see if hash table is empty
Preconditions: //
Postconditions: //
*****************************/
//  bool isEmpty() const;

/****************************
isFull

Function: Determines if there's room to add things to the hash... shouldn't be an issue TBH....
Preconditions:
Postconditions:
*****************************/
// bool isFull() const;

/****************************
insertItem

Function: Adds newItem to the hash
Preconditions: BST has been initialized and is not full.
Postconditions: newItem is in the proper position for a BST.
*****************************/
//void insertItem(const ItemType& newItem);

/****************************
deleteItem

Function: Removes target from BST.
Preconditions: BST has been initialized.
Postconditions: If found, element has been removed from BST.
*****************************/
// void deleteItem(const ItemType& newItem);
