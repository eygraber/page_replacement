#include "FCFSAlgorithm.h"

void MemoryManager::FCFSAlgorithm::accessPage(PageTableEntry* page, PageTable* pageTable) {
    if(!pageTable->contains(&page)) {
        mm->incrementPageFaultCount();
        if(pageTable->size() >= mm->maxPagesInMemory) {
            PageTableEntry* pageToReplace = q->front();
            q->pop_front();
            q->push_back(pageTable->replace(pageToReplace, page));
            delete page;
        }
        else {
            pageTable->insert(page);
            q->push_back(page);
        }
    }
}

