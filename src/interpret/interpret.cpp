#include "interpret.hpp"

Output Interpretter::interpret(std::unique_ptr<Expr> u)
{
    try
    {
        auto c = std::make_unique<Config<Output>>();
        return u->interpret(std::move(c))->value;
    }
    catch (const InterpretException &ie)
    {
        throw ie;
    }
}