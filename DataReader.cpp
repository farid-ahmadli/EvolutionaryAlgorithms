/* 
 * File:   DataReader.cpp
 * Author: CHS
 * 
 * Created on 11. October 2011, 15:02
 */

#include "DataReader.h"

DataReader::DataReader() {
}

/*
 * Default constructor of DataReader class.
 * Reads an XML file and fills the Data unit object with values from this file.
 */
DataReader::DataReader(const char* filename, DataUnit& du) {
    
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;
    
    doc = xmlReadFile(filename, NULL, 0);                       // reading document from xml, libxml parses it automatically into a tree
    root_element = xmlDocGetRootElement(doc);                   // get the root element of the tree
    
    du.InitData();                                              // initializing data unit
    ReadKeyFactors(root_element, du);                           // calculating number of factors and projections from xml
    du.InitCsvMatrix(du.GetNumProj(), du.GetNumProj());         // initializing consistency values matrix
    ReadCsvMatrix(root_element, du);                            // filling consistency values matrix from xml
    
    xmlFreeDoc(doc);                                            // free memory when done
}

DataReader::~DataReader() {
}

xmlNode* DataReader::NextElement(xmlNode* node) {
    xmlNode *cur_node = NULL;
    cur_node = node->next;
    
    while (cur_node != NULL && cur_node->type != XML_ELEMENT_NODE)
        cur_node = cur_node->next;
    
    return cur_node;
}

/*
 * Going through all nodes, it checks their names and initializes number of key factors and projections.
 */
void DataReader::ReadKeyFactors(xmlNode* node, DataUnit& du) {
   
    xmlNode *cur_node = NULL;
    cur_node = NextElement(node->children);
    int num_proj;
    int total_proj;
    vector<int> num_kf;
    
    while (xmlStrcmp(cur_node->name, (xmlChar*)"FACTOR") != 0)
        cur_node = NextElement(cur_node);
    
    total_proj = 0;
    while (cur_node != NULL) {                  // go through all factors
        xmlNode *proj_node;        
        proj_node = NextElement(cur_node->children);   // and for each factor
        
        num_proj = 0;
        while (proj_node != NULL) {             // go through all its projections
            num_proj++;
            proj_node = NextElement(proj_node); // go to the next projection
        }
        total_proj += num_proj;                 // counting total number of projections
        num_kf.push_back(num_proj);             // set number of projection for the key factor
        
        cur_node = NextElement(cur_node);       // go to the next factor
    }
    
    du.SetNumKF(num_kf.size());                 // set the number of key factors (number of total pairs is also calculated)
    du.SetNumProj(total_proj);                  // set the number of total projections
    du.SetNumProjKF(&num_kf[0]);                // set the count of projections for each key factor
    
    du.SetSigma(10);                            // set starting step size of Gauss-Mutation
    du.SetSizePopP(du.GetNumProj());            // set size of the parent population
    du.SetSizePopC(du.GetSizePopP()*6);         // set size of the child population
    du.SetNumGnr(30);                           // set number of generations to iterate
    du.SetSizeHoF(100);                         // set the size of the Hall of Fame
    du.SetNumEF(35);                            // set the number of effecting factors
    //du.Set
    du.SetNumFixProj(0);
    du.SetBestCsvSum(du.GetNumCsvPairs()*5);    // set best possible consistency value by rating everything with 5
    //du.Init
    du.SetMinMax(1);                            // set min - 0, max - 1
    // READ EF MATRIX
    du.SetReinstateRate(0.8);
    du.SetPenTotIncons(0.99);
    du.SetPenPartIncons(0.999);
    du.SetPenMissProj(0.8);
    du.SetThrTotIncons(1);
    du.SetThrPartIncons(16);
    
    du.SetLinkIMxCMx(false);
    
    if (du.GetNumFixProj() > 0) {
        du.InitNumProjKF(du.GetNumFixProj());
        
        // TODO set fixed projections
    }
    
    du.SetBrkConvrg(true);
    du.SetBrkGnr(true);
    du.SetBrkTime(false);
    du.SetBrkHof(false);
    
    du.SetLimitTime(60);
    du.SetLimitGnr(30);
    du.SetLimitConvrg(0.1);
    du.SetLimitHof(0);
    
    du.InitAvgFitness(du.GetLimitGnr());
    
    du.SetAllowOnes(true);
    du.SetOnesInHoF(false);
    du.SetNonFixProjInHoF(false);
    du.SetChance(false);
    du.SetChanceFactor(0.02);
    
    du.SetWeight(false);
    // du.InitWeightMatrix(...
    
    // denial reasons array
    
    // individual exists
    
    du.SetLogOnes(false);
    
}

/*
 * This function reads the xml tree using depth first search method.
 * It goes through all nodes and fills the existing consistency values matrix.
 * Note: the matrix must be first initialized with values from ReadKeyFactors method.
 */
void DataReader::ReadCsvMatrix(xmlNode* node, DataUnit& du) {
    xmlNode *cur_node;

    for (cur_node = node; cur_node; cur_node = NextElement(cur_node)) {

        if (xmlStrcmp(cur_node->name, (xmlChar*)"PROJECTION") == 0) {                           // find a projection
            xmlChar *proj_id = xmlGetProp(cur_node, (xmlChar*)"projectionid");                  // get the id of projection                
            cur_proj = du.GetSumProjKF((int)(proj_id[0] - '1')) + ((int)(proj_id[1] - 'A'));    // and convert it to its order number
        } 
        else if (xmlStrcmp(cur_node->name, (xmlChar*)"MATRIXRELATION") == 0) {                  // find a relation 
            xmlChar *proj_id = xmlGetProp(cur_node, (xmlChar*)"projectionid");                          // get the id of projection                
            int proj_num = du.GetSumProjKF((int)(proj_id[0] - '1')) + ((int)(proj_id[1] - 'A'));// and convert it to its order number
            int value = atoi((char*)xmlGetProp(cur_node, (xmlChar*)"correlationvalue"));        // get the consistency value

            du.SetCsValue(cur_proj, proj_num, value);                                           // setting consistency value
        }
        
        if (cur_node->children != NULL)
                ReadCsvMatrix(NextElement(cur_node->children), du);
    }
}
