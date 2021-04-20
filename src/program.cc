#include "program.h"

//SYMBOL TABLE
SymbolTable::SymbolTable(std::vector<std::string> variables)
{
    keys = (std::string*) malloc(sizeof(std::string) * variables.size());
    memOffsets = (int*) calloc(variables.size(), sizeof(int));
    isAllocated = (bool *) malloc(sizeof(bool) * variables.size());
    size = variables.size();
    int i = 0;
    for(auto v : variables)
    {
        keys[i] = v;
        memOffsets[i] = 0;
        isAllocated[i] = false;
        i++;
    };
}

SymbolTable::~SymbolTable()
{
    free(keys);
}


int SymbolTable::getMemoryOffset(std::string s)
{
    for(int i = 0; i < size; i ++)
    {
        if(keys[i] == s){return memOffsets[i];}
    }
    return -1;//not found
}
void SymbolTable::setMemoryOffset(std::string s)
{
    for(int i = 0; i < size; i ++)
    {
        if(keys[i] == s && isAllocated[i] == 0)
        {
            memOffsets[i] = next_available;
            next_available++;
            isAllocated[i] = 1;
            return;
        }
    }
}

int SymbolTable::idxOf(std::string s)
{
    for(int i = 0; i < size; i++)
    {
        if(keys[i] == s){return i;}
        return -1;
    }
}


//PROGRAM 
Program::Program()
{
    symbols = NULL;
    program = NULL;
    head = NULL;
}
Program::~Program()
{

}
void Program::insertInstruction(struct InstructionNode * i)
{
    i->next = NULL;
    if(head == NULL)
    {
        program = i;
        head = i;
    }
    else
    {
        head->next = i;
        head = i;
    }
}
void Program::printSymbols()
{
    for(int i = 0; i < symbols->size; i++ )
    {
        std::cout << symbols->keys[i] << " : " << symbols->getMemoryOffset(symbols->keys[i]) << std::endl;
    }
}

void Program::initLocation(std::string s)
{
    symbols->setMemoryOffset(s);
}