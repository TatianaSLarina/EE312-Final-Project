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

int main() {
    hash Hash1;
    string dir = string("sm_doc_set");
    vector<string> files = vector<string>();

    Hash1.getdir(dir,files);
    ifstream file(files[2].c_str());
    stringstream buffer;
    buffer << file.rdbuf();
    string test = buffer.str();
    cout << test << endl;

    
    return 0;
}