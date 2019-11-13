#include <stdio.h>
#include <iostream>
#include "Relation.h"
#include "Database.h"
#include "Scheme.h"
#include "Parameter.h"
#include <map>
#include <string>
#include <vector>
#include "Predicate.h"
#include "Rule.h"

using namespace std;
int test(int argc, char* argv[])
{
	// Test project
    Relation test_relation = Relation("test_relation", Scheme());

    test_relation.scheme.push_back("t");
    test_relation.scheme.push_back("y");
    test_relation.scheme.push_back("p");
    test_relation.scheme.push_back("e");

    Tuple new_tuple = Tuple();
    new_tuple.push_back("'char'");
    new_tuple.push_back("'int'");
    new_tuple.push_back("'long'");
    new_tuple.push_back("'float'");
    test_relation.addTuple(new_tuple);
    
    new_tuple = Tuple();
    new_tuple.push_back("'apple'");
    new_tuple.push_back("'pear'");
    new_tuple.push_back("'orange'");
    new_tuple.push_back("'pear'");
    test_relation.addTuple(new_tuple);

    Database test_database = Database();
    vector<Parameter> parameters;
    parameters.push_back(Parameter("t"));
    parameters.push_back(Parameter("y"));

    cout << "relation before: " << test_relation.toString() << endl;
    test_relation = test_database.project(test_relation, parameters);
    cout << "relation after: " << test_relation.toString() << endl;
    return 0;
}