# concurrent-Aho-Corasick-string-match

Concurrent implementation of Aho-Corasick algorithm in C using pthread. This system uses a finite state machine (Trie) to find all occurrences of a list of keywords in a given string. The Aho-Corasick algorithm is especially effective when working with a large amount of keywords. No matter the amount of keywords, we only need to traverse the search text once. This results in an O(n) algorithm.


Usage: 

* Build
```bash
gcc main.c fifo.c search.c stateMachine.c inputOutput.c -o match -Wall
```

* Run
```bash
./match text.in keys.in N_threads
```

* Outputs:

    *stdout*: key_name	times_found \
    *sdterr*: setup_time	search_time	cleanup_time \
    *results.out*: key_name		times_found		 positions_found	


* Original Aho Corasick paper:

Alfred V. Aho and Margaret J. Corasick. 1975. Efficient string matching: an aid to bibliographic search. Commun. ACM 18, 6 (June 1975), 333-340. DOI=http://dx.doi.org/10.1145/360825.360855

