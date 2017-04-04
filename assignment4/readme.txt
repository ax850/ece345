README:

Code is written in C and contained in tsp.c
Binary object file is included as tsp
To recompile, in LINUX terminal: gcc -o tsp tsp.c

Executable can be called from command line as tsp distances.txt or ./tsp distances.txt
Graphs should be in same folder as executable.
10 graphs are included, number of cities is given in the file names. Because of the nature of the Held-Karp algortihm, running more than ~25-30 cities uses too much memory for my implementation and runs into seg-faults. Therefore, the number of cities I used never exceeded 25. For testing, the program should not be given city sizes greater than 25.

genall.c is the code included for generating the distances with different number of cities. Included for those curious.

Andy Xu, Jonathan Chan, Jerry Wang
