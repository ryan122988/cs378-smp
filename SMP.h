
// --------
// includes
// --------

#include <cassert> // assert
#include <iostream> // endl, istream, ostreamin
#include <vector>
using namespace std;




// ------------
// smp_read
// ------------

/**
* reads two ints into i and j
* @param r a std::istream
* @param i an int by reference
* @param j an int by reference
* @return true if that succeeds, false otherwise
*/
bool collatz_read (std::istream& r, int& i, int& j) {
    r >> i;
    if (!r)
        return false;
    r >> j;
    assert(i > 0);
    assert(j > 0);
    return true;}



// -------------
// collatz_print
// -------------

/**
* prints the values of i, j, and v
* @param w a std::ostream
* @param i the beginning of the range, inclusive
* @param j the end of the range, inclusive
* @param v the max cycle length
*/
void smp_print (std::ostream& w, int i, int j, int v) {
    assert(i > 0);
    assert(j > 0);
    assert(v > 0);
    w << i << " " << j << " " << v << std::endl;}


// --------------
// readTest 
// --------------
vector < vector < int > > readTest (std::istream& r, int numMarriages){
    int marriages = numMarriages * 2;
    vector < vector < int > > output(marriages);
    vector < int > line (numMarriages);
    int count = 0;
    int temp = 0;
    r >> temp;
    while (marriages > 0){
        for(int i = 0; i < numMarriages; ++i){
            r >> temp;
            line[i] = temp;
        }
        if ( marriages > 1)
            r >> temp;
        output[count] = line;
        ++count;
        --marriages;
    }
    return output;
}

// -------------
// generate_woman_vector
// -------------
vector < int > generate_woman_vector(vector < int > line, int numMarriages){
    int size = numMarriages + 1;
    vector < int > out(size);
    out[0] = -1; 
    int val = -1; 
    int num = -1;
    for(int i = 0; i < numMarriages; ++i){
        val = i+1;
        num = line[i];
        out[num] = val;
    }
    return out;
}

// -------------
// update
// -------------
int update(vector < vector < int > > women, vector < vector < int > > men, int man, int nextChoice, int numUnmatchedMen, int numMarriages){
    int out = numUnmatchedMen;
    int menLocation = man -1;
    int womanLocation = nextChoice -1;
    int mansRank = women[womanLocation][man];
    int currentPartner = women[womanLocation][0];
    if(currentPartner == -1){
        women[womanLocation][0] = man;
        men[menLocation][0] = nextChoice;
        --out;
        return out;
    }
    int currentPartnerRank = women[womanLocation][currentPartner];
    int currentPartnerLocation = currentPartner -1;
    int lastSpotInMen = numMarriages + 1;
    int val = -1;
    if(mansRank > currentPartnerRank){
        women[womanLocation][0] = man;
        men[menLocation][0] = nextChoice;
        men[currentPartnerLocation][0] = -1;
        val = men[currentPartnerLocation][lastSpotInMen];
        ++val;
        men[currentPartnerLocation][lastSpotInMen] = val;
    }
    else{
        val = men[menLocation][lastSpotInMen];
        ++val;
        men[menLocation][lastSpotInMen] = val;
    }
    return out;
}

