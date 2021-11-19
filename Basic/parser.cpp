/*
 * File: parser.cpp
 * ----------------
 * Implements the parser.h interface.
 */

#include <iostream>
#include <string>
#include <cctype>

#include "exp.h"
#include "parser.h"
#include "statement.h"

#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/strlib.h"
#include "../StanfordCPPLib/tokenscanner.h"

using namespace std;

Statement *parseState(TokenScanner &scanner) {
    string token = scanner.nextToken();
//    TokenType type = scanner.getTokenType(token);
    if (token == "REM") {
        if (scanner.hasMoreTokens()) {
            return new Remstmt();
        }
    } else if (token == "LET") {
        return new Letstmt(parseExp(scanner));
    } else if (token == "PRINT") {
        return new Printstmt(parseExp(scanner));
    } else if (token == "INPUT") {
        token = scanner.nextToken();
        return new Inputstmt(token);
    } else if (token == "END")
        return new Endstmt();
    else if (token == "GOTO") {
        token = scanner.nextToken();
        return new Gotostmt(atoi(token.c_str()));
    } else if (token == "IF") {
        string judge;
        while (token = scanner.nextToken(), token != "THEN") {
            judge += token;
        }
        return new Ifstmt(judge, atoi(scanner.nextToken().c_str()));
//        TokenScanner exp_judge(judge);
//        EvalState state;
//        Expression *exp = parseExp(exp_judge);
//        int if_true = exp->eval(state);
//        if (if_true)
//            return new Gotostmt(atoi(scanner.nextToken().c_str()));
//        else return new Gotostmt(-1);
    } else {}
}


/*
 * Implementation notes: parseExp
 * ------------------------------
 * This code just reads an expression and then checks for extra tokens.
 */

Expression *parseExp(TokenScanner &scanner) {
    Expression *exp = readE(scanner);
    if (scanner.hasMoreTokens()) {
        error("parseExp: Found extra token: " + scanner.nextToken());
    }
    return exp;
}

/*
 * Implementation notes: readE
 * Usage: exp = readE(scanner, prec);
 * ----------------------------------
 * This version of readE uses precedence to resolve the ambiguity in
 * the grammar.  At each recursive level, the parser reads operators and
 * subexpressions until it finds an operator whose precedence is greater
 * than the prevailing one.  When a higher-precedence operator is found,
 * readE calls itself recursively to read in that subexpression as a unit.
 */

Expression *readE(TokenScanner &scanner, int prec) {
    Expression *exp = readT(scanner);
    string token;
    while (true) {
        token = scanner.nextToken();
        int newPrec = precedence(token);
        if (newPrec <= prec) break;
        Expression *rhs = readE(scanner, newPrec);
        exp = new CompoundExp(token, exp, rhs);
    }
    scanner.saveToken(token);
    return exp;
}

/*
 * Implementation notes: readT
 * ---------------------------
 * This function scans a term, which is either an integer, an identifier,
 * or a parenthesized subexpression.
 */

Expression *readT(TokenScanner &scanner) {
    string token = scanner.nextToken();
    TokenType type = scanner.getTokenType(token);
    if (ifstatement(token)) {
        cout << "SYNTAX ERROR" << endl;
        error("SYNTAX ERROR");
    }
    if (type == WORD) return new IdentifierExp(token);
    if (type == NUMBER) return new ConstantExp(stringToInteger(token));
    if (token != "(") error("Illegal term in expression");
    Expression *exp = readE(scanner);
    if (scanner.nextToken() != ")") {
        error("Unbalanced parentheses in expression");
    }
    return exp;
}

/*
 * Implementation notes: precedence
 * --------------------------------
 * This function checks the token against each of the defined operators
 * and returns the appropriate precedence value.
 */

int precedence(string token) {
    if (token == "=" || token == "<" || token == ">") return 1;
    if (token == "+" || token == "-") return 2;
    if (token == "*" || token == "/") return 3;
    return 0;
}

bool isNumber(const string &str) {
    int symbol = 0;
    for (char const &c: str) {
        if (c == '-' && symbol == 0)
            symbol = 1;
        else if (std::isdigit(c) == 0)
            return false;
    }
    return true;
}
