#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "compiler.h"

class SymbolTable
{
    public:
    std::string * keys;
    int * memOffsets;
    bool * isAllocated;
    int size;
    SymbolTable(std::vector<std::string> variables);
    ~SymbolTable();
    int getMemoryOffset(std::string s);
    void setMemoryOffset(std::string s);
    int idxOf(std::string s);
};
class Program
{
    public:
    SymbolTable * symbols;
    struct InstructionNode * program;
    struct InstructionNode * head;
    Program();
    ~Program();
    void printSymbols();
    void initLocation(std::string s);
    void insertInstruction(struct InstructionNode * i);
};