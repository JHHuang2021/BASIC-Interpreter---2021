/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"

using namespace std;

Program::Program() {
    // Replace this stub with your own code
}

Program::~Program() {
    // Replace this stub with your own code
}

void Program::clear() {
    line_numbers.clear();
    program_lines.clear();
    program_parsed.clear();
    // Replace this stub with your own code
}

void Program::addSourceLine(int lineNumber, const string &line) {
    // Replace this stub with your own code
    line_numbers.insert(lineNumber);
    program_lines[lineNumber] = line;
}

void Program::removeLine(int lineNumber) {
    // Replace this stub with your own code
    program_lines.erase(lineNumber);
    program_parsed.erase(lineNumber);
    line_numbers.erase(lineNumber);
}

string Program::getSourceLine(int lineNumber) {
    return program_lines[lineNumber];
    // Replace this stub with your own code
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    program_parsed[lineNumber] = stmt;
    // Replace this stub with your own code
}

Statement *Program::getParsedStatement(int lineNumber) {
    return program_parsed[lineNumber];
    // Replace this stub with your own code
}

int Program::getFirstLineNumber() {
    if (line_numbers.empty())
        return -1;
    else {
        it = this->line_numbers.begin();
        return *(it++);
    }
    // Replace this stub with your own code
}

int Program::getNextLineNumber() {
    if (it == line_numbers.end())
        return -1;
    else
        return *(it++);
    // Replace this stub with your own code
}

bool Program::program_empty() { return line_numbers.empty(); }

void Program::findLineNumber(int line_number) {
    it = line_numbers.find(line_number);
    if (it == line_numbers.end()) {
        cout << "LINE NUMBER ERROR" << endl;
        error("LINE NUMBER ERROR");
    }
}

