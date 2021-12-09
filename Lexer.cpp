#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "CommaAutomaton.h"
#include "PeriodAutomaton.h"
#include "QMarkAutomaton.h"
#include "LeftParenAutomaton.h"
#include "RightParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "ID_Automaton.h"
#include "StringAutomaton.h"
#include "CommentAutomaton.h"
#include "EOF_Automaton.h"

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
//    for (Automaton* automaton : automata) delete automaton;
//    automata.clear();

    for (Token* token : tokens) delete token;
    tokens.clear();
}

void Lexer::CreateAutomata() {
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new CommaAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new QMarkAutomaton());
    automata.push_back(new LeftParenAutomaton());
    automata.push_back(new RightParenAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new ID_Automaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());
    automata.push_back(new EOF_Automaton());
}

void Lexer::Run(std::string& input)
{
    //std::cout << input << std::endl << std::endl << std::endl << std::endl;
    // TODO: convert this pseudo-code with the algorithm into actual C++ code
    int lineNumber = 1;
    while (input.size() > 0)
    {
        int maxRead = 0;
        Automaton* maxAutomaton = automata[0];
        while (input[0] == ' ' || input[0] == '\t') input = input.substr(1);
        while (input[0] == '\n')
        {
            input = input.substr(1);
            lineNumber += 1;
            while (input[0] == ' ' || input[0] == '\t') input = input.substr(1);
        }
        if (input.size() == 0) break;

        // Here is the "Parallel" part of the algorithm
        for (unsigned int i = 0; i < automata.size(); ++i)
        {
            int inputRead = automata[i]->Start(input);
            if (inputRead > maxRead)
            {
                maxRead = inputRead;
                maxAutomaton = automata[i];
            }
        }

        // Here is the "Max" part of the algorithm
        if (maxRead > 0)
        {
            Token* newToken = maxAutomaton->CreateToken(input.substr(0, maxRead), lineNumber);
            lineNumber += maxAutomaton->NewLinesRead();
            tokens.push_back(newToken);
        }

        // No Automaton Accepted
        // Create Single Character Undefined Token
        else
        {
            maxRead = 1;
            if (input[0] == '\'' || (input[0] == '#' && input[1] == '|'))
            {
                Token* newToken = new Token(TokenType::UNDEFINED, input.substr(0), lineNumber);
                tokens.push_back(newToken);
                maxRead = input.size();

                // Check For New Lines
                for (unsigned int i = 0; i < input.size(); ++i)
                {
                    if (input[i] == '\n') lineNumber++;
                }
            }
            else
            {
                Token* newToken = new Token(TokenType::UNDEFINED, input.substr(0, maxRead), lineNumber);
                tokens.push_back(newToken);
            }
        }

        //Update Input By Removing Characters Read To Create New Tokens
        input = input.substr(maxRead);
    }

    // Add End Of File Token
    Token* newToken = new Token(TokenType::EOF_TYPE, "", lineNumber);
    tokens.push_back(newToken);
}

void Lexer::toString()
{
    for (unsigned int i = 0; i < tokens.size(); ++i)
    {
        std::string printType = "";
        switch(tokens[i]->myType)
        {
            case TokenType::COLON:
                printType = "COLON";
                break;
            case TokenType::COLON_DASH:
                printType = "COLON_DASH";
                break;
            case TokenType::UNDEFINED:
                printType = "UNDEFINED";
                break;
            case TokenType::COMMA:
                printType = "COMMA";
                break;
            case TokenType::PERIOD:
                printType = "PERIOD";
                break;
            case TokenType::MULTIPLY:
                printType = "MULTIPLY";
                break;
            case TokenType::ADD:
                printType = "ADD";
                break;
            case TokenType::QMARK:
                printType = "Q_MARK";
                break;
            case TokenType::LEFTPAREN:
                printType = "LEFT_PAREN";
                break;
            case TokenType::RIGHTPAREN:
                printType = "RIGHT_PAREN";
                break;
            case TokenType::QUERIES:
                printType = "QUERIES";
                break;
            case TokenType::FACTS:
                printType = "FACTS";
                break;
            case TokenType::SCHEMES:
                printType = "SCHEMES";
                break;
            case TokenType::EOF_TYPE:
                printType = "EOF";
                break;
            case TokenType::RULES:
                printType = "RULES";
                break;
            case TokenType::STRING:
                printType = "STRING";
                break;
            case TokenType::COMMENT:
                printType = "COMMENT";
                break;
            case TokenType::ID:
                printType = "ID";
                break;
        }
        std::cout << "(" << printType << ",\""  << tokens[i]->myDescription << "\"," << tokens[i]->myLine << ")\n";
    }
    std::cout << "Total Tokens = " << tokens.size();
}
