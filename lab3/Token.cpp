#include "Token.h"

Token::Token(string value_in, int line_in, TokenType type_in)
{
    this->value = value_in;
    this->line_number = line_in;
    this->type = type_in;
}

string Token::toString()
{
    string output = "";
    output += "(" + getTokenString(this->type) + ",\"" + this->value + "\"," + to_string(this->line_number) + ")";
    return output;
}

string Token::getTokenString(TokenType type_in)
{
    string string_out;
    switch(type_in)
    {
        case COMMA:
            string_out = "COMMA";
            break;
        case PERIOD:
            string_out = "PERIOD";
            break;
        case Q_MARK:
            string_out = "Q_MARK";
            break;
        case LEFT_PAREN:
            string_out = "LEFT_PAREN";
            break;
        case RIGHT_PAREN:
            string_out = "RIGHT_PAREN";
            break;
        case COLON:
            string_out = "COLON";
            break;
        case COLON_DASH:
            string_out = "COLON_DASH";
            break;
        case MULTIPLY:
            string_out = "MULTIPLY";
            break;
        case ADD:
            string_out = "ADD";
            break;
        case SCHEMES:
            string_out = "SCHEMES";
            break;
        case FACTS:
            string_out = "FACTS";
            break;
        case RULES:
            string_out = "RULES";
            break;
        case QUERIES:
            string_out = "QUERIES";
            break;
        case ID:
            string_out = "ID";
            break;
        case STRING:
            string_out = "STRING";
            break;
        case COMMENT:
            string_out = "COMMENT";
            break;
        case EOF_TOKEN:
            string_out = "EOF";
            break;
        default:
            string_out = "UNDEFINED";
            break;
    }
    return string_out;
}
