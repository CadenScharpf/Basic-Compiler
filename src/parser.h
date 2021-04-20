#pragma once

#include "compiler.h"
#include "lexer.h"
#include "program.h"
#include <vector>
#include <iostream>
#include <string>

void syntaxErr();

Token expect(TokenType t);

void parse_stmt_list(Program &p);

Token parse_primary(Program &p);

void parse_stmt(Program &p);

void parse_output_stmt(Program &p);

void parse_input_stmt(Program &p);

void parse_while_statement(Program &p);

void parse_if_stmt(Program &p);

void parse_switch_stmt(Program &p);

Token parse_op(Program &p);

void parse_for_stmt(Program &p);

void parse_inputs(Program &p);

void parse_num_list(Program &p);

void parse_if_stmt(Program &p);

void parse_assign_statement(Program &p);

void parse_body(Program &p);

void parse_id_list(std::vector<std::string> & idlist);

void parse_var_section(Program &p);

Program parse_program();

struct InstructionNode * parse_generate_intermediate_representation();