replace_page : main.o MemoryManager.o InputHandler.o FCFSAlgorithm.o SCAlgorithm.o LRUAlgorithm.o
	g++ -o replace_page  main.o MemoryManager.o InputHandler.o FCFSAlgorithm.o SCAlgorithm.o LRUAlgorithm.o

main.o : main.cpp MemoryManager.h PageTable.h InputHandler.h
	g++ -c main.cpp
MemoryManager.o : MemoryManager.cpp MemoryManager.h
	g++ -c MemoryManager.cpp
InputHandler.o : InputHandler.cpp PageTable.h
	g++ -c InputHandler.cpp
FCFSAlgorithm.o : FCFSAlgorithm.cpp FCFSAlgorithm.h MemoryManager.h
	g++ -c FCFSAlgorithm.cpp
SCAlgorithm.o : SCAlgorithm.cpp SCAlgorithm.h MemoryManager.h
	g++ -c SCAlgorithm.cpp
LRUAlgorithm.o : LRUAlgorithm.cpp LRUAlgorithm.h MemoryManager.h
	g++ -c LRUAlgorithm.cpp
clean : 
	rm replace_page  main.o MemoryManager.o InputHandler.o FCFSAlgorithm.o SCAlgorithm.o LRUAlgorithm.o
