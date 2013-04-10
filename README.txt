Code can be compiled by running make.

Code is run by calling ./replace_page replacement_policy max_pages_in_memory inputfile ... (eg ./replace_page
0 3 test.txt 1 5 test.txt 2 4 test.txt

Output will be sent to inputfile.replacement_policy.txt (eg test.fcfs.txt test.second.txt
test.lru.txt)