// -------------
// generate_solution
// -------------
vector < vector < int > > generate_solution(std::ostream& w, vector < vector < int > > women, vector < vector < int > > men, int numMarriages){
    int numUnmatchedMen = numMarriages;
    int nextChoice = -1;
    int man = -1;
    int mansRank = -1;
    int womanLocation = -1;
    int currentPartner = -1;
    int currentPartnerRank = -1;
    int currentPartnerLocation = -1;
    int lastSpotInMen = numMarriages +1;
    int val = -1;
    int nextChoiceLocation = -1;
    vector < vector < int > > output(numMarriages);
    for(int i = 0; i < numMarriages; ++i){
        for(int j = 0; j < numMarriages; ++j){
            if(men[j][0] == -1){
                nextChoiceLocation = men[j][numMarriages + 1];
                nextChoice = men[j][nextChoiceLocation];
                man = j+1;
                womanLocation = nextChoice -1;
                mansRank = women[womanLocation][man];
                currentPartner = women[womanLocation][0];
                if(currentPartner == -1){
                    women[womanLocation][0] = man;
                    men[j][0] = nextChoice;
                    --numUnmatchedMen;
                    continue;
                }
                currentPartnerRank = women[womanLocation][currentPartner];
                currentPartnerLocation = currentPartner -1;
                if(mansRank < currentPartnerRank){
                    women[womanLocation][0] = man;
                    men[j][0] = nextChoice;
                    men[currentPartnerLocation][0] = -1;
                    val = men[currentPartnerLocation][lastSpotInMen];
                    ++val;
                    men[currentPartnerLocation][lastSpotInMen] = val;
                }
                else{
                    val = men[j][lastSpotInMen];
                    ++val;
                    men[j][lastSpotInMen] = val;
                }
            }
        }
        if(numUnmatchedMen == 0){
            break;
        }
    }
    vector < int > data (2); 
    for(int k = 0; k < numMarriages; ++k){
        val = k+1;
        data[0] = val;
        data[1] = men[k][0];
        output[k] = data;
    }
    return output;
}

// -------------
// compute
// -------------

vector < vector < int > > compute (std::ostream& w,vector < vector < int > > test, int numMarriages){
    vector < vector < int > > output(numMarriages);
    vector < int > woman(numMarriages+1);
    vector < vector < int > > women(numMarriages);
    vector < int > man(numMarriages+2);
    vector < vector < int > > men(numMarriages);
    for(int i = 0; i < numMarriages; ++i){
	woman = generate_woman_vector( test[i], numMarriages);
        women[i] = woman;
    }
    int maxLimit = numMarriages * 2;
    man[0] = -1;
    man[numMarriages+1] = 1;
    int count = 0;
    for(int j = numMarriages; j < maxLimit; ++j){
        int val = -1;
        for(int k = 0; k < numMarriages; ++k){
		val = k+1;
                man[val] = test[j][k];
        }
        men[count] = man;
        ++count;
    }
    output = generate_solution(w,women, men, numMarriages);
    for(int z = 0; z < numMarriages; z++){
        w<<output[z][0]<<" "<<output[z][1]<<endl;
    }
    return output;
}

// -------------
// output
// -------------
void output(std::ostream& w, vector < vector < vector < int > > > outputData, vector < int > numMarriagesVector,int numTests){
    int count1 = 0;
    int count2 = 0;
    int size = -1;
    while (count1 < numTests){
        size = numMarriagesVector[count1];
        while (count2 < size){
            w << outputData[count1][count2][0]<<" "<<outputData[count1][count2][1]<<endl;
            ++count2;
        }
        count2 = 0;
        ++count1;
    }
}


// -------------
// smp_solve
// -------------

/**
* read, eval, print loop
* @param r a std::istream
* @param w a std::ostream
*/
void smp_solve (std::istream& r, std::ostream& w) {
    int tests = 0;
    int count = 0;
    r >> tests;
    int numMarriages = 0;
    int cyclesLeft = tests;
    vector< vector < vector < int > > > testsVector (tests);
    vector < int > numMarriagesVector (tests);
    while (cyclesLeft > 0){
        r >> numMarriages;
        vector < vector < int > > thisTest = readTest(r, numMarriages);
        numMarriagesVector[count] = numMarriages;
        testsVector[count] = thisTest;
        --cyclesLeft;
        ++count;
    }
    count = 0;
    vector < vector < vector < int > > > outputData(tests);
    while (count < tests){
        int marriages = numMarriagesVector[count];
        outputData[count] = compute(w, testsVector[count], marriages);
	++count;
    }
    //output(w, outputData, numMarriagesVector, tests);
    /*count = 0;
    int size = 0;
    int count2 = 0;
    while (count < tests){
        size = numMarriagesVector[count];
        while(count2 < size){
	    w << outputData[count][count2][0] << " " << outputData[count][count2][1]<< endl;
            ++count2;
        }
        ++count;
    }*/
    
}

