#include "Parser.h"

static int token_list_index;

Parser::Parser(vector<Token> token_list)
{
    this->token_list = token_list;
}

void Parser::throwError(Token error_token)
{
    cout << "Failure!" << endl;
    cout << "  " << error_token.toString() << endl;
    exit(0);
}

void Parser::printLists()
{
    cout << "Success!" << endl;
    cout << "Schemes(" << scheme_list.size() << "):" << endl;
    for (int x=0;x<scheme_list.size();x++)
    {
        cout << "  " << scheme_list[x].toString() << endl;
    }
    cout << "Facts(" << fact_list.size() << "):" << endl;
    for (int x=0;x<fact_list.size();x++)
    {
        cout << "  " << fact_list[x].toString('.') << endl;
    }
    cout << "Rules(" << rule_list.size() << "):" << endl;
    for (int x=0;x<rule_list.size();x++)
    {
        cout << "  " << rule_list[x].toString() << endl;
    }
    cout << "Queries(" << query_list.size() << "):" << endl;
    for (int x=0;x<query_list.size();x++)
    {
        cout << "  " << query_list[x].toString('?') << endl;
    }
    cout << "Domain(" << domain_list.size() << "):" << endl;
    for (auto domain : domain_list)
    {
        cout << domain << endl;
    }
}

void Parser::parse()
{
    token_list_index = 0;
    while(token_list[token_list_index].type != EOF_TOKEN)
    {
        if (token_list[token_list_index].type != SCHEMES)
            throwError(token_list[token_list_index]);
        if (token_list[++token_list_index].type != COLON)
            throwError(token_list[token_list_index]);
        token_list_index++;
        parseSchemeList();
        if (token_list[token_list_index].type != FACTS)
            throwError(token_list[token_list_index]);
        if (token_list[++token_list_index].type != COLON)
            throwError(token_list[token_list_index]);
        token_list_index++;
        parseFactList();
        if (token_list[token_list_index].type != RULES)
            throwError(token_list[token_list_index]);
        if (token_list[++token_list_index].type != COLON)
            throwError(token_list[token_list_index]);
        token_list_index++;
        parseRuleList();
        if (token_list[token_list_index].type != QUERIES)
            throwError(token_list[token_list_index]);
        if (token_list[++token_list_index].type != COLON)
            throwError(token_list[token_list_index]);
        token_list_index++;
        parseQueryList();
    }
}

void Parser::parseSchemeList()
{
    while (token_list[token_list_index].type == ID){
        scheme_list.push_back(parseScheme());
    }
    if (scheme_list.size() == 0)
        throwError(token_list[token_list_index]);
}

void Parser::parseFactList()
{
    while (token_list[token_list_index].type == ID){
        fact_list.push_back(parseFact());
    }
    if (fact_list.size() == 0)
        throwError(token_list[token_list_index]);
}

void Parser::parseRuleList()
{
    while (token_list[token_list_index].type == ID){
        rule_list.push_back(parseRule());
    }
}

void Parser::parseQueryList()
{
    while (token_list[token_list_index].type == ID){
        query_list.push_back(parseQuery());
    }
}


Predicate Parser::parseScheme()
{
    if (token_list[token_list_index].type != ID)
        throwError(token_list[token_list_index]);
    Predicate new_predicate = Predicate(token_list[token_list_index++].value);
    parseIDList(&new_predicate);
    return new_predicate;
}

Predicate Parser::parseFact()
{
    Predicate new_predicate = Predicate(token_list[token_list_index++].value);
    parseStringList(&new_predicate);
    token_list_index++;
    return new_predicate;
}

Rule Parser::parseRule()
{
    Predicate head_predicate = Predicate(token_list[token_list_index++].value);
    parseIDList(&head_predicate);
    Rule new_rule = Rule(head_predicate);
    token_list_index++;
    parsePredicateList(&new_rule);
    token_list_index++;
    return new_rule;
}

Predicate Parser::parseQuery()
{
    Predicate new_predicate = parsePredicate();
    if (token_list[token_list_index].type != Q_MARK)
    {
        throwError(token_list[token_list_index]);
        exit(0);
    }
    token_list_index++;
    return new_predicate;
}

void Parser::parsePredicateList(Rule* new_rule)
{
    while(token_list[token_list_index].type != PERIOD)
    {
        if (token_list[token_list_index].type == ID)
            new_rule->addPredicate(parsePredicate());
        else
            token_list_index++;
    }
}
void Parser::parseParameterList(Predicate* new_predicate)
{
    token_list_index++;
    while(token_list[token_list_index].type != RIGHT_PAREN)
    {
        if (token_list[token_list_index].type != COMMA)
            new_predicate->addParameter(parseParameter());
        else
            token_list_index++;
    }
    token_list_index++;
}

void Parser::addDomain(string input)
{
    if (domain_list.find(input) != domain_list.end())
        return;
    domain_list.insert(input);
}


void Parser::parseStringList(Predicate* new_predicate)
{
    token_list_index++;
    while(token_list[token_list_index].type != RIGHT_PAREN)
    {
        if (token_list[token_list_index].type == STRING)
        {
            new_predicate->addParameter(Parameter(token_list[token_list_index].value));
            addDomain(token_list[token_list_index].value);
        }
        else if (token_list[token_list_index].type != COMMA)
            throwError(token_list[token_list_index]);
        token_list_index++;
    }
    token_list_index++;
}
void Parser::parseIDList(Predicate* new_predicate)
{
    token_list_index++;
    if (token_list[token_list_index].type == RIGHT_PAREN)
        throwError(token_list[token_list_index]);
    while(token_list[token_list_index].type != RIGHT_PAREN)
    {
        if (token_list[token_list_index].type == ID)
            new_predicate->addParameter(Parameter(token_list[token_list_index].value));
        else if (token_list[token_list_index].type == COMMA){}
        else
            throwError(token_list[token_list_index]);
        token_list_index++;
    }
    token_list_index++;
}

Predicate Parser::parsePredicate()
{
    Predicate new_predicate = Predicate(token_list[token_list_index++].value);
    parseParameterList(&new_predicate);
    return new_predicate;
}

Parameter Parser::parseParameter()
{
    if (token_list[token_list_index].type == STRING || token_list[token_list_index].type == ID){
        return Parameter(token_list[token_list_index++].value);
    }
    else{
        return Parameter(parseExpression());
    }
}

string Parser::parseExpression()
{
    string expression_string = "";
    expression_string += token_list[token_list_index++].value;
    expression_string += parseParameter().toString();
    expression_string += parseOperator();
    expression_string += parseParameter().toString();
    expression_string += token_list[token_list_index++].value;
    return expression_string;
}

string Parser::parseOperator()
{
    string return_operator;
    if (token_list[token_list_index].type == ADD)
        return_operator = "+";
    else if (token_list[token_list_index].type == MULTIPLY)
        return_operator = "*";
    else
        throwError(token_list[token_list_index]);
    token_list_index++;
    return return_operator;
}