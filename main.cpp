#include <vector>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

using namespace std;

//Function: getdir():
//Input Parameter: 1st value-the directory string value,
//                 2nd value-the location of the vector of where the files are going to be
//Output Parameter: return 0 value
//Definition: Going to go to the directory and put the files in the
//file vector
int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    int dontOpenfirstTwo = 0;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }
    while ((dirp = readdir(dp)) != NULL) {
        if (dontOpenfirstTwo == 0)
            dontOpenfirstTwo++;
        else if (dontOpenfirstTwo == 1)
            dontOpenfirstTwo++;
        else {
            files.push_back(string(dir + "/" + dirp->d_name));
        }
    }
    closedir(dp);
    return 0;
}

//Function: readfile():
//Input Parameters: 1st value-the empty file vector where the file path names are stored
//                  2nd value-the index value of the file that needs to be read
//Output Parameters: the string value of the documents contents
//Definition: Going to read the correct file and output a string with the contents of the
//file that is going to be parsed through later
string readfile(vector<string> files, int i){
    ifstream file(files[i].c_str());
    stringstream buffer;
    buffer << file.rdbuf();
    string chunkingDocument = buffer.str();
    return chunkingDocument;
}

//Function: gettingChunk():
//Input Parameters: 1st value-the number of words that need to be in the chunk (second input in command line)
//                  2nd value-the location of where the chunk queue array is going to be stored
//                  3rd value-the string value of the document in question (words from document)
//                  4th value-index value of where in the document we are going to start the chunk reading
//Output Parameters: the vector of the words that are going to later be concatenated into a string
//Definition: Going to create a vector that will have n-words which will be used for concatenation later
vector<string> gettingChunk(int nWordsequence, vector<string> chunk, string chunkingDocument, int index){
    string tempstring;
    char period = '.';
    string space = "";
    int const1 = -43;
    int const2 = -46;
    int length = chunkingDocument.length();
    while(nWordsequence !=0) {
        if(index == length){
            chunk.clear();
            chunk.push_back("flag");
            nWordsequence = 0;
        }
        else if (std::isalpha(chunkingDocument[index])) {
            chunkingDocument[index] = std::toupper(chunkingDocument[index]);
            tempstring = tempstring + chunkingDocument[index];
            index++;
        }
        else if (std::isdigit(chunkingDocument[index])) {
            tempstring = tempstring + chunkingDocument[index];
            index++;
        }
        else if (int(chunkingDocument[index]) == const1)
            index++;
        else if (int(chunkingDocument[index]) == const2)
            index++;
        else{
            if(chunkingDocument[index] == period)
                index++;
            else {
                if(tempstring == space)
                    index++;
                else {
                    nWordsequence--;
                    chunk.push_back(tempstring);
                    index++;
                    tempstring.clear();
                }
            }
        }
    }
    return chunk;
}

//Function: chunkconcatenation():
//Input Parameters: 1st value-the number of words that need to be in the chunk (second input in command line)
//                  2nd value-the location of where the chunk queue array is going to be stored
//Output Parameters: The concatenated chunk that is going to be used for later comparisons. If the concatenated chunk
// just read "flag", then that means te file is done being read and there is no chunk to be concatenated.
//Definition: take the vector of the nWordsequence (second input from command line) and concatenate string
//for later comparisons
string chunkconcatenation(int nWordsequence, vector<string> chunk){
   int beginning = 0;
   string tempstring;
    if(chunk[beginning] != "flag") {
        for (int j = 0; j < nWordsequence; j++) {
            tempstring = tempstring + chunk[j];
        }
        cout << "string:" << tempstring << endl;
    }
    else {
        tempstring = "flag";
    }
    return tempstring;
}

int main(int argc, char *argv[]) {
    string dir = string(argv[1]);
    vector<string> files = vector<string>();
    int i = 0;
    int beginning =0;
    int nWordsequence = atoi(argv[2]);
    getdir(dir,files);

    //Go through all of the files to create chunks
    for(int Size = files.size(); Size!=0; Size--){
        string chunkingDocument = readfile(files, i);
        vector<string> chunk;
        string tempstring;
        int index = 0;

        //Go through a specific file to create chunks
        while(tempstring != "flag") {       //if tempstring="flag", then the file has finished being read
            chunk = gettingChunk(nWordsequence, chunk, chunkingDocument, index);
            tempstring = chunkconcatenation(nWordsequence, chunk);
            if(tempstring == "flag"){
                break;
            }
            index = index + chunk[beginning].length()+1;    //used for traversing through file for creating each chunk
            chunk.clear();
            tempstring.clear();
        }
        i++;  //the file number that is being analyzed
    }

    return 0;
}

