#ifndef RELATION_H
#define RELATION_H

using namespace std;
#include <string>
#include <set>
#include "Tuple.h"
#include "Scheme.h"

class Relation
{
public:

    Relation(string name_in, Scheme scheme_in);

    void addTouple(Tuple to_add);

    string toString();

private:

    string name;
    Scheme scheme;
    set<Tuple> tuple_list;


};


#endif
