#include "MemoryManager.h"
#include "PageTable.h"
#include "InputHandler.h"

#include<cstdlib>

#include<iostream>
#include<fstream>
#include<sstream>
#include<cstring>

#include<queue>

using namespace std;

char* getFileNameWithoutExtension(char* name);
string getReplacementPolicyString(int policy);

int main(int argc, char** argv) {
    //saves stdout's buffer so we can restore it later
    //streambuf* coutbuf = cout.rdbuf();

    InputHandler ih;

    for(int i = 1; i < argc; i += 3) {
        //gets the type of replacement policy to use from the parameters
        int policy = atoi(argv[i]);
        unsigned int maxPagesInMemory = atoi(argv[i + 1]);
        char* path = argv[i + 2];

        //processes the input file and builds a queue of page accesses
        queue<PageTableEntry*>* pageTableEntries = ih.parseInput(path);
        if(pageTableEntries == NULL) {
            cout << "There was an error parsing the input for " << path << "!" << endl;
            continue;
        }

        //ostringstream oss;
        //strips the extension off the filename and builds the output file name
        //oss << getFileNameWithoutExtension(path) << "." << getReplacementPolicyString(policy) << ".txt";
        //ofstream out(oss.str().c_str());
        //sets cout's buffer to the output file
        //cout.rdbuf(out.rdbuf());

        //creates and runs the memeory manager on the queue of page accesses
        //based on the replacement policy
        MemoryManager* mm = new MemoryManager((ReplacementPolicy)policy, maxPagesInMemory, pageTableEntries);
        mm->doManage();
        delete mm;

        delete pageTableEntries;

        //gives cout its buffer back so we can print any errors
        //cout.rdbuf(coutbuf);
    }

    //gives cout its buffer back
    //cout.rdbuf(coutbuf);

    return 0;
}

char* getFileNameWithoutExtension(char* name) {
    int dotPos = -1;
    for(int i = 0; name[i] != '\0'; i++) {
        if(name[i] == '.') {
            //if another dot is found
            //store its index
            dotPos = i;
        }
    }

    if(dotPos < 0) {
        return name;
    }
    else {
        //allocates a new array for the stripped filename
        char* newName = new char[dotPos + 1];
        strncpy(newName, name, dotPos);
        newName[dotPos] = '\0';
        return newName;
    }
}

string getReplacementPolicyString(int policy) {
    switch(policy) {
        case 0:
            return "fifo";
        case 1:
            return "second";
        case 2:
            return "lru";
        default:
            return "error";
    }
}

