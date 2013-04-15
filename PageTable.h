#ifndef PAGETABLE_H
#define PAGETABLE_H

#include<iostream>
#include<list>
#include<map>

using namespace std;

class PageTableEntry {
   public:
       PageTableEntry(int page) : page(page), r(false), age(0) {}
       int page;
       bool r;
       unsigned long age;
};

class PageTable {
    public:
        typedef list<PageTableEntry*> memory_list;
        PageTable() : pages(new memory_list()), pageSearch(new searchTable()), counter(0) {}

        //returns an iterator to the beginning of the pages memory_list
        memory_list::iterator begin() {
            return pages->begin();
        }

        //returns an iterator to the end of the pages memory_list
        memory_list::iterator end() {
            return pages->end();
        }

        //returns the size of the pages memory_list
        size_t size() {
            return pages->size();
        }

        //increments the age that will be assigned to PageTableEntrys on access
        void updateCounter() {
            counter++;
        }

        //checks if a given page is in memory
        //if it is it will set its R bit to true
        //and assign the passed in page parameter to it
        bool contains(PageTableEntry** page) {
            searchTable::iterator it;
            it = pageSearch->find((*page)->page);

            if(it == pageSearch->end()) {
                return false;
            }
            else {
                //since it already exists in memory
                //we don't need a new pointer so we
                //delete the old one and assign the
                //pointer in memory to the page parameter
                delete (*page);
                *page = it->second;
                //the page's age is set to the value of counter
                (*page)->age = counter;
                //since we accessed it we set R to true
                (*page)->r = true;
                return true;
            }
        }

        //inserts the page into the pages memory_list and pageSearch
        //since it is accessed we set its R to true
        void insert(PageTableEntry* page) {
            page->r = true;
            //the page's age is set to the value of counter
            page->age = counter;
            pageSearch->insert( searchPair(page->page, page) );
            pages->push_back(page);
        }

        PageTableEntry* replace(PageTableEntry* replaceThis, PageTableEntry* withThis) {
            //replaces the R and age values of replaceThis with withThis
            replaceThis->r = true;
            //the page's age is set to the value of counter
            replaceThis->age = counter;

            //erases the replaced page number from pageSearch
            pageSearch->erase(replaceThis->page);
            //inserts replaceThis (acting as withThis) into pageSearch using withThis's
            //page number as a key
            pageSearch->insert( searchPair(withThis->page, replaceThis) );

            //changes the page value of replaceThis to withThis's page value
            //now withThis's page value is occupying the slot that replaceThis's
            //did in memory
            replaceThis->page = withThis->page;

            //return replaceThis (which has the new values in it)
            return replaceThis;
        }

        //iterates the pages memory_list and prints each page
        void print() {
            memory_list::iterator it;
            for(it = pages->begin(); it != pages->end(); it++) {
                cout << (*it)->page << " ";
            }
            cout << endl;
        }

        ~PageTable() {
            memory_list::iterator it;
            for(it = pages->begin(); it != pages->end(); it++) {
                delete (*it);
            }
            delete pages;
            delete pageSearch;
        }
    private:
        typedef map<int, PageTableEntry*> searchTable;
        typedef pair<int, PageTableEntry*> searchPair;
        //holds all the pages that are in memory for iteration
        memory_list* pages;
        //holds all the pages that are in memory for search
        searchTable* pageSearch;
        //represents age
        unsigned long counter;
};

#endif // PAGETABLE_H
