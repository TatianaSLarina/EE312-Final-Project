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

Function:
Preconditions:
Postconditions:
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
            if (cheaterArr[i][j]>=minCheatsize)
                cout<<"Coincidences between "<< names[i] <<" and "<< names[j] <<": "<<cheaterArr[i][j]<<endl;

        }
    }


    return;
}
