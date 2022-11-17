/* 
 * File:   ESASolver.cpp
 * Author: CHS
 * 
 * Created on 11. Oktober 2011, 15:01
 */

#include "ESASolver.h"

ESASolver::ESASolver(const char *filename) {
    dr = DataReader(filename, du);    
}

ESASolver::~ESASolver() {
}

void ESASolver::CreateInitialPopulation() {
    popParent.Init(du.GetSizePopP(), du);       // creating parent population
    popParent.RandPopulate();
    popParent.CalcFitness();
    popParent.SortIndividuals();
    //debug.PrintPopulation(popParent);   // debug
    
    popBests.Init(du.GetSizeHoF(), du);         // creating the best population
    popBests.RandPopulate();
    popBests.CalcFitness();
    popBests.SortIndividuals();
    debug.PrintPopulation(popBests);    // debug
}

void ESASolver::Solve() {
    bool terminated = false;
    
    int numGeneration = 1;
    
    long timer = time(NULL);
    
    //double startStep = du.GetSigma();
    int sigmaAdapt = du.GetNumKF() / 2;
    
    popChild.Init(du.GetSizePopC(), du);
        
    // TODO HoF
    
    double fitGrad = 0.00001;
    int fitGradInt = 10;
    
    int minHoF = 0;
    int s = 0;
    
    while (!terminated) {
        printf("Generation %d: \n", numGeneration);
        
        // TODO some output
        
        popChild.SinglePointCrossover(popParent, popParent.StochasticUniversalSampling());
        
        // TODO some output
        //debug.PrintPopulation(popChild);        
        
        popChild.GaussMutation(popParent, s);
        popChild.SortIndividuals();        
        // TODO some output
        //debug.PrintPopulation(popChild);
        
        popParent.ReinstateElite(popChild, du.GetReinstateRate());
        popParent.SortIndividuals();
        // TODO some output
        //debug.PrintPopulation(popParent);
        
        popBests.Enhance(popParent);
        // TODO some output
        debug.PrintPopulation(popBests);
                
        // update sigma
        if (numGeneration % sigmaAdapt == 0) {
            du.SetSigma(AdaptiveAdjust(du.GetSigma(), (s / (sigmaAdapt * du.GetSizePopC()))));
            s = 0;
        }
        
        // set average of the generation
        du.SetAvgFitness(numGeneration, popBests.GetAvgFitness());
        
        // TODO some output
        
        // termination criterion convergence
        if (du.IsBrkConvrg()) {
            if (numGeneration > 2 * fitGradInt) {
                double grad = du.GetAvgFitness(numGeneration - fitGradInt) / du.GetAvgFitness(numGeneration);
                if (fabs(1 - grad) <= fitGrad) {
                    terminated = true;
                }
            }
        }
        
        // termination time
        if (du.IsBrkTime()) {
            if ((time(NULL) - timer) / 1000 >= du.GetLimitTime()) {
                terminated = true;
            }
        }
        
        // termination max number of generations
        if (du.IsBrkGnr()) {
            if (numGeneration >= du.GetLimitGnr()) {
                terminated = true;
            }
        }
        
        // termination max number of elements in hof
        if (du.IsBrkHof()) {
            // TODO Hof
        }
        
        numGeneration++;
        
        terminated = true;
    }
    
    // more output
}

void ESASolver::Start() {
    srand(1000000);
    
    debug.Start(false, "logs.txt");
    
    debug.PrintCsvMatrix(du);
    
    CreateInitialPopulation();
    // HeaderPopulationUndHallofFameErzeugen TODO ??
    // AusgabeDerAktuellenElternPopulation
    
<<<<<<< .mine
    Solve();
=======
    Solve();
    
>>>>>>> .r19
    debug.End();
}

double ESASolver::AdaptiveAdjust(double sigma, double param) {
    double level, alpha;
    
    level = 0.2;
    alpha = 1.224;
    
    if (param > level)
        return sigma * alpha;
    
    if (param < level)
        return sigma / alpha;
    
    return sigma;
}
