#include "LRUAlgorithm.h"

void MemoryManager::LRUAlgorithm::accessPage(PageTableEntry* page, PageTable* pageTable) {
    if(!pageTable->contains(&page)) {
        mm->incrementPageFaultCount();
        if(pageTable->size() >= mm->maxPagesInMemory) {
            PageTable::q::iterator it = pageTable->begin();
            PageTableEntry* pageToReplace = (*it);
            for(++it; it != pageTable->end(); it++) {
                if((*it)->age < pageToReplace->age) {
                    pageToReplace = *it;
                }
            }
            pageTable->replace(pageToReplace, page);
            delete page;
        }
        else {
            pageTable->insert(page);
        }
    }
}
