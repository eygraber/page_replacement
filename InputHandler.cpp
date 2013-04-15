#include "InputHandler.h"
#include<iostream>
#include<cstdlib>

queue<PageTableEntry*>* InputHandler::parseInput(char* path) {
    ifstream inputFile(path);

    //if the input file does not exist
    if(!inputFile || inputFile.fail()) {
        return NULL;
    }

    queue<PageTableEntry*>* pageTableEntries = new queue<PageTableEntry*>();

    //create a queue of PageTableEntrys
    while(!inputFile.eof() && inputFile.good()) {
        int page = parseData(&inputFile);
        if(page < 0) {
            return NULL;
        }
        pageTableEntries->push(new PageTableEntry(page));
    }

    inputFile.close();

    return pageTableEntries;
}

//parses out data separated by whitespace or newlines
int InputHandler::parseData(ifstream* s) {
    char c;
    string str = "";
    do {
        if(!s->good()) {
            return -1;
        }
        c = s->get();
    } while(c == ' ' || c == '\n');

    while(c != ' ' && c != '\n') {
        str += c;

        if(!s->good()){
            break;
        }

        c = s->get();
    }

    while(c == ' ' || c == '\n') {
        c = s->get();

        if(!s->good()) {
            return atoi(str.c_str());
        }
    }

    s->unget();

    return atoi(str.c_str());
}

