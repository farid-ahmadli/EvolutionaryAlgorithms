/* 
 * File:   DataReader.h
 * Author: CHS
 *
 * Created on 11. Oktober 2011, 15:02
 */

#ifndef DATAREADER_H
#define	DATAREADER_H

#include "DataUnit.h"
#include <stdio.h>
#include <vector>
#include <libxml/parser.h>
#include <libxml/tree.h>

using namespace std;

class DataReader {
private:
    int cur_proj;
    
public:
    DataReader();
    DataReader(const char* filename, DataUnit& du);
    virtual ~DataReader();
    
    xmlNode* NextElement(xmlNode* node);
    void ReadKeyFactors(xmlNode* node, DataUnit& du);
    void ReadCsvMatrix(xmlNode* node, DataUnit& du);
};

#endif	/* DATAREADER_H */

