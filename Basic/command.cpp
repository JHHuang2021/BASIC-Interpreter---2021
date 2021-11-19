#include <string>
#include "command.h"

bool ifcommand(const std::string &str) {
    if (str == "RUN") { return true; }
    else if (str == "LIST") { return true; }
    else if (str == "CLEAR") { return true; }
    else if (str == "QUIT") { return true; }
    else if (str == "HELP") { return true; }
    else return false;
}

void List(Program &program) {
    int line_number = program.getFirstLineNumber();
    if (line_number == -1)
        return;
    {
        cout << program.getSourceLine(line_number) << endl;
        while ((line_number = program.getNextLineNumber()) != -1) {
            cout << program.getSourceLine(line_number) << endl;
        }
    }
}

void Clear(Program &program, EvalState &state) {
    while (!program.program_empty()) {
        int line_number;
        line_number = program.getFirstLineNumber();
        program.removeLine(line_number);
    }
    state.clearSymbolTable();
}

void Run(Program &program, EvalState &state) {
    state.run_end = false;
    if (!program.program_empty()) {
        int program_line = program.getFirstLineNumber();
        program.getParsedStatement(program_line)->execute(state);
        if (state.goto_line_number != -1) {
            program.findLineNumber(state.goto_line_number);
            state.goto_line_number = -1;
        }
        while ((program_line = program.getNextLineNumber()) != -1) {
            program.getParsedStatement(program_line)->execute(state);
            if (state.goto_line_number != -1) {
                program.findLineNumber(state.goto_line_number);
                state.goto_line_number = -1;
            }
            if (state.run_end)
                return;
        }
    }
}