#include "ast.hpp"

// pp
std::string Int::pp() const
{
    return std::to_string(value);
}

// std::string Var::pp() const
// {
//     return variable;
// }

// std::string WildCard::pp() const
// {
//     return "WILDCARD";
// }

std::string Neg::pp() const
{
    return "(NEG " + value->pp() + ")";
}

std::string Paren::pp() const
{
    return "(PAREN " + value->pp() + ")";
}

// interpret
Output Int::interpret() const
{
    return Output(this->value);
}

Output Neg::interpret() const
{
    try
    {
        return -(value->interpret());
    }
    catch (const InterpretException &ie)
    {
        throw ie;
    }
    catch (const std::out_of_range &e)
    {
        throw InterpretException("Value out of range for 64-bit Int.");
    }
    catch (const std::exception &ee)
    {
        throw InterpretException("Unexpected error in interpret.");
    }
}

Output Paren::interpret() const
{
    try
    {
        return value->interpret();
    }
    catch (const InterpretException &ie)
    {
        throw ie;
    }
}