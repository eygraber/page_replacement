#ifndef FCFSALGORITHM_H
#define FCFSALGORITHM_H

#include "MemoryManager.h"
#include<list>

class MemoryManager::FCFSAlgorithm : public MemoryManager::ReplacementAlgorithm {
    public:
        FCFSAlgorithm(MemoryManager* mm) : mm(mm), q(new list<PageTableEntry*>()) {}
        void accessPage(PageTableEntry* page, PageTable* pageTable);

        ~FCFSAlgorithm() {}
    private:
        MemoryManager* mm;
        //structure used to manage this replacement policy
        list<PageTableEntry*>* q;
};

#endif // FCFSALGORITHM_H

