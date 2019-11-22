#ifndef RELATION_H
#define RELATION_H

using namespace std;
#include <string>
#include <set>
#include "Tuple.h"
#include "Scheme.h"

/**
 * @brief Relation class
 * 
 */
class Relation
{

public:

    /**
     * @brief Construct a new Relation object
     * 
     * @param name_in 
     * @param scheme_in 
     */
    Relation(string name_in, Scheme scheme_in);

    void addTuple(Tuple to_add);

    Relation join(Relation relation_in);
    Relation unite(Relation relation_in);

    string toString();
    
    string name;

    Scheme scheme;
    set<Tuple> tuple_list;

};


#endif
