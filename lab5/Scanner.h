#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include "Token.h"
#include <vector>
#include <fstream>

enum state {scanning_state, id_state, comment_state, string_state, token_state};

class Scanner
{
public:
    Scanner();

    vector<Token> tokenize(string input);

    void parseID();

    void parseString();

    void parseComment();

    void parseColon();

private:

    vector<Token> token_list;

    ifstream file_in;

    int line_number;

    bool scanning_finished;
};

#endif