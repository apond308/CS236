#include "Scanner.h"
#include <cctype>

Scanner::Scanner()
{

}

void Scanner::tokenize(string input)
{
    file_in.open(input);
    line_number = 1;
    state current_state = scanning_state;
    state next_state = current_state;
    scanning_finished = false;
    while(!scanning_finished)
    {
        char character = file_in.peek();
        // cout << "Current character: " << (char)character << endl;
        if (isspace(character)) {
            if (character=='\n'){
                line_number++;
                file_in.get();
                continue;
            }
            else if (character == ' ' || character == '\t'){
                file_in.get();
                continue;
            }
        }
        // cout << "Current state: " << current_state << endl;
        if (isalpha(character))
            parseID();
        else if (character=='#')
            parseComment();
        else if (character == '\'')
            parseString();
        else if (character == ':'){
            parseColon();
        }
        else
        {
            if (character == ',')
                token_list.push_back(Token(",", line_number, COMMA));
            else if (character == '.')
                token_list.push_back(Token(".", line_number, PERIOD));
            else if (character == '?')
                token_list.push_back(Token("?", line_number, Q_MARK));
            else if (character == '(')
                token_list.push_back(Token("(", line_number, LEFT_PAREN));
            else if (character == ')')
                token_list.push_back(Token(")", line_number, RIGHT_PAREN));
            else if (character == '*')
                token_list.push_back(Token("*", line_number, MULTIPLY));
            else if (character == '+')
                token_list.push_back(Token("+", line_number, ADD));
            else if (character == EOF){
                token_list.push_back(Token("", line_number, EOF_TOKEN));
                scanning_finished = true;
            }
            else
                token_list.push_back(Token(string(1, character), line_number, UNDEFINED));
            file_in.get();
        }

        current_state = next_state;
    }
    for (unsigned int x=0;x<token_list.size();x++)
    {
        cout << token_list[x].toString() << endl;
    }
    cout << "Total Tokens = " << token_list.size() << endl;
}

void Scanner::parseID()
{
    string word = "";
    while(isalnum(file_in.peek()))
    {
        word += file_in.get();
    }
    if (word == "Schemes")
        token_list.push_back(Token("Schemes", line_number, SCHEMES));
    else if (word == "Facts")
        token_list.push_back(Token("Facts", line_number, FACTS));
    else if (word == "Facts")
        token_list.push_back(Token("Facts", line_number, FACTS));
    else if (word == "Rules")
        token_list.push_back(Token("Rules", line_number, RULES));
    else if (word == "Queries")
        token_list.push_back(Token("Queries", line_number, QUERIES));
    else
        token_list.push_back(Token(word, line_number, ID));
}

void Scanner::parseString()
{
    string word = "";
    word += file_in.get();
    bool done = false;
    int orig_line_number = line_number;
    while(!done)
    {
        char character = file_in.peek();
        if (character == '\'')
        {
            file_in.get();
            if(file_in.peek() != '\'')
                done = true;
            else
                word += file_in.get();
        }
        else if (character == '\n'){
            line_number++;
            file_in.get();
        }
        else if (character == EOF)
        {
            token_list.push_back(Token(word, orig_line_number, UNDEFINED));
            return;
        }
        else
            file_in.get();
        word += character;
    }
    token_list.push_back(Token(word, orig_line_number, STRING));
}

void Scanner::parseComment()
{
    string word = "";
    word += file_in.get();
    char character;
    int orig_line_number = line_number;
    if (file_in.peek() == '|')
    {
        word+= file_in.get();
        character = file_in.get();
        while(true)
        {
            if (character == '|' && file_in.peek() == '#'){
                file_in.get();
                word += "|#";
                break;
            }
            else if (character == '\n')
                line_number++;
            else if (character == EOF)
            {
                token_list.push_back(Token(word, orig_line_number, UNDEFINED));
                return;
            }
            word += character;
            character = file_in.get();
        }
    }
    else
    {
        char character = file_in.peek();
        while(file_in.peek() != '\n')
        {
            character = file_in.get();
            word += character;
        }
    }
    // token_list.push_back(Token(word, orig_line_number, COMMENT));
}

void Scanner::parseColon()
{
    string word = "";
    word += file_in.get();
    if (file_in.peek() == '-')
    {
        word += file_in.get();
        token_list.push_back(Token(":-", line_number, COLON_DASH));
    }
    else
        token_list.push_back(Token(":", line_number, COLON));
}