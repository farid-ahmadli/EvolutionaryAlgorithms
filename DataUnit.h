/* 
 * File:   DataUnit.h
 * Author: Farid
 *
 * Created on October 14, 2011, 1:36 AM
 */

#ifndef DATAUNIT_H
#define	DATAUNIT_H

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

static int** InitIntMatrix(int rows, int cols ) {
    int **matrix = new int*[rows];
    for(int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
        memset(matrix[i], 0, sizeof(int)*cols);
    }
    return matrix;
}

static int RandNormDist(double mu, double stabw) {
    //srand(time(NULL));
    
    double sum = 0;
    
    for (int i=0; i<12; i++) 
        sum += rand() / RAND_MAX;
    
    return abs((int)(stabw * (sum - 6) + mu));
}

class DataUnit {
private:
    int                 **csvMatrix;            // matrix of consistency values
    int                 **efMatrix;             // matrix of effecting factors
    int                 **weightMatrix;         // matrix of weight values
    int                 bestCsvSum;             // best possible sum of consistency values
    int                 numKF;                  // number of key factors
    long                numCsvPairs;            // number of consistency value pairs
    int                 numFixProj;             // number of fixed projections
    int                 numProj;                // number of projections
    int                 numGnr;                 // number of generations (iterations)
    int                 numEF;                  // number of effecting factors
    double              numL;                   // number of possible combinations
    int                 sizePopP;               // size of the parent population
    int                 sizePopC;               // size of the child population    
    long                sizeHoF;                // size of "Hall of Fame"
    int                 *numProjKF;             // number of projections for each key factor
    int                 *sumProjKF;             // ...    
    int                 *relKFEF;               // relation of key factor with effecting factors   
    int                 minMax;                 // 0 - minimization, 1 - maximization
    bool                brkTime;                // break on time limit
    bool                brkConvrg;              // break on convergence limit
    bool                brkGnr;                 // break on max generation limit
    bool                brkHof;                 // break on max number in the hall of fame
    bool                bLinkIMxCMx;            // ...
    bool                bBestPerProj;           // find best bundle for every projection
    bool                bLogOnes;               // save the log of ones 
    bool                bWeight;                // weight function switch
    bool                bChance;                // chance function switch
    bool                bAllowOnes;             // allow ones
    bool                bOnesInHoF;             // allow individuals with one into the "Hall of Fame"
    bool                bNonFixProjInHoF;       // allow individuals without fixed projection into HoF
    int                 *fixedProj;             // fixed projections
    float               reinstateRate;          // elite child pop. will be reinstated parent pop.
    float               chanceFactor;           // chance factor
    float               penTotIncons;           // penalty value for total inconsistency
    float               penPartIncons;          // penalty value for partial inconsistency
    float               penMissProj;            // penalty value for missing projections
    int                 limitConvrg;            // termination criterion convergency
    int                 limitTime;              // termination criterion time limit
    int                 limitGnr;               // termination criterion maximal number of generations
    int                 limitHof;               // termination criterion maximal number in the hall of fame
    int                 thrTotIncons;           // threshold value for total inconsistency
    int                 thrPartIncons;          // threshold value for partial inconsistency
    double              sigma;                  // adaptive value ...
    double              *avgFitness;

    
public:
    DataUnit();
    virtual ~DataUnit();

    void SetSigma(double sigma) {
        this->sigma = sigma;
    }

    double GetSigma() const {
        return sigma;
    }

    void SetThrPartIncons(int thrPartIncons) {
        this->thrPartIncons = thrPartIncons;
    }

    int GetThrPartIncons() const {
        return thrPartIncons;
    }

    void SetThrTotIncons(int thrTotIncons) {
        this->thrTotIncons = thrTotIncons;
    }

    int GetThrTotIncons() const {
        return thrTotIncons;
    }

    void SetPenMissProj(float penMissProj) {
        this->penMissProj = penMissProj;
    }

