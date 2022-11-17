/* 
 * File:   Population.cpp
 * Author: CHS
 * 
 * Created on 11. Oktober 2011, 13:23
 */

#include "Population.h"

/**
 * 
 */
Population::Population() {
    size = 0;
    selSize = 0;
    numConsPairs = 0;
    selIndividuals = NULL;
    individuals = NULL;
}

/**
 * 
 */
Population::~Population() {
//    delete [] individuals;
//    delete [] selIndividuals;
}

/**
 * Hier könnten irgendwelche Defaultwerte initialisiert werden (Diese Funktion wird bei jedem New Befehl aufgerufen). Da ich aber Populationen mit unterschiedlichen
 * Parametern erzeugen möchte, geschieht dies manuell über die Init-Methode dieser Klasse
 * 
 * @param size
 * @param du
 */
void Population::Init(int size, DataUnit& du) {
    //this->debug = debug;
    this->size = size;
    this->du = du;
    
    individuals = new Individual*[this->size];
    
    for (int i=0; i<this->size; i++) {
        individuals[i] = new Individual();
        individuals[i]->Init(du);
        // AddIndividual(individuals[i]);
    }

}

/**
 * This method assigns all values inside source population to the target population.
 * Deep copy method is used, for each Individual its own assign method is used.
 * 
 * @param orig
 */
void Population::Assign(const Population& orig) {
    // here we copy ordinary (int, double, ...) typed values
    size = orig.size;
    selSize = orig.selSize;
    numConsPairs = orig.numConsPairs;
    numOnes = orig.numOnes;
    avgOnes = orig.avgOnes;
    numTwos = orig.numTwos;
    avgTwos = orig.avgTwos;
    divEntropy = orig.divEntropy;
    bLogOnes = orig.bLogOnes;
    
    // here we copy a dynamic array (as a pointer)
    if (selIndividuals != NULL && selSize > 0)
        copy(orig.selIndividuals, orig.selIndividuals + selSize, selIndividuals);
    
    RemoveIndividuals();
    
    // here we copy individuals of the population using its own Assign method
    if (individuals != NULL && size > 0) {
        for (int i=0; i<size; i++) {
            individuals[i]->Assign(*orig.individuals[i]); // assign values of the individuals
            AddIndividual(individuals[i]);              // add the individual to the hash table
        }
    }
}

/**
 * Hier werden der Geschwindigkeit wegen direkt nur gültige Lösungen erzeugt
 * Diese Methode erzeugt eine ReellwertigeAusgangspopulation
 * (Es werden an gleichverteilt zufällige Werte an die Stellen des Genoms geschrieben)
 */
void Population::RandPopulate() {
    //srand(time(NULL));                  // initializing randomizer
    
    for (int i=0; i<size; i++) {        // for each individual in the population
        
        // TODO maybe change to individuals[i].RandFill()
        individuals[i]->RandFill();
        AddIndividual(individuals[i]);
    }
}

/**
 * This method adds the reference (pointer) of an existing individual into the hash table.
 * This table will be used later for fast search operation, without going through all individuals.
 * 
 * @param ind
 */
void Population::AddIndividual(Individual* ind) {
    int val = ind->HashVal();
    ind->SetHeapPos(table[val].size());
    table[val].push_back(ind);
    
    /*if (size == 20)
        printf("ADD %s   (%5d : %d: %d)\n", ind->ToString(), val, ind->GetHeapPos(), table[val].size()); */
}

/**
 * Fast search function of an individual within the population.
 * It uses hash value of the individual, to find it from the table where it was stored before.
 * 
 * @param ind
 * @return 
 */
 bool Population::FindIndividual(Individual* ind) {
     int val = ind->HashVal();
     
     for (int i=0; i<table[val].size(); i++) {
         Individual* a = table[val][i];         // get the individual from the table
         
         if (*a == *ind) {
             return true;                       // return true on match
         }
     }
     
     return false;                              // return false, if no match found
 }
 
 /**
  * 
  * @param ind
  */
 void Population::RemoveIndividual(Individual* ind) {
     if (ind->GetHeapPos() >= 0) {
         int val = ind->HashVal();
         int hp = ind->GetHeapPos();

         for (int i=hp+1; i<table[val].size(); i++)
             table[val][i]->SetHeapPos(i-1);
         
         table[val].erase(table[val].begin() + hp);
         
         /*if (size == 20)
             printf("REMOVE %s   (%5d : %d: %d)\n", ind->ToString(), val, ind->GetHeapPos(), table[val].size());
          */
         
         ind->SetHeapPos(-1);
     }
 }
 
 /**
  * 
  */
 void Population::RemoveIndividuals() {
     for (int i=0; i<size; i++) {
         int val = individuals[i]->HashVal();
         individuals[i]->SetHeapPos(-1);
         if (table[val].size() > 0)
             table[val].clear();
     }
 }

