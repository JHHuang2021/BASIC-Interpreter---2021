/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface, which is an excellent model for
 * the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include "../StanfordCPPLib/tokenscanner.h"
#include "evalstate.h"
#include "exp.h"

/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

bool ifstatement(const string &token);

class Statement {

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

    Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

    virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

    virtual void execute(EvalState &state) = 0;

};

/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */

class Remstmt : public Statement {
public:
    Remstmt() {};

    virtual ~Remstmt() {};

    virtual void execute(EvalState &state);
};

class Letstmt : public Statement {
private:
    Expression *exp;
public:
    Letstmt(Expression *);

    virtual ~Letstmt() {};

    virtual void execute(EvalState &state);
};

class Printstmt : public Statement {
private:
    Expression *exp;
public:
    Printstmt(Expression *exp);

    virtual ~Printstmt() {};

    virtual void execute(EvalState &state);
};

class Inputstmt : public Statement {
private:
    string variable;
    int input;
public:
    Inputstmt(string &variable);

    virtual ~Inputstmt() {};

    virtual void execute(EvalState &state);
};

class Endstmt : public Statement {
private:
public:
    Endstmt();

    virtual ~Endstmt();

    virtual void execute(EvalState &state);
};

class Gotostmt : public Statement {
private:
    int goto_line_number;
public:
    Gotostmt(int goto_line_number);

    virtual ~Gotostmt();

    virtual void execute(EvalState &state);
};

class Ifstmt : public Statement {
private:
    string str_exp;
    int line_number;
public:
    Ifstmt(string &str_exp,int line_number);

    virtual ~Ifstmt();

    virtual void execute(EvalState &state);
};

#endif