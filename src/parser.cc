#include "parser.h"
#include "compiler.h"

LexicalAnalyzer lexer;

void syntaxErr(){std::cout << "syntax error !!\n"; exit(0);};

Token expect(TokenType t)
{
    if(lexer.peek(1).token_type == t){return lexer.GetToken();}
    else{syntaxErr();}
}

void parse_stmt(Program &p)
{
    Token t = lexer.peek(1);
    TokenType tt = t.token_type;
    if(  tt == ID || tt == WHILE || tt == IF ||
         tt == SWITCH || tt == FOR ) 
    {
        if(tt == ID){parse_assign_statement(p);}
        else if(tt == WHILE) {parse_while_statement(p);}
        else if(tt == IF){ parse_if_stmt(p);}
        else if(tt == SWITCH){parse_switch_stmt(p);}
        else if(tt == FOR){parse_for_stmt(p);}
        else{syntaxErr();}
    } else if(tt == OUTPUT || tt == INPUT)
    {
        if(tt == OUTPUT){parse_output_stmt(p);}
        else if(tt == INPUT) { parse_input_stmt(p);}
        else {syntaxErr();}
    }
}


void parse_output_stmt(Program &p)
{
    expect(OUTPUT);
    std::string id = expect(ID).lexeme;
    expect(SEMICOLON);
    struct InstructionNode * i = new InstructionNode;
    i->type = OUT; 
    i->output_inst.var_index = p.symbols->getMemoryOffset(id);
    p.insertInstruction(i);

}

void parse_input_stmt(Program &p)
{
    expect(INPUT);
    std::string id = expect(ID).lexeme;
    expect(SEMICOLON);
    p.initLocation(id);
    struct InstructionNode * i = new InstructionNode;
    i->type = IN;
    i->input_inst.var_index = p.symbols->getMemoryOffset(id);
    p.insertInstruction(i);
}

void parse_while_statement(Program &p)
{

}

Token parse_primary(Program &p)
{
    Token t = lexer.peek(1);
    if(t.token_type == ID || t.token_type == NUM)
    {
        return lexer.GetToken();
    } else{syntaxErr();}
}

void parse_switch_stmt(Program &p)
{

}

void parse_for_stmt(Program &p)
{

}

void parse_if_stmt(Program &p)
{

}
void parse_assign_statement(Program &p)
{
    std::string id = expect(ID).lexeme;
    expect(EQUAL);
    Token primary = parse_primary(p);
    p.initLocation(id);

    InstructionNode * i = new InstructionNode;
    i->type = ASSIGN;
    i->assign_inst.left_hand_side_index = p.symbols->getMemoryOffset(id);
    Token tt = lexer.peek(1);
    TokenType ttt = tt.token_type;
    if(tt.token_type == SEMICOLON)//use rule assign_stmt -> ID EQUAL primary SEMICOLON
    {
        i->assign_inst.op = OPERATOR_NONE;
        if(primary.token_type == NUM)
        {
            int n = stoi(primary.lexeme);
            mem[next_available] = n;
            i->assign_inst.operand1_index = next_available;
            next_available++;

        } else if(primary.token_type == ID)
        {
            p.initLocation(primary.lexeme);
            i->assign_inst.operand1_index = p.symbols->getMemoryOffset(primary.lexeme);
        }
    }
    else if(ttt == PLUS || ttt == MINUS || ttt == MULT || ttt == DIV)
    {
        lexer.GetToken();
        if(ttt == PLUS)
        { i->assign_inst.op = OPERATOR_PLUS; }
        else if(ttt == MINUS)
        { i->assign_inst.op = OPERATOR_MINUS; }
        else if(ttt == MULT)
        { i->assign_inst.op = OPERATOR_MULT; }
        else if(ttt == DIV)
        { i->assign_inst.op = OPERATOR_DIV; }

        Token operand2 = parse_primary(p);
        if(primary.token_type == NUM)
        {
            int n = stoi(primary.lexeme);
            mem[next_available] = n;
            i->assign_inst.operand1_index = next_available;
            next_available++;
        } else
        {
            i->assign_inst.operand1_index = p.symbols->getMemoryOffset(primary.lexeme);
        }

        if(operand2.token_type == NUM)
        {
            int n = stoi(operand2.lexeme);
            mem[next_available] = n;
            i->assign_inst.operand2_index = next_available;
            next_available++;
        } else
        {
            i->assign_inst.operand2_index = p.symbols->getMemoryOffset(operand2.lexeme);
        }
    }
    expect(SEMICOLON);
    p.insertInstruction(i);
}

Token parse_op(Program &p)
{
    Token t = lexer.peek(1);
    TokenType tt =  t.token_type;
    if(tt == PLUS || tt == MINUS || tt == MULT || tt == DIV)
    {
        return t;
    }
    else{syntaxErr();}
}


void parse_stmt_list(Program &p)
{
    parse_stmt(p);
    Token t = lexer.peek(1);
    TokenType tt = t.token_type;
    if( tt == ID || tt == OUTPUT || tt == INPUT || 
        tt == WHILE || tt == IF    || tt == SWITCH || tt== FOR )
    { parse_stmt_list(p);}
    else if(tt == RBRACE){ return;}
    else {syntaxErr();}
}

void parse_body(Program &p)
{
    expect(LBRACE);
    parse_stmt_list(p);
    expect(RBRACE);
}

void parse_id_list(std::vector<std::string> & idlist)
{
    Token t = expect(ID);
    idlist.push_back(t.lexeme);
    Token tt = lexer.peek(1);
    if(tt.token_type == COMMA)
    {
        lexer.GetToken();
        return parse_id_list(idlist); // maybe sketchy
    }
    else if(tt.token_type == SEMICOLON)
    {return;}
}

void parse_var_section(Program &p)
{
    std::vector<std::string> idlist;
    parse_id_list(idlist);
    p.symbols = new SymbolTable(idlist);
    expect(SEMICOLON);
}
void parse_inputs(Program &p)
{
    parse_num_list(p);
}

void parse_num_list(Program &p)
{
    Token t = expect(NUM);
    inputs.push_back(stoi(t.lexeme));

    TokenType tt = lexer.peek(1).token_type;
    if(tt == NUM){parse_num_list(p);}
    else if(tt == EOF){return;}
}

Program parse_program(Program &p)
{
    
    parse_var_section(p);
    parse_body(p);
    parse_inputs(p);
}
struct InstructionNode * parse_generate_intermediate_representation()
{
    Program p;
    parse_program(p);
    return p.program;
}