#include "SCAlgorithm.h"

void MemoryManager::SCAlgorithm::accessPage(PageTableEntry* page, PageTable* pageTable) {
    if(pageTable->contains(&page)) {
        /*if(page->page != q->back()->page) {
            list<PageTableEntry*>::iterator it;
            for(it = q->begin(); it != q->end(); it++) {
                if(page->page == (*it)->page) {
                    PageTableEntry* temp = (*it);
                    q->erase(it);
                    q->push_back(temp);
                    break;
                }
            }
        }*/
    }
    else {
        mm->incrementPageFaultCount();
        if(pageTable->size() >= mm->maxPagesInMemory) {
            PageTableEntry* pageToReplace = getPageToReplace();
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

PageTableEntry* MemoryManager::SCAlgorithm::getPageToReplace() {
    list<PageTableEntry*>::iterator it = q->begin();
    while((*it)->r) {
        (*it)->r = false;
        q->splice(q->end(), *q, it);
        it = q->begin();
    }
    return (*it);
}
