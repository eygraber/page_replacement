#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include "PageTable.h"

#include<iostream>
#include<queue>
#include<map>

using namespace std;

//represents the different policies that can be used
enum ReplacementPolicy { FCFS = 0, SC = 1, LRU = 2 };

class MemoryManager {
    private:
        //abstract algorithm class
        class ReplacementAlgorithm {
            //gives MemoryManager access to ReplacementAlgorithm's private members
            friend class MemoryManager;

            //runs the algorithm
            virtual void accessPage(PageTableEntry* page, PageTable* pageTable) = 0;

            virtual ~ReplacementAlgorithm() {}
        };

        //forward declarations of algorithm implementations
        class FCFSAlgorithm;
        class SCAlgorithm;
        class LRUAlgorithm;

        //making these friends classes gives access to ReplacementAlgorithm
        friend class FCFSAlgorithm;
        friend class SCAlgorithm;
        friend class LRUAlgorithm;

        //pointer to an abstract ReplacementAlgorithm
        ReplacementAlgorithm* alg;
        //returns a pointer to a concrete implementation of a ReplacementAlgorithm
        ReplacementAlgorithm* getReplacementAlgorithm(ReplacementPolicy policy);

        unsigned int maxPagesInMemory;

        //this queue holds the PageTableEntrys parsed from the input
        queue<PageTableEntry*>* pageTableEntries;
        //the page table that will be used to manage the pages in memory
        PageTable* pageTable;

        double pageAccessCount;
        double pageFaultCount;
        void incrementPageFaultCount() { pageFaultCount++; }
        double getPageFaultPercentage() { return pageFaultCount / pageAccessCount; }
    public:
        MemoryManager(ReplacementPolicy policy, unsigned int maxPagesInMemory, queue<PageTableEntry*>* pageTableEntries) :
            alg(getReplacementAlgorithm(policy)), maxPagesInMemory(maxPagesInMemory), pageTableEntries(pageTableEntries),
            pageTable(new PageTable()), pageAccessCount(pageTableEntries->size()), pageFaultCount(0) {}

        void doManage() {
            //loop through all of the PageTableEntrys parsed from input
            while(!pageTableEntries->empty()) {
                //runs the policy for accessing a page
                //if a page needs to be replaced it will happen here
                alg->accessPage(pageTableEntries->front(), pageTable);
                //prints the PageTable in memory-order
                pageTable->print();
                //updates the age of the pages
                pageTable->updateCounter();
                //remove this page from the queue of PageTableEntrys parsed from input
                pageTableEntries->pop();
            }

            cout.precision(2);
            cout << "Percentage of Page faults = " << getPageFaultPercentage() << endl;
        }

        ~MemoryManager() {
            delete alg;
            delete pageTable;
        }
};

#endif // MEMORYMANAGER_H
