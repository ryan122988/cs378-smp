
// --------
// includes
// --------

#include <cassert> // assert
#include <iostream> // endl, istream, ostreamin
#include <vector>
using namespace std;



// --------------
// readTest 
// --------------
vector < vector < int > > readTest (std::istream& r, int numMarriages){
    /*
    This method reads in a test case
    */
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
    /*
    This method takes the line representing a womans
    preferences and formats it as per the requirements for
    computing the solution
    */
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
// generate_solution
// -------------
vector < vector < int > > generate_solution(vector < vector < int > > women, vector < vector < int > > men, int numMarriages){
    /*
    This method takes in the women vector, the men vector, and the numMarriages and 
    generates the output
    */
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

void compute (std::ostream& w,vector < vector < int > > test, int numMarriages){
    /*
    This method calls all other methods solve this 
    test case and then writes the output for this testcase
    */
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
    output = generate_solution(women, men, numMarriages);
    for(int z = 0; z < numMarriages; z++){
        w<<output[z][0]<<" "<<output[z][1]<<endl;
    }
   //return output;
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
    while (count < tests){
        int marriages = numMarriagesVector[count];
        compute(w, testsVector[count], marriages);
	++count;
    } 
}

