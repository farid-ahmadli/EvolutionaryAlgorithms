/* 
 * File:   Debug.cpp
 * Author: CHS
 * 
 * Created on 11. Oktober 2011, 14:57
 */

#include "Debug.h"

Debug::Debug() {
}

Debug::~Debug() {    
}

/**
 * 
 * @param stdIO
 * @param logFile
 */
void Debug::Start(const bool stdIO, const char* logFile) {
    this->stdIO = stdIO;
    
    f = fopen(logFile, "w");
}

/**
 * 
 */
void Debug::End() {
    fclose(f);
}

/**
 * 
 * @param du
 */
void Debug::PrintCsvMatrix(DataUnit& du) {
    
    for (int i=0; i<du.GetNumProj(); i++) {
        for (int j=0; j<du.GetNumProj(); j++) {
            int val = du.GetCsValue(i, j);
            if (val <= 0 || val > 6) {
                if (stdIO) printf("  ");        // put empty space instead of zeros
                fprintf(f, "  ");
            }
            else {
                if (stdIO) printf("%d ", du.GetCsValue(i, j));
                fprintf(f, "%d ", du.GetCsValue(i, j));
            }
        }
        if (stdIO) printf("\n");
        fprintf(f, "\n");
    }
}

/**
 * 
 * @param pop
 */
void Debug::PrintPopulation(Population& pop) {
    if (stdIO) printf("\n");
    fprintf(f, "\n");
    for (int i=0; i<pop.GetSize(); i++) {
        if (stdIO) printf("Population %3d:  ", (i+1));
        fprintf(f, "Population %3d:  ", (i+1));
        
        PrintIndividual(pop.GetIndividual(i));
        
        fprintf(f, "\n");        
    }    
    
    int s = 0;
    for (int i=0; i<MAX_IND; i++) {
        s += pop.table[i].size();
        for (int j=0; j<pop.table[i].size(); j++)
            fprintf(f, "%d ", pop.table[i][j]->HashVal());        
    }
    
    fprintf(f, " | %d\n", s);
    fflush(f);
        
}

<<<<<<< .mine
void Debug::PrintIndividual(Individual& ind) {
    for (int i=0; i<ind.GetNumIGenoms(); i++) {
        printf("%d ", ind.GetIGenom(i));
    }
    
    printf("  FIT: %.3lf\n", ind.GetFitness());
}
=======
/**
 * 
 * @param ind
 */
void Debug::PrintIndividual(Individual* ind) {
    char * s = ind->ToString();
    if (stdIO) printf("%s", s);
    fprintf(f, "%s", s);
}
>>>>>>> .r19
