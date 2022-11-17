/* 
 * File:   Debug.h
 * Author: CHS
 *
 * Created on 11. Oktober 2011, 14:57
 */

#ifndef DEBUG_H
#define	DEBUG_H

#include <stdio.h>

#include "Individual.h"
#include "Population.h"
#include "DataUnit.h"

class Debug {

private:
    bool stdIO;
    char* logFile;
    FILE* f;
    
public:
    Debug();    
    virtual ~Debug();
    
    void Start(const bool stdIO, const char* logFile);
    void End();
    
    void PrintCsvMatrix(DataUnit& du);
    void PrintPopulation(Population& pop);
    void PrintIndividual(Individual* ind);

};

#endif	/* DEBUG_H */

