#ifndef CODE_COMMAND_H
#define CODE_COMMAND_H

#include "program.h"

bool ifcommand(const std::string &str);

void List(Program &program);

void Clear(Program &program, EvalState &state);

void Run(Program &program, EvalState &state);

#endif //CODE_COMMAND_H
