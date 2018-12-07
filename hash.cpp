#include <string>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include "hash.h"
using namespace std;


/****************************************
//Function implementations for Hashtable
*****************************************/


/****************************
computeHash

Function: computeHash()
Preconditions: the key for the hashing
Postconditions: output the hash associated with the phrase
*****************************/
int Hash::computeHash(string s)
{
    int length = s.length();
    int index = 0;

    for (int i = 0; i<length; i++)
    {
        double power = pow(HASH_CALC_NUM, (double)i);
        index+=s[length-i-1]*(int)power;
    }

    if (index<0)
    {
        index *=-1;
        index/=2;
    }

    index %=HASH_SIZE;

    if(index<0 || index>HASH_SIZE)
        return FAIL;

    return index;

}


/****************************
makeHash

Function: makeHash()
Preconditions: the hash location, the file number
Postconditions: the hash table location
*****************************/
int Hash::makeHash(string s, int id)
{	cout<<endl;
    cout<<s<<endl;

    int i = computeHash(s);
    cout <<i<<endl;
    HashList * temp = new HashList;
    temp->fNum = id;
    temp->next = NULL;
    if (HashTable[i] ==NULL)
        HashTable[i] = temp;
    else
    {
        temp->next = HashTable[i];
        HashTable[i] = temp;
        cout<<"Inserting before "<<(HashTable[i]->next->fNum)<<endl;

    }
    cout<<HashTable[i]->fNum<<endl;




    return 1;

}

/****************************
getCheaters

Function: getCheaters()
Preconditions: the number of documents, the names of the documents, and the minimum size of what constitutes as
cheating between two documents
Postconditions: output the documents that pass cheating conditions
*****************************/
void Hash::getCheaters(int numDocs, vector<string> &names, int minCheatsize)
{

    std::vector< vector<int> > cheaterArr(numDocs, vector<int>(numDocs));

    for(int i = 0; i<numDocs ; i++)
    {
        for (int j = i; j<numDocs; j++)
            cheaterArr[i][j]=0;
    }


    for(int i = 0; i<HASH_SIZE ; i++)
    {
        if(HashTable[i])
        {
            HashList * temp = HashTable[i];
            while(temp)
            {
                HashList * temp2 = temp->next;
                while(temp2)
                {
                    cheaterArr[temp2->fNum][temp->fNum]++;
                    temp2 = temp2->next;
                }
                temp = temp->next;
            }
        }
    }

    for(int i = 0; i<numDocs ; i++)
    {
        for (int j = i; j<numDocs; j++)
        {
            hashNode *Node;
            if (cheaterArr[i][j]>=minCheatsize)
                if(i==0 && j==0){
                    hashNode *heads;
                    heads = new hashNode;
                    heads->fd1 = names[i];
                    heads->fd2 = names[j];
                    heads->instants = cheaterArr[i][j];
                    heads->next = NULL;
                    head = heads;
                }
                else{
                    hashNode *headss;
                    headss = new hashNode;
                    headss->fd1 = names[i];
                    headss->fd2 = names[j];
                    headss->instants = cheaterArr[i][j];
                    headss->next = NULL;
                    Node = head;
                    while(Node->next != NULL){
                        Node = Node ->next;
                    }
                    Node->next = headss;
                }
        }
    }

    sorting();
    while(head)
    {
        cout << "Coincidences between " << head->fd1 << " and " << head->fd2 << ": " << head->instants << endl;
        head = head->next;
    }
    return;
}

/**********************************************************************************************************
Function highest_index_helper_function():
Input Parameter: the hashNode that is going to traverse through head, the comparator for the highest index
Output Parameter: the highest index that is currently in the list
Definition: Finds the highest index in the function
**********************************************************************************************************/
int Hash:: highest_index_helper_function(hashNode *traversePtr, int lowest_index){
// Going to the find the lowest song in the list currently
    traversePtr=head;
    while (traversePtr->next != NULL) {
        if (lowest_index < traversePtr->next->instants) {
            lowest_index = traversePtr->next->instants;
            traversePtr = traversePtr->next;
        }
        else {
            traversePtr = traversePtr->next;
        }
    }
    return lowest_index;
}

/**********************************************************************************************************
Function update_index_helper_function():
Input Parameter: the hashNode that is going to traverse through index, the comparator for the highest index
                 and the hashNode linked list with the updated descending order of indices
Output Parameter: the highest index that is currently found
Definition: Will update index with the ascending order of indices
 *********************************************************************************************************/
int Hash:: update_index_helper_function(int lowest_index, hashNode *traversePtr){
    if (head != NULL) {
        lowest_index = traversePtr->instants;
    }
    head = traversePtr;
    return lowest_index;
}


/****************************************************************************************
Function removesong():
Input Parameters: lowest_index is the address of the index that is going to be removed
from the temp array
Output Parameter: Nothing
***************************************************************************************/
void Hash::removeindex(int const lowest_index){
    hashNode *tempNode = head;
    hashNode *Node = NULL;
    int first_element_encountered_flag=0;
    hashNode *finalNode = tempNode;

    if(tempNode==NULL){ //List is empty
        return;
    }


    while(tempNode->next!=NULL){
        if(tempNode->instants == lowest_index){
//First element is going to be deleted from song list
            if(first_element_encountered_flag==0){
                head = tempNode->next;
                delete tempNode;
                return;
            }
            else {
//Normal case
                Node->next = tempNode->next;
            }
            delete tempNode;
            return;
        }
        first_element_encountered_flag++;
        Node = tempNode;
        tempNode = tempNode -> next;
    }


//last element is going to be deleted from song list
    if(tempNode->instants == lowest_index){
        if(first_element_encountered_flag==0){
            head=NULL;     //if it is the only element left in the list to be deleted
            delete tempNode;
            return;
        }
        Node->next = NULL;
        head=finalNode;
        delete tempNode;
        return;
    }
    return;
}

void Hash::sorting(){
    hashNode *traversePtr = head;
    hashNode *copy_Tempt = NULL;

    int lowest_index = traversePtr->instants;
    hashNode *index;

    // Going to find the lowest song in the list currently
    while (traversePtr != NULL) {
        lowest_index = highest_index_helper_function(traversePtr, lowest_index);

        // Going to add the lowest element into the temporary buffer
        hashNode *Tempt = new hashNode;
    while(traversePtr->instants != lowest_index){
        traversePtr=traversePtr->next;

    }
        Tempt->fd1 = traversePtr->fd1;
        Tempt->fd2 = traversePtr->fd2;
        Tempt->instants = lowest_index;
        Tempt->next = NULL;
        hashNode *traversePtr2;

        if (copy_Tempt != NULL) {
            traversePtr2 = copy_Tempt;
            while(traversePtr2->next != NULL) {
                traversePtr2 = traversePtr2->next;
            }
            traversePtr2->next = Tempt;
            copy_Tempt = copy_Tempt->next;
        } else {
            copy_Tempt = Tempt;
            index = copy_Tempt;
        }

        removeindex(lowest_index);    // Removes the lowest song from the general songs list so can find new lowest value
        traversePtr = head;
        lowest_index = update_index_helper_function(lowest_index, traversePtr);
    }

    head = index;


}
