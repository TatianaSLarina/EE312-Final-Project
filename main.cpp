#include <vector>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>

#include "hash.h"

using namespace std;

int main(int argc, char *argv[]) {
    hashes Hash1;
    string dir = string("sm_doc_set");
    vector<string> files = vector<string>();
    int i = 0;
    int nWordsequence = atoi(argv[1])-1;

    Hash1.getdir(dir,files);

    for(int Size = files.size(); Size!=0; Size--){
        ifstream file(files[i].c_str());
        stringstream buffer;
        buffer << file.rdbuf();
        string chunkingDocument = buffer.str();
        i++;

        int index = 0;
        for(int lengthOfchunkingDocument = chunkingDocument.length(); lengthOfchunkingDocument != 0; lengthOfchunkingDocument --){
            string tempstring = chunkingDocument.substr (index, index+nWordsequence);
            Hash1.addData(tempstring, files[i], index);
        }
    }


    return 0;
}