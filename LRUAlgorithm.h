#ifndef LRUALGORITHM_H
#define LRUALGORITHM_H

#include "MemoryManager.h"

class MemoryManager::LRUAlgorithm : public MemoryManager::ReplacementAlgorithm {
    public:
        LRUAlgorithm(MemoryManager* mm) : mm(mm) {}
        void accessPage(PageTableEntry* page, PageTable* pageTable);
    private:
        MemoryManager* mm;
};

#endif // LRUALGORITHM_H


