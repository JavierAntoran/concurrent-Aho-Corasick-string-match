# concurrent-Aho-Corasick-string-match

Concurrent implementation of Aho-Corasick algorithm in C using pthread. This system uses a finite state machine (Trie) to find all occurrences of a list of keywords in a given string. The Aho-Corasick algorihm is specially efective when working with a large amount of keywords. No matter the amount of keywords, we only need to traverse the search text once. This results in an O(n) algorithm.


Usage: 

$gcc main.c fifo.c search.c stateMachine.c inputOutput.c -o match -Wall

$./match text.in keys.in N_threads


Outputs:

stdout: key_name	times_found

sdterr: setup_time	search_time	cleanup_time

results.out: key_name		times_found		 positions_found	