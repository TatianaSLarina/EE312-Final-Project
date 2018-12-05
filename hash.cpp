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
    cout<<index<<endl;

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
void Hash::getCheaters(int numDocs, string ArrNames[])
{
    int cheaterArr[numDocs][numDocs] = {0};

    for(int i = 0; i<numDocs ; i++)
    {
        for (int j = i; j<numDocs; j++)
            cheaterArr[i][j]=0;

    }


    for(int i = 0; i<HASH_SIZE ; i++)
    {
        if(HashTable[i])
        {   cout<<i<<" : ";

            HashList * temp = HashTable[i];
            while(temp)
            {
                HashList * temp2 = temp->next;
                while(temp2)
                {	cout<<temp->fNum<< " - ";
                    cout<<temp2->fNum<<" ,";
                    cheaterArr[temp2->fNum][temp->fNum]++;
                    cout<<" now "<<cheaterArr[temp2->fNum][temp->fNum]<<"; ";
                    temp2 = temp2->next;
                }
                temp = temp->next;
            }
            cout<<endl;
        }
    }
    cout<<endl;

    for(int i = 0; i<numDocs ; i++)
    {
        for (int j = i; j<numDocs; j++)
        {
            if (cheaterArr[i][j]>0)
                cout<<"Coincidences between "<< ArrNames[i] <<" and "<< ArrNames[j] <<": "<<cheaterArr[i][j]<<endl;

        }
    }


    return;
}
