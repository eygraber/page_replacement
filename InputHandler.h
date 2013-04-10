#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "PageTable.h"

#include<fstream>
#include<queue>

using namespace std;

class InputHandler {
    private:
        int parseData(ifstream* s);
    public:
        queue<PageTableEntry*>* parseInput(char* path);
};

#endif //INPUTHANDLER_H

