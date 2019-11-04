#ifndef PARSER_H
#define PARSER_H
using namespace std;

#include <vector>
#include <set>
#include <fstream>
#include <iostream>

#include "Token.h"
#include "Predicate.h"
#include "Parameter.h"
#include "Rule.h"

class Parser
{
public:

    Parser(vector<Token> token_list);

    void throwError(Token error_token);

    void parse();
    void printLists();

    void parseSchemeList();
    void parseFactList();
    void parseQueryList();
    void parseRuleList();

    Predicate parseScheme();
    Predicate parseFact();
    Rule parseRule();
    Predicate parseQuery();

    void parsePredicateList();
    void parsePredicateList(Rule* new_rule);
    void parseParameterList(Predicate* new_predicate);
    void parseStringList(Predicate* new_predicate);
    void parseIDList(Predicate* new_predicate);

    Predicate parsePredicate();
    Parameter parseParameter();
    string parseExpression();
    string parseOperator();

    void addDomain(string input);

private:

    vector<Token> token_list;

    vector<Predicate> scheme_list;
    vector<Predicate> fact_list;
    vector<Rule> rule_list;
    vector<Predicate> query_list;

    set<string> domain_list;

};


#endif