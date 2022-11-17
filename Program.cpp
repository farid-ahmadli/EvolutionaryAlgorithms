/* 
 * File:   main.cpp
 * Author: CHS
 *
 * Created on 11. Oktober 2011, 13:23
 */

#include <stdlib.h>
#include <time.h>

#include "Population.h"
#include "DataReader.h"
#include "Individual.h"
#include "ESASolver.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {    
    
    ESASolver solver = ESASolver("input.xml");
    solver.Start();
    
    return 0;
}
