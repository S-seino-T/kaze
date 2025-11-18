#include "ast.hpp"
using Conf = std::unique_ptr<Config<Output>>;
// pp
std::string Int::pp() const
{
    return std::to_string(value);
}

std::string Var::pp() const
{
    return variable;
}

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

std::string Add::pp() const
{
    return "(ADD " + lvalue->pp() + " " + rvalue->pp() + ")";
}

std::string Sub::pp() const
{
    return "(SUB " + lvalue->pp() + " " + rvalue->pp() + ")";
}

std::string Let::pp() const
{
    return "(LET " + variable->pp() + " " + expr->pp() + ")";
}

// interpret
Conf Int::interpret(Conf c) const
{
    c->value = Output(this->value);
    return c;
}

Conf Var::interpret(Conf c) const
{
    Output ret;
    if (defining)
    {
        c->variable = variable;
        c->value = ret;
        return c;
    }
    try
    {
        ret = c->search_let(variable);
        c->value = ret;
        return c;
    }
    catch (const VariableException &e)
    {
        throw InterpretException(e.what());
    }
}

Conf Neg::interpret(Conf c) const
{
    try
    {
        auto ret = value->interpret(std::move(c));
        ret->value = -ret->value;
        return ret;
    }
    catch (const InterpretException &ie)
    {
        throw ie;
    }
    catch (const std::exception &ee)
    {
        throw InterpretException("Unexpected error in interpret.");
    }
}

Conf Paren::interpret(Conf c) const
{
    try
    {
        return value->interpret(std::move(c));
    }
    catch (const InterpretException &ie)
    {
        throw ie;
    }
}

Conf Add::interpret(Conf c) const
{
    try
    {
        auto l = lvalue->interpret(std::move(c));
        Output lv = l->value;
        auto r = rvalue->interpret(std::move(l));
        r->value = r->value + lv;
        return r;
    }
    catch (const InterpretException &ie)
    {
        throw ie;
    }
    catch (const std::exception &ee)
    {
        throw InterpretException("Unexpected error in interpret.");
    }
}

Conf Sub::interpret(Conf c) const
{
    try
    {
        auto l = lvalue->interpret(std::move(c));
        Output lv = l->value;
        auto r = rvalue->interpret(std::move(l));
        r->value = lv - r->value;
        return r;
    }
    catch (const InterpretException &ie)
    {
        throw ie;
    }
    catch (const std::exception &ee)
    {
        throw InterpretException("Unexpected error in interpret.");
    }
}

Conf Let::interpret(Conf c) const
{
    std::string var = c->variable;
    try
    {
        auto ret = expr->interpret(std::move(c));
        if (!ret->try_add_let_dict(var, ret->value))
        {
            throw VariableException("`" + var + "` is immutable.");
        }
        ret->value = Output();
        return ret;
    }
    catch (const VariableException &e)
    {
        throw InterpretException(e.what());
    }
    catch (const InterpretException &e)
    {
        throw e;
    }
}