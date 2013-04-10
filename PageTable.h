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
        typedef list<PageTableEntry*> q;
        PageTable() : pages(new q()), pageSearch(new searchTable()), counter(0) {}

        q::iterator begin() {
            return pages->begin();
        }

        q::iterator end() {
            return pages->end();
        }

        size_t size() {
            return pages->size();
        }

        void updateCounter() {
            counter++;
        }

        bool contains(PageTableEntry** page) {
            searchTable::iterator it;
            it = pageSearch->find((*page)->page);

            if(it == pageSearch->end()) {
                return false;
            }
            else {
                delete (*page);
                *page = it->second;
                (*page)->age = counter;
                (*page)->r = true;
                return true;
            }
        }

        void insert(PageTableEntry* page) {
            page->r = true;
            page->age = counter;
            pageSearch->insert( searchPair(page->page, page) );
            pages->push_back(page);
        }

        PageTableEntry* replace(PageTableEntry* replaceThis, PageTableEntry* withThis) {
            replaceThis->r = true;
            replaceThis->age = counter;

            pageSearch->erase(replaceThis->page);
            pageSearch->insert( searchPair(withThis->page, replaceThis) );

            replaceThis->page = withThis->page;

            return replaceThis;
        }

        void print() {
            q::iterator it;
            for(it = pages->begin(); it != pages->end(); it++) {
                cout << (*it)->page << " ";
            }
            cout << endl;
        }

        ~PageTable() {
            q::iterator it;
            for(it = pages->begin(); it != pages->end(); it++) {
                delete (*it);
            }
            delete pages;
            delete pageSearch;
        }
    private:
        typedef map<int, PageTableEntry*> searchTable;
        typedef pair<int, PageTableEntry*> searchPair;
        q* pages;
        searchTable* pageSearch;
        unsigned long counter;
};

#endif // PAGETABLE_H
