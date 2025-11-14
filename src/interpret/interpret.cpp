#include "interpret.hpp"

Output Interpretter::interpret(std::unique_ptr<Expr> u)
{
    try
    {
        return u->interpret();
    }
    catch (const InterpretException &ie)
    {
        throw ie;
    }
}