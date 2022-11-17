/* 
 * File:   HeapSort.cpp
 * Author: CHS
 * 
 * Created on 11. Oktober 2011, 15:22
 */

#include "HeapSort.h"

/**
 * 
 */
HeapSort::HeapSort() {

}


/**
 * 
 */
HeapSort::~HeapSort() {
    //delete[] data;
}

/**
 * 
 * @param a
 * @param size
 */
void HeapSort::Sort(Individual **a, int size) {

    this->size = size;
    
    BuildHeap(a);
    
    for (int i=size-1; i>0; i--) {
        Swap(a[0], a[i]);
        this->size--;
        Heapify(a, 0);
    }
}

/**
 * 
 * @param a
 * @param b
 */
void HeapSort::Swap(Individual*& a, Individual*& b) {
    Individual* tmp;
    tmp = a;
    a = b;
    b = tmp;
}

/**
 * 
 * @param a
 * @param i
 */
void HeapSort::Heapify(Individual **a, int i) {
    int l = 2 * i;      
    int r = l + 1;
    
    int min;
    
    if (l < size && *a[l] < *a[i])
        min = l;
    else
        min = i;
    
    if (r < size && *a[r] < *a[min])
        min = r;
    
    if (min != i) {
        Swap(a[i], a[min]);
        Heapify(a, min);
    }
}

/**
 * 
 * @param a
 */
void HeapSort::BuildHeap(Individual **a) {
    for (int i=(size-1)/2; i>=0; i--)
        Heapify(a, i);
}


