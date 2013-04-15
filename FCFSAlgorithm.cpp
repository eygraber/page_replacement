#include "FCFSAlgorithm.h"

void MemoryManager::FCFSAlgorithm::accessPage(PageTableEntry* page, PageTable* pageTable) {
    //if the page is not in memory (contains sets R to true if it is present)
    if(!pageTable->contains(&page)) {
        //we have a page fault
        mm->incrementPageFaultCount();
        //if there is no room left in memory and we need to replace
        if(pageTable->size() >= mm->maxPagesInMemory) {
            //in FIFO we simply replace the head
            PageTableEntry* pageToReplace = q->front();
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

