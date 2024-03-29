

/*
To run the program:
% g++ -ansi -pedantic -Wall RunSMP.c++ -o RunSMP.app
% valgrind RunSMP.app < RunSMP.in >& RunSMP.out

To configure Doxygen:
% doxygen -g
That creates the file "Doxyfile".
Make the following edits:
EXTRACT_ALL = YES
EXTRACT_PRIVATE = YES
EXTRACT_STATIC = YES
GENERATE_LATEX = NO

To document the program:
% doxygen Doxyfile
*/

// -------
// defines
// -------

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

// --------
// includes
// --------

#include <iostream> // cin, cout, ios_base

#include "SMP.h"

// ----
// main
// ----
using namespace std;

int main () {
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    smp_solve(cin, cout);
    return 0;}
