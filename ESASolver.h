/* 
 * File:   ESASolver.h
 * Author: CHS
 *
 * Created on 11. Oktober 2011, 15:01
 */

#ifndef ESASOLVER_H
#define	ESASOLVER_H

#include <time.h>

#include "HeapSort.h"
#include "DataUnit.h"
#include "DataReader.h"
#include "Population.h"
#include "Individual.h"
#include "Debug.h"

class ESASolver {
private:
    Debug               debug;
    DataUnit            du;
    DataReader          dr;
    Population          popParent;              // current parent population
    Population          popParentPreSel;        // parent population before selection
    Population          popChild;               // current child population
    Population          popBestList;
    Population          popBests;
    Population          popBestPerProj;
    
protected:
    void CreateInitialPopulation();
    void Solve();
    
public:
    ESASolver(const char *filename);
    virtual ~ESASolver();
    
    void        Start();
    double      AdaptiveAdjust(double sigma, double param);

    void SetPopBestPerProj(Population popBestPerProj) {
        this->popBestPerProj = popBestPerProj;
    }

    Population GetPopBestPerProj() const {
        return popBestPerProj;
    }

    void SetPopBests(Population popBests) {
        this->popBests = popBests;
    }

    Population GetPopBests() const {
        return popBests;
    }

    void SetPopBestList(Population popBestList) {
        this->popBestList = popBestList;
    }

    Population GetPopBestList() const {
        return popBestList;
    }

    void SetPopChild(Population popChild) {
        this->popChild = popChild;
    }

    Population GetPopChild() const {
        return popChild;
    }

    void SetPopParent(Population popParent) {
        this->popParent = popParent;
    }

    Population GetPopParent() const {
        return popParent;
    }

};

#endif	/* ESASOLVER_H */

