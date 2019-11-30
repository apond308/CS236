#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Node.h"

using namespace std;
class Graph
{
public:

    Graph(){}
    
    static Graph generateDependencyGraph(vector<Rule> rules_in);

    static Graph generateReverseGraph(vector<Rule> rules_in);

    string toString();

    vector<Node> node_list;


};

#endif