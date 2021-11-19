/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include "parser.h"

using namespace std;

bool ifstatement(const string &token) {
    if (token == "REM") return true;
    else if (token == "LET") return true;
    else if (token == "PRINT") return true;
    else if (token == "INPUT") return true;
    else if (token == "END") return true;
    else if (token == "GOTO") return true;
    else if (token == "IF") return true;
    else return false;
}

/* Implementation of the Statement class */

Statement::Statement() {
    /* Empty */
}

Statement::~Statement() {
    /* Empty */
}

void Remstmt::execute(EvalState &state) {}

Letstmt::Letstmt(Expression *exp) {
    this->exp = exp;
}

void Letstmt::execute(EvalState &state) {
    exp->eval(state);
}

Printstmt::Printstmt(Expression *exp) {
    this->exp = exp;
}

void Printstmt::execute(EvalState &state) {
    int value = exp->eval(state);
    cout << value << endl;
}

Inputstmt::Inputstmt(string &variable) {
    this->variable = variable;
}

void Inputstmt::execute(EvalState &state) {
    cout << " ? ";
    cin >> this->input;
    getchar();
    state.setValue(this->variable, this->input);
}

Endstmt::Endstmt() {}

Endstmt::~Endstmt() {}

void Endstmt::execute(EvalState &state) {
    state.run_end = true;
}

Gotostmt::Gotostmt(int goto_line_number) {
    this->goto_line_number = goto_line_number;
}

Gotostmt::~Gotostmt() {}

void Gotostmt::execute(EvalState &state) {
    state.goto_line_number = goto_line_number;
}

Ifstmt::Ifstmt(string &str_exp, int line_number) {
    this->str_exp = str_exp;
    this->line_number = line_number;
}

Ifstmt::~Ifstmt() {}

void Ifstmt::execute(EvalState &state) {
    TokenScanner exp_judge(str_exp);
    Expression *exp = parseExp(exp_judge);
    exp->setIfJudge();
    int if_true = exp->eval(state);
    if (if_true)
        state.goto_line_number = this->line_number;
    else
        state.goto_line_number = -1;
}