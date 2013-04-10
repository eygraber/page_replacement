#ifndef SCALGORITHM_H
#define SCALGORITHM_H

#include "MemoryManager.h"

class MemoryManager::SCAlgorithm : public MemoryManager::ReplacementAlgorithm {
    public:
        SCAlgorithm(MemoryManager* mm) : mm(mm), q(new list<PageTableEntry*>()) {}
        void accessPage(PageTableEntry* page, PageTable* pageTable);
    private:
        MemoryManager* mm;
        list<PageTableEntry*>* q;
        PageTableEntry* getPageToReplace();
};

#endif // SCALGORITHM_H


