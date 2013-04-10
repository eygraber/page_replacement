#include "MemoryManager.h"
#include "FCFSAlgorithm.h"
#include "SCAlgorithm.h"
#include "LRUAlgorithm.h"

MemoryManager::ReplacementAlgorithm* MemoryManager::getReplacementAlgorithm(ReplacementPolicy policy) {
    switch(policy) {
        case FCFS:
            return new FCFSAlgorithm(this);
        case SC:
            return new SCAlgorithm(this);
        case LRU:
            return new LRUAlgorithm(this);
        default:
            return NULL; //its an error
    }
}