    float GetPenMissProj() const {
        return penMissProj;
    }

    void SetPenPartIncons(float penPartIncons) {
        this->penPartIncons = penPartIncons;
    }

    float GetPenPartIncons() const {
        return penPartIncons;
    }

    void SetPenTotIncons(float penTotIncons) {
        this->penTotIncons = penTotIncons;
    }

    float GetPenTotIncons() const {
        return penTotIncons;
    }

    void SetChanceFactor(float chanceFactor) {
        this->chanceFactor = chanceFactor;
    }

    float GetChanceFactor() const {
        return chanceFactor;
    }

    void SetReinstateRate(float reinstateRate) {
        this->reinstateRate = reinstateRate;
    }

    float GetReinstateRate() const {
        return reinstateRate;
    }

    void SetFixedProj(int i, int fixedProj) {
        this->fixedProj[i] = fixedProj;
    }

    int GetFixedProj(int i) const {
        return fixedProj[i];
    }

    void SetNonFixProjInHoF(bool bNonFixProjInHoF) {
        this->bNonFixProjInHoF = bNonFixProjInHoF;
    }

    bool IsNonFixProjInHoF() const {
        return bNonFixProjInHoF;
    }

    void SetOnesInHoF(bool bOnesInHoF) {
        this->bOnesInHoF = bOnesInHoF;
    }

    bool IsOnesInHoF() const {
        return bOnesInHoF;
    }

    void SetAllowOnes(bool bAllowOnes) {
        this->bAllowOnes = bAllowOnes;
    }

    bool IsAllowOnes() const {
        return bAllowOnes;
    }

    void SetChance(bool bChance) {
        this->bChance = bChance;
    }

    bool IsChance() const {
        return bChance;
    }

    void SetWeight(bool bWeight) {
        this->bWeight = bWeight;
    }

    bool IsWeight() const {
        return bWeight;
    }

    void SetLogOnes(bool bLogOnes) {
        this->bLogOnes = bLogOnes;
    }

    bool IsLogOnes() const {
        return bLogOnes;
    }

    void SetBestPerProj(bool bBestPerProj) {
        this->bBestPerProj = bBestPerProj;
    }

    bool IsBestPerProj() const {
        return bBestPerProj;
    }

    void SetLinkIMxCMx(bool bLinkIMxCMx) {
        this->bLinkIMxCMx = bLinkIMxCMx;
    }

    bool IsLinkIMxCMx() const {
        return bLinkIMxCMx;
    }

    void SetMinMax(int minMax) {
        this->minMax = minMax;
    }

    int GetMinMax() const {
        return minMax;
    }

    void SetSizeHoF(long sizeHoF) {
        this->sizeHoF = sizeHoF;
    }

    long GetSizeHoF() const {
        return sizeHoF;
    }

    long GetNumCsvPairs() const {
        return numCsvPairs;
    }

    void SetSizePopC(int sizePopC) {
        this->sizePopC = sizePopC;
    }

    int GetSizePopC() const {
        return sizePopC;
    }

    void SetSizePopP(int sizePopP) {
        this->sizePopP = sizePopP;
    }

    int GetSizePopP() const {
        return sizePopP;
    }

    void SetNumL(double numL) {
        this->numL = numL;
    }

    double GetNumL() const {
        return numL;
    }

    void SetRelKFEF(int i, int relKFEF) {
        this->relKFEF[i] = relKFEF;
    }

    int GetRelKFEF(int i) const {
        return relKFEF[i];
    }

    void SetNumEF(int numEF) {
        this->numEF = numEF;
    }

    int GetNumEF() const {
        return numEF;
    }

    void SetNumGnr(int numGnr) {
        this->numGnr = numGnr;
    }

    int GetNumGnr() const {
        return numGnr;
    }
    
    void InitNumProjKF(int size) {
        this->numProjKF = new int[size];
    }
    
