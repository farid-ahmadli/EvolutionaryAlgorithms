/* 
 * File:   Individual.cpp
 * Author: CHS
 * 
 * Created on 11. Oktober 2011, 13:31
 */

#include "Individual.h"

/**
 * Default constructor.
 */
Individual::Individual() {
    numBGenoms = 0;
    numIGenoms = 0;
    numConsPair = 0;
    fitness = 0;
    consistency = 0;
    heapPos = -1;
    bGenom = NULL;
    iGenom = NULL;
    consistencies = NULL;
}

/**
 * Default destrcutor
 */
Individual::~Individual() {
//    if (iGenom != NULL) delete[] iGenom;
//    if (bGenom != NULL) delete[] bGenom;
//    if (consistencies != NULL) delete[] consistencies;
}


/**
 * This method initializes the individual with data from data unit (global variables)
 * @param hp Initial position in the population
 * @param du Data unit with global variables
 */
void Individual::Init(DataUnit& du) {
    this->du = du;
    heapPos = -1;
    numIGenoms = du.GetNumKF();
    numBGenoms = du.GetNumProj();
    numConsPair = du.GetNumCsvPairs();
    iGenom = new int[numIGenoms];
    bGenom = new bool[numBGenoms];
    consistencies = new int[numConsPair];
    bOnesOverThreshold = false;
    bTwosOverThreshold = false;
    hasFixProj = false;
    fitness = du.GetMinMax();
    
    for (int i=0; i<numIGenoms; i++) 
        iGenom[i] = 1;
    
    for (int i=0; i<numBGenoms; i++) 
        bGenom[i] = false;
    
    logOnes = false;
}

/**
 * This method assigns values from some Individual to the current one
 * @param orig Individual with source values
 */
void Individual::Assign(const Individual& orig) {
    du = orig.du;
    consistency = orig.consistency;    
    numBGenoms = orig.numBGenoms;
    numIGenoms = orig.numIGenoms;
    numConsPair = orig.numConsPair;
    fitness = orig.fitness;
    heapPos = orig.heapPos;
    bOnesOverThreshold = orig.bOnesOverThreshold;
    bTwosOverThreshold = orig.bTwosOverThreshold;
    numOnes = orig.numOnes;
    numTwos = orig.numTwos;
    hasFixProj = orig.hasFixProj;
    logOnes = orig.logOnes;
    if (orig.bGenom != NULL && numBGenoms > 0) {
        if (bGenom == NULL)
            bGenom = new bool[numBGenoms];
        copy(orig.bGenom, orig.bGenom+numBGenoms, bGenom);
    }
    if (orig.iGenom != NULL && numIGenoms > 0) {
        if (iGenom == NULL)
            iGenom = new int[numIGenoms];
        copy(orig.iGenom, orig.iGenom+numIGenoms, iGenom);
    }
    if (orig.consistencies != NULL && numConsPair > 0) {
        if (consistencies == NULL)
            consistencies = new int[numConsPair];
        copy(orig.consistencies, orig.consistencies+numConsPair, consistencies);
    }
}

/**
 * Fills the genoms of the individual with random values
 */
void Individual::RandFill() {
    for (int i=0; i<numIGenoms; i++)
        iGenom[i] = rand() % (du.GetNumProjKF(i)) + 1;
    
    CalcFitness();
}

/**
 * This method recombines given individuals and assigns it to the current individual.
 * Single point crossover method is used, as a splitting point an integer value is given as input parameter.
 * @param a first individual
 * @param b second individual
 * @param split point of splitting for recombination
 */
void Individual::Recombine(const Individual& a, const Individual& b, const int& split) {
                
    for (int i=0; i<split; i++)
        iGenom[i] = a.iGenom[i];
    
    for (int i=split; i<numIGenoms; i++)
        iGenom[i] = b.iGenom[i];
    
    CalcFitness();
}

/**
 * 
 */
void Individual::CalcConsistency() {    
   
    numOnes = 0;
    numTwos = 0;
    
    int pos = 0;
    consistency = 0;
    
    for (int i=0; i<numIGenoms; i++) {
        
        // TODO weighting function
        int w1 = 1;
                
        int r = du.GetSumProjKF(i) + iGenom[i] - 1;
        for (int j=i+1; j<numIGenoms; j++) {
            // TODO weighting function
            int w2 = 1;
            
            int c = du.GetSumProjKF(j) + iGenom[j] - 1;
            consistencies[pos] = du.GetCsValue(r, c);
            
            if (du.IsLinkIMxCMx()) {
                // Vernetzung ...
            }
            else {
                consistency += consistencies[pos] * w1 * w2;
            }
            
            if (consistencies[pos] == 1) numOnes++;
            if (consistencies[pos] == 2) numTwos++;
            
            pos++;
        }
    }
    
    bOnesOverThreshold = numOnes >= du.GetThrTotIncons();
    bTwosOverThreshold = numTwos >= du.GetThrPartIncons();

}

/**
 * This function calculates the fitness value of the individual
 * @return Fitness value of the individual
 */
double Individual::CalcFitness() {
    CalcConsistency();
    
    if (du.GetMinMax() == 1) {
        fitness = consistency;
        
        // calculating fitness after penalty if ones are not allowed
        // and number of ones is over the allowed limit
        if (bOnesOverThreshold && !du.IsAllowOnes())
            fitness *= du.GetPenTotIncons();
        
        // calculating fitness after penalty if twos are not allowed
        if (bTwosOverThreshold)
            fitness *= du.GetPenPartIncons();
        
        // calculate fitness if some of fixed (to be) projections are absent
        if (du.GetNumFixProj() > 0) {
            // TODO add fixed projections algo
        }
        
        // adding some random chance to the fitness
        if (du.IsChance()) {
            fitness *= (1 + 0.2*rand());
        }
    }
    else {
        // TODO min
    }
    
    return fitness;
}

/**
 * 
 */
void Individual::GaussMutation() {
    int stepSize = RandNormDist(0, du.GetSigma());
    if (stepSize > numIGenoms) stepSize = numIGenoms;
    
    int u[stepSize];
    for (int i=0; i<stepSize; i++)
        u[i] = i;
    
    while (stepSize > 0) {
        int p = rand() % stepSize;
        
        iGenom[u[p]] = rand() % (du.GetNumProjKF(u[p])) + 1;
        
        stepSize--;
        u[p] = u[stepSize];
    }
    
    CalcFitness();
}

/**
 * This function calculates some hash value using genom data and fitness by combining them into an integer value
 * @return Integer value with some hash value from 0 to MAX_IND-1
 */
int Individual::HashVal() {
    int val = 0;
    for (int i=0; i<numIGenoms; i++)
        val = (val*MAX_PROJ + iGenom[i]) % MAX_IND;
    
    return ((int)(val*fitness)) % MAX_IND;
}
