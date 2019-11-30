#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Node.h"

using namespace std;
class Graph
{
public:

    Graph(vector<Rule> rules_in);
    
    void generateDependencyGraph();

    vector<Node> node_list;


};

#endif