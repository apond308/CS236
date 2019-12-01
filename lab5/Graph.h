#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Node.h"
#include <stack>
#include <set>

using namespace std;
class Graph
{
public:

    Graph(){}
    
    static Graph generateDependencyGraph(vector<Rule> rules_in);

    static Graph generateReverseGraph(vector<Rule> rules_in);

    vector<Node> getPostOrder();

    vector<vector<Node>> getSCCs(vector<Node> postorder_list);

    string sccs_toString(vector<vector<Node>> scc_list);

    string toString();

    vector<Node> node_list;

private:

    void goDeep(Node current_node);

    Node getNodeWithIndex(int index);

    vector<Node> order_list;
    set<int> visited_list;

    vector<vector<Node>> scc_list;

};

#endif