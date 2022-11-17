/* 
 * File:   HeapSort.h
 * Author: CHS
 *
 * Created on 11. Oktober 2011, 15:22
 */

#ifndef HEAPSORT_H
#define	HEAPSORT_H

#include "Individual.h"

class HeapSort {
private:
    int         size;
    
protected:    
    void Heapify(Individual **a, int i);
    void BuildHeap(Individual **a);
    
public:
    HeapSort();
    virtual ~HeapSort();
        
    void Sort(Individual **a, int size);
    void Swap(Individual*& a, Individual*& b);
    
};

#endif	/* HEAPSORT_H */

