#include "LRUAlgorithm.h"

void MemoryManager::LRUAlgorithm::accessPage(PageTableEntry* page, PageTable* pageTable) {
    //if the page is not in memory (contains sets R to true if it is present)
    if(!pageTable->contains(&page)) {
        //we have a page fault
        mm->incrementPageFaultCount();
        //if there is no room left in memory and we need to replace
        if(pageTable->size() >= mm->maxPagesInMemory) {
            //we use PageTable's internal list to iterate through the PAgeTableEntrys
            //since order doesn't matter here
            PageTable::memory_list::iterator it = pageTable->begin();
            PageTableEntry* pageToReplace = (*it);
            for(++it; it != pageTable->end(); it++) {
                //selects the PageTableEntry with the lowest value for age
                if((*it)->age < pageToReplace->age) {
                    pageToReplace = *it;
                }
            }
            //replace uses the pointers that are already in the PageTable (pageToReplace)
            //and copies the incoming page's information to it
            //this makes managing the data structures easier
            //it then returns the pointer from the PageTable and we send it to tail
            pageTable->replace(pageToReplace, page);
            //since the pointer that is in the PageTable is used we can delete the
            //incoming page
            delete page;
        }
        //there is still room in memory
        else {
            pageTable->insert(page);
        }
    }
}
