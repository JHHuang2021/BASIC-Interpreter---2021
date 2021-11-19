/*
 * File: Basic.cpp
 * ---------------
 * This file is the starter project for the BASIC interpreter.
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "command.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"

using namespace std;

/* Function prototypes */

void processLine(string line, Program &program, EvalState &state);

/* Main program */

int main() {
    EvalState state;
    Program program;
//    cout << "Stub implementation of BASIC" << endl;
    while (true) {
        try {
            string input = getLine();
//            if (input.empty())
//                return 0;
            processLine(input, program, state);
            if (state.exit)
                return 0;
        } catch (ErrorException &ex) {
            cerr << ex.getMessage() << endl;
        }
    }
    return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version of
 * implementation, the program reads a line, parses it as an expression,
 * and then prints the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program &program, EvalState &state) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);
    string token = scanner.nextToken();
    if (scanner.getTokenType(token) != NUMBER) {
        if (ifcommand(token)) {//command
            if (token == "QUIT")
                state.exit = true;
            else if (token == "LIST")
                List(program);
            else if (token == "CLEAR")
                Clear(program, state);
            else if (token == "RUN") {
                Run(program, state);
            }
        } else if (ifstatement(token)) {//statement
            if (token == "REM") {}
            else if (token == "LET") {
                Expression *exp = parseExp(scanner);
                int value = exp->eval(state);
                delete exp;
            } else if (token == "PRINT") {
                Expression *exp = parseExp(scanner);
                int value = exp->eval(state);
                delete exp;
                cout << value << endl;
            } else if (token == "INPUT") {
                cout << " ? ";
                token = scanner.nextToken();
                string num;
                while (getline(cin, num)) {
                    string abs_num = num.substr(1);
                    if (isNumber(num))
                        break;
                    cout << "INVALID NUMBER" << endl;
                    cout << " ? ";
                }
                state.setValue(token, atoi(num.c_str()));
            }
        } else {//expression
            scanner.saveToken(token);
            Expression *exp = parseExp(scanner);
            int value = exp->eval(state);
            cout << value << endl;
            delete exp;
        }
    } else {//program
        int line_number = atoi(token.c_str());
        if (scanner.hasMoreTokens()) {
            program.addSourceLine(line_number, line);
            program.setParsedStatement(line_number, parseState(scanner));
        } else
            program.removeLine(line_number);
    }
}