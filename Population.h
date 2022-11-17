/*
 * File:   Population.h
 * Author: CHS
 *
 * Created on 11. Oktober 2011, 13:23
 */

#ifndef POPULATION_H
#define	POPULATION_H

#include <math.h>
#include <vector>

#include "DataUnit.h"
#include "HeapSort.h"
#include "Individual.h"

using namespace std;

class Population {

protected:
    DataUnit    du;
    HeapSort    hs;

private:

    /*
     * Variables
     */
    int         size;
    int         selSize;
    Individual  **individuals;          // Dies ist die eigentliche Population, welche über die Methoden dieser Klasse verändert wird - Ein Array vom Typ individuum
    int         *selIndividuals;        // In diesem Array werden die Positionen der für die Rekombination selektierten Individuuen der Population gespeichert
    //bool        *strategicParam;      // In diesem Variant-Datenfeld können später die Strategieparameter für jede Population gespeichert werden
    int         numConsPairs;           // In dieser Variablen wird die Anzahl an Konsistenzwertpaaren die jedes Individuum besitzt gespeichert: NumK (0.5 * NumS * (NumS - 1))
    long        numOnes;                //
    float       avgOnes;
    long        numTwos;
    float       avgTwos;
    float       divEntropy;             // !
    bool        bLogOnes;               // log ones
    double      totalFitness;
    double      avgFitness;

public:
    vector<Individual*> table[MAX_IND];

    /*
     * Initialization
     */
    Population();
    virtual ~Population();
    
    void        Init(int size, DataUnit& du);
    void        Assign(const Population& orig);    

    /*
     * Main functions
     */

    void        RandPopulate();
    void        CalcFitness();
    void        AddIndividual(Individual* ind);
    bool        FindIndividual(Individual* ind);
    void        RemoveIndividual(Individual* ind);
    void        RemoveIndividuals();
    void        SortIndividuals();
    vector<int> StochasticUniversalSampling();
    void        SinglePointCrossover(Population& pop, vector<int> idx);
    void        GaussMutation(Population& pop, int& s);
    void        ReinstateElite(Population& pop, float rr);
    void        Enhance(Population& pop);
    
    int GetIndividualNum() {
        int s = 0;
        for (int i=0; i<MAX_IND; i++)
                s += table[i].size();
        return s;
    }

    /*
     * Getters & Setters
     */

    void SetBLogOnes(bool bLogOnes) {
        this->bLogOnes = bLogOnes;
    }

    bool IsBLogOnes() const {
        return bLogOnes;
    }

    void SetDivEntropy(float divEntropy) {
        this->divEntropy = divEntropy;
    }

    float GetDivEntropy() const {
        return divEntropy;
    }

    void SetAvgTwos(float avgTwos) {
        this->avgTwos = avgTwos;
    }

    float GetAvgTwos() const {
        return avgTwos;
    }

    void SetNumTwos(long numTwos) {
        this->numTwos = numTwos;
    }

    long GetNumTwos() const {
        return numTwos;
    }

    void SetAvgOnes(float avgOnes) {
        this->avgOnes = avgOnes;
    }

    float GetAvgOnes() const {
        return avgOnes;
    }

    void SetNumOnes(long numOnes) {
        this->numOnes = numOnes;
    }

    long GetNumOnes() const {
        return numOnes;
    }

    //void SetStrategicParam(int i, bool value) {
    //    this->strategicParam[i] = value;
    //}

    //bool IsStrategicParam(int i) const {
    //    return strategicParam[i];
    //}

    void SetNumConsPairs(int numConsPairs) {
        this->numConsPairs = numConsPairs;
    }

    int GetNumConsPairs() const {
        return numConsPairs;
    }

    void SetSelIndividual(int i, int value) {
        this->selIndividuals[i] = value;
    }

    int GetSelIndividual(int i) const {
        return selIndividuals[i];
    }

    void SetIndividual(int i, Individual* value) {
        this->individuals[i] = value;
    }

    Individual* GetIndividual(int i) const {
        return individuals[i];
    }

    int GetSize() const {
        return size;
    }

    double GetAvgFitness() const {
        return avgFitness;
    }

    double GetTotalFitness() const {
        return totalFitness;
    }

};

#endif	/* POPULATION_H */

