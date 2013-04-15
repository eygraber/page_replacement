#include "SCAlgorithm.h"

void MemoryManager::SCAlgorithm::accessPage(PageTableEntry* page, PageTable* pageTable) {
    //if the page is not in memory (contains sets R to true if it is present)
    if(!pageTable->contains(&page)) {
        //we have a page fault
        mm->incrementPageFaultCount();
        //if there is no room left in memory and we need to replace
        if(pageTable->size() >= mm->maxPagesInMemory) {
            //get the page that needs to be replaced
            PageTableEntry* pageToReplace = getPageToReplace();
            //we can pop the head off the queue
            q->pop_front();
            //replace uses the pointers that are already in the PageTable (pageToReplace)
            //and copies the incoming page's information to it
            //this makes managing the data structures easier
            //it then returns the pointer from the PageTable and we send it to tail
            q->push_back(pageTable->replace(pageToReplace, page));
            //since the pointer that is in the PageTable is used we can delete the
            //incoming page
            delete page;
        }
        //there is still room in memory
        else {
            pageTable->insert(page);
            q->push_back(page);
        }
    }
}

PageTableEntry* MemoryManager::SCAlgorithm::getPageToReplace() {
    list<PageTableEntry*>::iterator it = q->begin();
    //iterate through the queue checking to see when the head's R bit is false
    //when it is, return a pointer to the PageTableEntry stored there
    while((*it)->r) {
        //if the R bit is true set it to false
        (*it)->r = false;
        //moves this entry from the head to the tail
        q->splice(q->end(), *q, it);
        //sets our iterator back to the head
        it = q->begin();
    }
    return (*it);
}