/**
 * This method sorts all individuals within the population using their fitness value to compare.
 * HeapSort algorithm is used.
 */
void Population::SortIndividuals() {
    hs.Sort(individuals, size);                         // sorting via heapsort algorithms, using fitness to compare
}

/**
 * This method calculates fitness of all individuals within the population.
 * Besides, it calculates total fitness of the population.
 */
void Population::CalcFitness() {
    totalFitness = 0;
    for (int i=0; i<size; i++) {
        totalFitness += individuals[i]->GetFitness();   // calculate fitness of each individual
    }
    avgFitness = totalFitness / size;
}

/**
 * Stochastic Universal Sampling ...
 * 
 * @return 
 */
vector<int> Population::StochasticUniversalSampling() {
    SortIndividuals();  // sort first
    
    //srand(time(NULL));
    
    int numSelInd = (int)ceil(0.5 + sqrt(0.5 + 2 * du.GetSizePopC()));        // number individuals to select
    
    double step = totalFitness / numSelInd;
    double startPoint = step * (1.0 * rand() / RAND_MAX);
    double pointer = startPoint;
    int k = 0;
    double f = 0.0;
    vector<int> selInd;
    
    for (int i=0; i<numSelInd; i++) {
        while  (!(f < pointer && pointer < f + individuals[k]->GetFitness())) {
            f += individuals[k]->GetFitness();
            k++;
        }
        pointer += step;
        selInd.push_back(k);
    }
    
    return selInd;
}

/**
 * This method recombines individuals using single point crossover algorithm.
 * Goings through possible pairs of different individuals, we combine them to get a new individual,
 * until the number of individuals reaches given limit.
 * 
 * @param pop
 * @param s
 */
void Population::SinglePointCrossover(Population& pop, vector<int> idx) {
    int k = 0;
    int limit = size;
    int kf = du.GetNumKF()-1;
    
    //srand(time(NULL));  // initialize randomizer
    
    RemoveIndividuals();
        
    while (k < limit) {
        for (int i=0; i<idx.size(); i++) {
            
            for (int j=0; j<idx.size(); j++) {
                
                    if (i != j) {

                    individuals[k]->Recombine(*pop.GetIndividual(idx[i]), *pop.GetIndividual(idx[j]), 1 + rand() % kf);
                    // TODO idx[i], idx[j] or i, j ??

                    if (!FindIndividual(individuals[k]) && !pop.FindIndividual(individuals[k])) {
                        AddIndividual(individuals[k]);
                        k++;
                    }
                }
                if (k == limit) break;
            }
            if (k == limit) break;
        }
    }
    
    CalcFitness();
}

/**
 * This method performs Gaussian mutation of the entire population.
 * If mutation is successful, old individual is removed from the population and a new one appears instead.
 * 
 * @param pop
 * @param rr
 */ 
void Population::GaussMutation(Population& pop, int& s) {

    Individual a;
    for (int i=0; i<size;) {
        a.Assign(*individuals[i]);
        a.GaussMutation();
        
        if (!FindIndividual(&a) && !pop.FindIndividual(&a)) {
            if (a > *individuals[i]) {
                s++;
            }
            
            RemoveIndividual(individuals[i]);
            individuals[i]->Assign(a);
            AddIndividual(individuals[i]);
            
            i++;
        }
    }
<<<<<<< .mine
}
=======
    
    CalcFitness();
}

/**
 * 
 * @param pop
 * @param rr
 */
void Population::ReinstateElite(Population& pop, float rr) {
    int numChange = (int)(size * rr);
    
    for (int i=0; i<numChange; i++) {
        RemoveIndividual(individuals[size-i-1]);
        individuals[size-i-1]->Assign(*pop.GetIndividual(i));
        AddIndividual(individuals[size-i-1]);
    }
    
    CalcFitness();
}

/**
 * 
 * @param pop
 */
void Population::Enhance(Population& pop) {
    for (int i=0; i<pop.GetSize(); i++) {
        Individual* ind = pop.GetIndividual(i);
        
        if (*ind < *individuals[size-1] || FindIndividual(ind))
            continue;

        RemoveIndividual(individuals[size-1]);
        individuals[size-1]->Assign(*ind);
        AddIndividual(individuals[size-1]);

        int i = size-1;
        while (i > 0 && *individuals[i] > *individuals[i-1]) {
            hs.Swap(individuals[i], individuals[i-1]);
            i--;        
        }
    }
    
    CalcFitness();
}>>>>>>> .r19
