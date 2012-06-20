
/*
To test the program:
% ls /usr/include/cppunit/
...
HelperMacros.h
...
% locate libcppunit.a
/usr/lib/libcppunit.a
% g++ -ansi -pedantic -lcppunit -ldl -Wall TestSMP.c++ -o TestSMP.app
% valgrind TestSMP.app >& TestSMP.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner
#include <vector>
#include "SMP.h"
#include <stdlib.h>

// -----------
// TestCollatz
// -----------

struct TestSMP : CppUnit::TestFixture {

    // -------
    // readTest
    //
    void test_readTest1 () {
	std::istringstream r("1 1 2\n2 1 2\n1 1 2\n2 1 2\n");
        vector < vector < int > >  result(4);
        result = readTest(r, 2);
        CPPUNIT_ASSERT(result[0][0] == 1);
        CPPUNIT_ASSERT(result[0][1] == 2);
        CPPUNIT_ASSERT(result[1][0] == 1);
        CPPUNIT_ASSERT(result[1][1] == 2);
        CPPUNIT_ASSERT(result[2][0] == 1);
        CPPUNIT_ASSERT(result[2][1] == 2);
        CPPUNIT_ASSERT(result[3][0] == 1);
        CPPUNIT_ASSERT(result[3][1] == 2);
    }

    void test_readTest2 () {
	std::istringstream r("1 2 1\n2 1 2\n1 2 1\n2 1 2\n");
        vector < vector < int > >  result(4);
        result = readTest(r, 2);
        CPPUNIT_ASSERT(result[0][0] == 2);
        CPPUNIT_ASSERT(result[0][1] == 1);
        CPPUNIT_ASSERT(result[1][0] == 1);
        CPPUNIT_ASSERT(result[1][1] == 2);
        CPPUNIT_ASSERT(result[2][0] == 2);
        CPPUNIT_ASSERT(result[2][1] == 1);
        CPPUNIT_ASSERT(result[3][0] == 1);
        CPPUNIT_ASSERT(result[3][1] == 2);
    }

    void test_readTest3 () {
	std::istringstream r("1 1 2\n2 2 1\n1 2 1\n2 1 2\n");
        vector < vector < int > >  result(4);
        result = readTest(r, 2);
        CPPUNIT_ASSERT(result[0][0] == 1);
        CPPUNIT_ASSERT(result[0][1] == 2);
        CPPUNIT_ASSERT(result[1][0] == 2);
        CPPUNIT_ASSERT(result[1][1] == 1);
        CPPUNIT_ASSERT(result[2][0] == 2);
        CPPUNIT_ASSERT(result[2][1] == 1);
        CPPUNIT_ASSERT(result[3][0] == 1);
        CPPUNIT_ASSERT(result[3][1] == 2);
    }

    void test_generate_woman1 () {
	vector < vector < int > > line(4);
        int counter = 0;
        for(int i = 0; i < 4; ++i){
            counter = i+1;
	    vector[i] = counter;
        }
        vector < vector < int > >  result(5);
        result = generate_woman_vector(line, 4);
        CPPUNIT_ASSERT(result[0] == -1);
        CPPUNIT_ASSERT(result[1] == 1);
        CPPUNIT_ASSERT(result[2] == 2);
        CPPUNIT_ASSERT(result[3] == 3);
        CPPUNIT_ASSERT(result[4] == 4);
    }

    void test_generate_woman2 () {
	vector < vector < int > > line(7);
        int counter = 0;
        for(int i = 0; i < 7; ++i){
            counter = i+1;
	    vector[i] = counter;
        }
        vector < vector < int > >  result(8);
        result = generate_woman_vector(line, 7);
        CPPUNIT_ASSERT(result[0] == -1);
        CPPUNIT_ASSERT(result[1] == 1);
        CPPUNIT_ASSERT(result[2] == 2);
        CPPUNIT_ASSERT(result[3] == 3);
        CPPUNIT_ASSERT(result[4] == 4);
        CPPUNIT_ASSERT(result[5] == 5);
        CPPUNIT_ASSERT(result[6] == 6);
        CPPUNIT_ASSERT(result[7] == 7);
    }

    void test_generate_woman3 () {
	vector < vector < int > > line(15);
        int counter = 0;
        for(int i = 0; i < 15; ++i){
            counter = i+1;
	    vector[i] = counter;
        }
        vector < vector < int > >  result(16);
        result = generate_woman_vector(line, 15);
        CPPUNIT_ASSERT(result[0] == -1);
        CPPUNIT_ASSERT(result[1] == 1);
        CPPUNIT_ASSERT(result[2] == 2);
        CPPUNIT_ASSERT(result[3] == 3);
        CPPUNIT_ASSERT(result[4] == 4);
        CPPUNIT_ASSERT(result[5] == 5);
        CPPUNIT_ASSERT(result[6] == 6);
        CPPUNIT_ASSERT(result[7] == 7);
        CPPUNIT_ASSERT(result[8] == 8);
        CPPUNIT_ASSERT(result[9] == 9);
        CPPUNIT_ASSERT(result[10] == 10);
        CPPUNIT_ASSERT(result[11] == 11);
        CPPUNIT_ASSERT(result[12] == 12);
        CPPUNIT_ASSERT(result[13] == 13);
        CPPUNIT_ASSERT(result[14] == 14);
        CPPUNIT_ASSERT(result[15] == 15);
    }



    CPPUNIT_TEST_SUITE(TestSMP);
    CPPUNIT_TEST(test_readTest1);
    CPPUNIT_TEST(test_readTest2);
    CPPUNIT_TEST(test_readTest2);
    CPPUNIT_TEST(test_generate_woman1);
    CPPUNIT_TEST(test_generate_woman2);
    CPPUNIT_TEST(test_generate_woman3);
    CPPUNIT_TEST_SUITE_END();

};


    /*
    // ----
    // read
    // ----

    void test_read () {
        std::istringstream r("1 10\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 1);
        CPPUNIT_ASSERT(j == 10);}

    // ----
    // eval
    // ----

    void test_eval_1 () {
        const int v = collatz_eval(1, 10);
        CPPUNIT_ASSERT(v == 20);}

    void test_eval_2 () {
        const int v = collatz_eval(100, 200);
        CPPUNIT_ASSERT(v == 125);}

    void test_eval_3 () {
        const int v = collatz_eval(201, 210);
        CPPUNIT_ASSERT(v == 89);}

    void test_eval_4 () {
        const int v = collatz_eval(900, 1000);
        CPPUNIT_ASSERT(v == 174);}

    void test_eval_5 () {
        const int v = collatz_eval(348, 932);
        CPPUNIT_ASSERT(v == 179);}

    void test_eval_6 () {
        const int v = collatz_eval(75, 265);
        CPPUNIT_ASSERT(v == 128);}

    void test_eval_7 () {
        const int v = collatz_eval(401, 914);
        CPPUNIT_ASSERT(v == 179);}


//cycle length

    void test_cycle_1 () {
        const int v = collatz_cycle_length(100);
        CPPUNIT_ASSERT(v == 26);}

    void test_cycle_2 () {
        const int v = collatz_cycle_length(200);
        CPPUNIT_ASSERT(v == 27);}

    void test_cycle_3 () {
        const int v = collatz_cycle_length(1000);
        CPPUNIT_ASSERT(v == 112);}
    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}

    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestSMP);
    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_eval_5);s
    CPPUNIT_TEST(test_eval_6);
    CPPUNIT_TEST(test_eval_7);
    CPPUNIT_TEST(test_cycle_1);
    CPPUNIT_TEST(test_cycle_2);
    CPPUNIT_TEST(test_cycle_3);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST_SUITE_END();};*/

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestSMP.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestSMP::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}