    void SetNumProjKF(int *a) {
        int size = numKF;        
        numProjKF = new int[size];
        sumProjKF = new int[size+1];
        
        sumProjKF[0] = 0;
        for (int i=0; i<size; i++) {
            numProjKF[i] = a[i];
            sumProjKF[i+1] = sumProjKF[i] + numProjKF[i];
        }
    }

    int GetNumProjKF(int i) const {
        return numProjKF[i];
    }
    
    int GetSumProjKF(int i) const {
        return sumProjKF[i];
    }

    void SetNumProj(int numProj) {
        this->numProj = numProj;
    }

    int GetNumProj() const {
        return numProj;
    }

    void SetNumFixProj(int numFixProj) {
        this->numFixProj = numFixProj;
    }

    int GetNumFixProj() const {
        return numFixProj;
    }

    void SetNumKF(int numKF) {
        this->numKF = numKF;
        this->numCsvPairs = numKF*(numKF-1)/2;
    }

    int GetNumKF() const {
        return numKF;
    }

    void SetBestCsvSum(int bestCsvSum) {
        this->bestCsvSum = bestCsvSum;
    }

    int GetBestCsvSum() const {
        return bestCsvSum;
    }
    
    void InitWeightMatrix(int rows, int cols) {
        this->weightMatrix = InitIntMatrix(rows, cols);
    }

    int** GetWeightMatrix() const {
        return weightMatrix;
    }
    
    int GetWeightValue(int row, int col) {
        return this->weightMatrix[row][col];
    }

    void InitEfMatrix(int rows, int cols) {
        this->efMatrix = InitIntMatrix( rows, cols);
    }

    int** GetEfMatrix() const {
        return efMatrix;
    }
    
    int GetEfValue(int row, int col) {
        return this->efMatrix[row][col];
    }

    void InitCsvMatrix(int rows, int cols) {
        this->csvMatrix = InitIntMatrix(rows, cols);
    }

    int** GetCsvMatrix() const {
        return csvMatrix;
    }
    
    void SetCsValue(int r, int c, int v) {
        this->csvMatrix[r][c] = v;
    }
    
    int GetCsValue(int r, int c) {
        return this->csvMatrix[r][c];
    }
        
    void InitData() {
        numKF = 0;
        numProj = 0;
    }

    void SetLimitHof(int limitHof) {
        this->limitHof = limitHof;
    }

    int GetLimitHof() const {
        return limitHof;
    }

    void SetLimitGnr(int limitGnr) {
        this->limitGnr = limitGnr;
    }

    int GetLimitGnr() const {
        return limitGnr;
    }

    void SetLimitTime(int limitTime) {
        this->limitTime = limitTime;
    }

    int GetLimitTime() const {
        return limitTime;
    }

    void SetLimitConvrg(int limitConvrg) {
        this->limitConvrg = limitConvrg;
    }

    int GetLimitConvrg() const {
        return limitConvrg;
    }

    void SetBrkHof(bool brkHof) {
        this->brkHof = brkHof;
    }

    bool IsBrkHof() const {
        return brkHof;
    }

    void SetBrkGnr(bool brkGnr) {
        this->brkGnr = brkGnr;
    }

    bool IsBrkGnr() const {
        return brkGnr;
    }

    void SetBrkConvrg(bool brkConvrg) {
        this->brkConvrg = brkConvrg;
    }

    bool IsBrkConvrg() const {
        return brkConvrg;
    }

    void SetBrkTime(bool brkTime) {
        this->brkTime = brkTime;
    }

    bool IsBrkTime() const {
        return brkTime;
    }    
        
    void InitAvgFitness(const int size) {
        avgFitness = new double[size];
    }
    
    void SetAvgFitness(int i, double val) {
        avgFitness[i] = val;
    }
    
    double GetAvgFitness(int i) const {
        return avgFitness[i];
    }

    
};

#endif	/* DATAUNIT_H */

