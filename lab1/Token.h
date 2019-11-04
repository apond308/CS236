#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <iostream>

using namespace std;

enum TokenType {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON,
    COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES,
    QUERIES, ID, STRING, COMMENT, UNDEFINED, EOF_TOKEN};

class Token
{
public:

    Token(string value_in, int line_in, TokenType type_in);

    string toString();

    string getTokenString(TokenType type_in);

    static TokenType getTokenType(string string_in);

private:
    string value;
    int line_number;
    TokenType type;
};

#endif