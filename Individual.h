/* 
 * File:   Individual.h
 * Author: CHS
 *
 * Created on 11. Oktober 2011, 13:31
 */

#ifndef INDIVIDUAL_H
#define	INDIVIDUAL_H

#include <vector>

#include "DataUnit.h"

using namespace std;

const int MAX_IND       = 9997;
const int MAX_PROJ      = 10;

class Individual {
    
protected:
    DataUnit    du;
    
private:    
    bool        *bGenom;                // Boolean-Array für das Genom des Individuums bestehend aus Boolean-Werten. Nur für die spätere Ausgabe. 
                                        // Innerhalb der Arbeit wird sonst nur mit reellen Werten gearbeitet
    int         *iGenom;                // Integer-Array für das Genom
    int         consistency;            // Der Konsistenzwert eines Individuums
    int         *consistencies;         // Ein Array für die Konsistenzwerte der Projektionspaare
    int         numBGenoms;
    int         numIGenoms;
    int         numConsPair;
    double      fitness;                // Die Fitness eines Individuums
    int         heapPos;                // Die ursprüngliche Position eines Individuums in der Liste - Für IndexBerechnung im Rahmen der Derandomisierten-ES
    bool        bOnesOverThreshold;
    bool        bTwosOverThreshold;    
    int         numOnes;
    int         numTwos;
    bool        hasFixProj;
    bool        logOnes;
    
    
public:
    Individual();
    virtual ~Individual();
    
    void        Init(DataUnit& du);    
    void        Assign(const Individual& orig);
    void        RandFill();
    void        Recombine(const Individual& a, const Individual& b, const int& split);
    void        CalcConsistency();
    double      CalcFitness();
    void        GaussMutation();
    int         HashVal();
    
    friend bool operator<(Individual& a, Individual& b) {
        return a.GetFitness() < b.GetFitness();
    }
    
    friend bool operator>(Individual& a, Individual& b) {
        return a.GetFitness() > b.GetFitness();
    }
    
    friend bool operator==(Individual& a, Individual& b) {
        
        if (a.GetNumIGenoms() != b.GetNumIGenoms())
            return false;
        
        for (int i=0; i<a.GetNumIGenoms(); i++)
            if (a.GetIGenom(i) != b.GetIGenom(i))
                return false;
        
        return true;
    }
    
    void SetGenomValue(int i, int v) {
        if (i>=0 && i<numIGenoms) {
            if (v != iGenom[i]) {
                iGenom[i] = v;
            }
        }
    }
    
    void SetGenomValue(int i, bool v) {
        if (i>=0 && i<numBGenoms)
            bGenom[i] = v;
    }
    
    int GetIGenom(int i) {
        return iGenom[i];
    }
    
    bool GetBGenom(int i) {
        return bGenom[i];
    }
    
    void SetHasFixProj(bool hasFixProj) {
        this->hasFixProj = hasFixProj;
    }

    bool IsHasFixProj() const {
        return hasFixProj;
    }

    void SetNumTwos(int numTwos) {
        this->numTwos = numTwos;
    }

    int GetNumTwos() const {
        return numTwos;
    }

    void SetNumOnes(int numOnes) {
        this->numOnes = numOnes;
    }

    int GetNumOnes() const {
        return numOnes;
    }

    void SetTwosOverThreshold(bool bTwosOverThreshold) {
        this->bTwosOverThreshold = bTwosOverThreshold;
    }

    bool IsTwosOverThreshold() const {
        return bTwosOverThreshold;
    }

    void SetOnesOverThreshold(bool bOnesOverThreshold) {
        this->bOnesOverThreshold = bOnesOverThreshold;
    }

    bool IsOnesOverThreshold() const {
        return bOnesOverThreshold;
    }

    void SetHeapPos(int heapPos) {
        this->heapPos = heapPos;
    }

    int GetHeapPos() const {
        return heapPos;
    }

    void SetFitness(double fitness) {
        this->fitness = fitness;
    }

    double GetFitness() const {
        return fitness;
    }
    
    void SetLogOnes(bool logOnes) {
        this->logOnes = logOnes;
    }

    bool IsLogOnes() const {
        return logOnes;
    }

    int GetNumConsPair() const {
        return numConsPair;
    }

    int GetNumIGenoms() const {
        return numIGenoms;
    }

    int GetNumBGenoms() const {
        return numBGenoms;
    }
    
    char* ToString() {
        char *buffer = new char[200];
        char *str = new char[50];
        
        strcpy(buffer, "");
        
        for (int i=0; i<numIGenoms; i++) {
            sprintf(str, "%d ", iGenom[i]);
            buffer = strcat(buffer, str);
        }

        sprintf(str, "  FIT: %.3lf   HV: %5d", fitness, HashVal());
        buffer = strcat(buffer, str);        
        
        return buffer;
    }
    
};


#endif	/* INDIVIDUAL_H */
